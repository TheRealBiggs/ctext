module;

#include "helpers.hpp"

#include <miniz/miniz.h>
#include <cstdint>

export module ctext.hooks:detchman_resource;

import ctext.config;
import ctext.io;

import std;

#define LOG_RES_HOOK 1


namespace {
	std::vector<mz_zip_archive*> loadedCtpArchives;
	std::unordered_map<std::string, ctext::io::FileEntry*> overridenFilepaths;


	void LoadCtpArchive(const std::filesystem::path& path) {
		const auto ctpFilename = path.generic_string();

		auto ctp = new mz_zip_archive{ 0 };
		mz_zip_reader_init_file(ctp, ctpFilename.c_str(), 0);

		for (unsigned int i = 0; i < mz_zip_reader_get_num_files(ctp); ++i) {
			mz_zip_archive_file_stat fileStat{ 0 };
			mz_zip_reader_file_stat(ctp, i, &fileStat);

			const std::string filename(fileStat.m_filename);
			std::string lcFilename(filename);
			std::transform(
				lcFilename.begin(),
				lcFilename.end(),
				lcFilename.begin(),
				[](unsigned char c) { return std::tolower(c); }
			);

			overridenFilepaths[lcFilename] = new ctext::io::ZipFileEntry(
				ctp,
				ctpFilename,
				filename,
				static_cast<size_t>(fileStat.m_uncomp_size)
			);
		}
	}


	HOOK_RET(DetchmanResource_LoadFileEntry, __stdcall, uint8_t*, const std::string& filename, size_t* outLen) {
#if LOG_RES_HOOK
		LOG_DEBUG("RES_HOOK: " << filename);
#endif

		std::string lcFilename = filename;
		std::transform(
			lcFilename.begin(),
			lcFilename.end(),
			lcFilename.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);

		if (!overridenFilepaths.contains(lcFilename))
			return CALL_ORIG(DetchmanResource_LoadFileEntry, filename, outLen);

		const auto* entry = overridenFilepaths[lcFilename];

#if LOG_RES_HOOK
		LOG_DEBUG("RES_HOOK: Redirecting to " << entry->GetFilePath());
#endif

		auto* buf = entry->GetData(outLen);

		return buf;
	}
}


export namespace ctext::hooks {
	void InitialiseDetchmanResourceHooks() {
		if (!std::filesystem::exists("mods"))
			return;

		const auto& loadOrder = ctext::Config::Get().ModsLoadOrder;

		for (const auto& load : loadOrder) {
			auto modPath = "mods" / std::filesystem::path(load);
			std::filesystem::path ctpPath(modPath);
			ctpPath.replace_extension(".ctp");

			if (std::filesystem::exists(ctpPath)) {
				LoadCtpArchive(ctpPath);

				continue;
			}

			if (!std::filesystem::exists(modPath))
				continue;

			const auto iter = std::filesystem::recursive_directory_iterator(modPath);

			for (const auto& filePath : iter) {
				if (!filePath.is_regular_file())
					continue;

				const auto relPath = filePath.path().lexically_relative(modPath);

				auto pattern = std::filesystem::path(relPath);

				if (pattern.extension() == ".mp3" || pattern.extension() == ".ogg")
					pattern.replace_extension(".sab");

				auto str = pattern.generic_string();
				std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });

				if (!overridenFilepaths.contains(str))
					overridenFilepaths[str] = new io::FilesystemFileEntry(filePath.path().string());
			}
		}
	}

	void EnableDetchmanResourceHooks() {
		ENABLE_HOOK(DetchmanResource_LoadFileEntry, 0xB9DD0);
	}

	void UninitialiseDetchmanResourceHooks() {
		for (auto& ctp : loadedCtpArchives)
			mz_zip_reader_end(ctp);
	}
}