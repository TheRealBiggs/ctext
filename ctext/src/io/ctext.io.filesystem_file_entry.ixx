module;

#include <cstdint>

export module ctext.io:filesystem_file_entry;

import :file_entry;

import std;


export namespace ctext::io {
	class FilesystemFileEntry final : public FileEntry {
	public:
		FilesystemFileEntry(const std::string& filepath)
			: filepath(filepath), filesize(static_cast<size_t>(std::filesystem::file_size(filepath))) {

		}

		~FilesystemFileEntry() {

		}


		virtual uint8_t* GetData(size_t* outLen) const override {
			auto buf = new uint8_t[filesize];

			std::ifstream file(filepath, std::ios::binary);
			file.read(reinterpret_cast<char*>(buf), filesize);
			file.close();

			*outLen = filesize;

			return buf;
		}

		virtual const std::string& GetFilePath() const override {
			return filepath;
		}


	private:
		std::string filepath;
		size_t filesize;
	};
}