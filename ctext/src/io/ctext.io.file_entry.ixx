module;

#include <cstdint>

export module ctext.io:file_entry;

import std;


export namespace ctext::io {
	class FileEntry {
	public:
		virtual uint8_t* GetData(size_t* outLen) const = 0;
		virtual const std::string& GetFilePath() const = 0;
	};
}