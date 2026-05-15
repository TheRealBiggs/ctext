module;

#include "build_config.hpp"

export module ctext.hooks;

import :ctr;
import :ctr.resource_manager;
import :detchman_resource;
import :field_impl;
import :msg_window;
import :name_input_scene;
import :sound_mananger;
import :sound_task;
import :text_manager;


export namespace ctext::hooks {
	void InitialiseHooks() {
		InitialiseDetchmanResourceHooks();
	}

	void EnableHooks() {
		EnableDetchmanResourceHooks();
		EnableFieldImplHooks();
		EnableCtrHooks();
		EnableCtrResourceManagerHooks();
		EnableSoundManagerHooks();
		EnableSoundTaskHooks();

#ifdef FEATURE_VOICE_ACTING
		EnableNameInputSceneHooks();
		EnableMsgWindowHooks();
		EnableTextManagerHooks();
#endif
	}

	void UninitialiseHooks() {
		UninitialiseDetchmanResourceHooks();
	}
}