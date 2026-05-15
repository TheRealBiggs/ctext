module;

#include "helpers.hpp"

#include <cstdint>

export module ct.audio:sound_obj;


export namespace SQEX::Sd::Driver {
	struct SoundController {
		uint32_t dword0;
		uint32_t dword4;

		static ADDR_AS_FUNC(int, __fastcall, Play, 0x2F0930, SoundController*, _this, int, _, float, a2, float, a3, int, a4);
		static ADDR_AS_FUNC(void, __fastcall, Resume, 0x2F0AC0, SoundController*, _this, int, _, float, a2, int, a3);
	};
}


export namespace ct::audio {
	class SoundObj {
	public:
		enum class SoundType {
			BGM,
			SE_1,
			SE_2
		};
		

		int id;
		uint32_t dword4;
		SQEX::Sd::Driver::SoundController controller;
		SoundType type;
		bool isOneShot;
		uint32_t volume;
		uint8_t* data;
		size_t dataLength;
		uint8_t gap[4];
	};
}