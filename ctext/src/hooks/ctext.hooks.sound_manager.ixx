module;

#include "helpers.hpp"

#include <cstdint>

export module ctext.hooks:sound_mananger;

import ct.audio;
import ctext.ma_sound_task;


namespace {
	HOOK_CLSFN(SoundManager_playSound, ct::audio::SoundManager,
		ct::audio::SoundObj* sound, int a3, int _stackfix0, int _stackfix1, int _stackfix2) {

		if (sound->type != ct::audio::SoundObj::SoundType::BGM)
			return CALL_ORIG(SoundManager_playSound, _this, sound, a3, _stackfix0, _stackfix1, _stackfix2);

		ct::audio::SoundTask* task = nullptr;

		if (*reinterpret_cast<uint32_t*>(sound->data) == 0x66626173 /* "SABF" */) {
			task = (ct::audio::SoundTask*)operator new(0x24);
			*(uintptr_t*)task = ADDR(0x3A1E3C);
			task->id = _this->nextSoundTaskId++;
			task->int8 = -1;
			task->sound = nullptr;
			task->dword10 = 0;
			task->isPlaying = false;
			task->isPaused = false;
			task->isStopped = false;
			task->byte17 = 0;
		} else
			task = new ctext::MASoundTask(_this->nextSoundTaskId++);

		if (sound->id != 0x45 && sound->id != ct::audio::prevBgmId)
			ct::audio::prevBgmTime = 0;

		float time = 0;

		if (ct::audio::resumePrevBgm && ct::audio::prevBgmId == sound->id) {
			time = ct::audio::prevBgmTime;

			ct::audio::resumePrevBgm = false;
		}

		task->init(sound, a3);
		task->play(time);

		_this->tasks.push_back(task);
	}
}


export namespace ctext::hooks {
	void EnableSoundManagerHooks() {
		ENABLE_HOOK(SoundManager_playSound, 0x1A1EF0);
	}
}