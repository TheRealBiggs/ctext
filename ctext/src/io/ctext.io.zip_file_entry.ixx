module;

#include <miniz/miniz.h>
#include <cstdint>

export module ctext.io:zip_file_entry;

import :file_entry;

import std;


export namespace ctext::io {
	class ZipFileEntry final : public FileEntry {
	public:
		ZipFileEntry(
			mz_zip_archive* ctp,
			const std::string& archiveFilename,
			const std::string& filename,
			size_t filesize
		) : ctp(ctp), filepath(archiveFilename + ":" + filename), filename(filename), filesize(filesize) {
		
		}

		~ZipFileEntry() {

		}


		virtual uint8_t* GetData(size_t* outLen) const override {
			auto buf = new uint8_t[filesize];

			mz_zip_reader_extract_file_to_mem(ctp, filename.c_str(), buf, filesize, 0);

			*outLen = filesize;

			return buf;
		}

		virtual const std::string& GetFilePath() const override {
			return filepath;
		}


	private:
		mz_zip_archive* ctp;
		std::string filepath;
		std::string filename;
		size_t filesize;
	};
}