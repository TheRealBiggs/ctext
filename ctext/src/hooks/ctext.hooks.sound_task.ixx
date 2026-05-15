module;

#include "helpers.hpp"

export module ctext.hooks:sound_task;

import ct.audio;

import std;


namespace {
	HOOK_CLSFN(SoundTask_stop, ct::audio::SoundTask) {
		if (_this->sound->type == ct::audio::SoundObj::SoundType::BGM) {
			if (_this->sound->id == 0x45)
				ct::audio::resumePrevBgm = true;
			else {
				ct::audio::prevBgmId = _this->sound->id;

				float time = _this->getCurrentTime();

				auto offset = *(uint32_t*)(_this->sound->data + 0x58);
				offset += *(uint32_t*)(_this->sound->data + offset + 0x10);

				auto rate = *(uint32_t*)(_this->sound->data + offset + 0x08);
				auto loopStart = *(uint32_t*)(_this->sound->data + offset + 0x0C);
				auto loopEnd = *(uint32_t*)(_this->sound->data + offset + 0x10);

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

		CALL_ORIG(SoundTask_stop, _this);
	}
}


export namespace ctext::hooks {
	void EnableSoundTaskHooks() {
		ENABLE_HOOK(SoundTask_stop, 0x1A2350);
	}
}