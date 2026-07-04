module;

#include "helpers.hpp"

export module ctext.hooks:sound_task;

import ct.addr;
import ct.audio;
import ctext.config;

import std;

using namespace ct::addr;
using namespace ct::audio;


namespace {
	C_FN_HOOK_A(
		void, SoundTask, stop,
		SOUND_TASK_STOP
	) {
		if (sound->type == SoundObj::SoundType::BGM) {
			if (sound->id == 0x45)
				ct::audio::resumePrevBgm = true;
			else {
				ct::audio::prevBgmId = sound->id;

				float time = getCurrentTime();

				auto offset = *(uint32_t*)(sound->data + 0x58);
				offset += *(uint32_t*)(sound->data + offset + 0x10);

				auto rate = *(uint32_t*)(sound->data + offset + 0x08);
				auto loopStart = *(uint32_t*)(sound->data + offset + 0x0C);
				auto loopEnd = *(uint32_t*)(sound->data + offset + 0x10);

				auto start = loopStart / (float)rate;
				auto end = loopEnd / (float)rate;
				auto duration = end - start;

				if (time > end) {
					time -= start;
					auto loops = std::floor(time / duration);
					auto inLoopTime = time - loops * duration;
					time = start + inLoopTime;
				}

				ct::audio::prevBgmTime += time;
			}
		}

		C_CALL_ORIG();
	}
}


export namespace ctext::hooks {
	void EnableSoundTaskHooks() {
		if (ctext::Config::Get().FixesFixBgmResumeAfterBattle)
			ENABLE_C_FN_HOOK(SoundTask, stop);
	}
}