module;

#include "helpers.hpp"

#include <cstdint>

export module sqex.sd.driver:sound_controller;

import ct.addr;

using namespace ct::addr;


export namespace SQEX::Sd::Driver {
	class SoundController {
	public:
		C_FN(
			int, Play,
			SQEX_SD_DRIVER_SOUND_CONTROLLER_PLAY,
			int, _, float, a2, float, a3, int, a4
		);
		C_FN(
			void, Resume,
			SQEX_SD_DRIVER_SOUND_CONTROLLER_RESUME,
			int, _, float, a2, int, a3
		);


		uint32_t dword0;
		uint32_t dword4;
	};
}