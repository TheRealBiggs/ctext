module;

#include "helpers.hpp"

#include <cstdint>

export module ctext.hooks:sound_mananger;

import ct.audio;
import ctext.ma_sound_task;


namespace {
	HOOK_CLSFN(SoundManager_playSound, ct::audio::SoundManager,
		ct::audio::SoundObj* sound, int a3, int _stackfix0, int _stackfix1, int _stackfix2) {

		if (sound->type != ct::audio::SoundObj::SoundType::BGM
			|| *reinterpret_cast<uint32_t*>(sound->data) == 0x66626173 /* "SABF" */)
			return CALL_ORIG(SoundManager_playSound, _this, sound, a3, _stackfix0, _stackfix1, _stackfix2);

		auto task = new ctext::MASoundTask(_this->nextSoundTaskId++);
		task->init(sound, a3);
		task->play(0);

		_this->tasks.push_back(task);
	}
}


export namespace ctext::hooks {
	void EnableSoundManagerHooks() {
		ENABLE_HOOK(SoundManager_playSound, 0x1A1EF0);
	}
}