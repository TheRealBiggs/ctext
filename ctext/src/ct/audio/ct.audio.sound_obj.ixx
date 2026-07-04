module;

#include "helpers.hpp"

#include <cstdint>

export module ct.audio:sound_obj;

import ct.addr;
import sqex.sd.driver;

using namespace ct::addr;


export namespace ct::audio {
	class SoundObj {
	public:
		enum class SoundType {
			BGM,
			SE_1,
			SE_2
		};


		FN_CC(
			__fastcall, void*, createSound,
			SOUND_OBJ_CREATE_SOUND,
			unsigned int, a1, unsigned int, a2
		);
		

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