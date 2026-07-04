module;

#include "helpers.hpp"

#include <cstdint>

export module ctext.hooks:sound_mananger;

import ct.addr;
import ct.audio;
import ctext.config;
import ctext.ma_sound_task;

using namespace ct::addr;
using namespace ct::audio;


namespace {
	C_FN_HOOK_A(
		void, SoundManager, playSound,
		SOUND_MANAGER_PLAY_SOUND,
		SoundObj*, sound, int, a3, int, _stackfix0, int, _stackfix1, int, _stackfix2
	) {
		if (sound->type != SoundObj::SoundType::BGM)
			return C_CALL_ORIG(sound, a3, _stackfix0, _stackfix1, _stackfix2);

		SoundTask* task = nullptr;

		if (*reinterpret_cast<uint32_t*>(sound->data) == 0x66626173 /* "SABF" */) {
			task = (ct::audio::SoundTask*)operator new(0x24);
			*(uintptr_t*)task = ADDR(SOUND_TASK_VFTABLE);
			task->id = nextSoundTaskId++;
			task->int8 = -1;
			task->sound = nullptr;
			task->dword10 = 0;
			task->isPlaying = false;
			task->isPaused = false;
			task->isStopped = false;
			task->byte17 = 0;
		} else
			task = new ctext::MASoundTask(nextSoundTaskId++);

		const auto& cfg = ctext::Config::Get();

		if (cfg.FixesFixBgmResumeAfterBattle) {
			if (sound->id != 0x45 && sound->id != ct::audio::prevBgmId)
				ct::audio::prevBgmTime = 0;
		}

		float time = 0;

		if (cfg.FixesFixBgmResumeAfterBattle) {
			if (ct::audio::resumePrevBgm && ct::audio::prevBgmId == sound->id) {
				time = ct::audio::prevBgmTime;

				ct::audio::resumePrevBgm = false;
			}
		}

		task->init(sound, a3);
		task->play(time);

		tasks.push_back(task);
	}
}


export namespace ctext::hooks {
	void EnableSoundManagerHooks() {
		ENABLE_C_FN_HOOK(SoundManager, playSound);
	}
}