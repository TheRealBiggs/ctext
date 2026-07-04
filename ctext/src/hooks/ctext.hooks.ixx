module;

#include "build_config.hpp"

export module ctext.hooks;

import :ctr;
import :ctr.resource_manager;
import :detchman_resource;
import :field_impl;
import :msg_window;
import :name_input_scene;
import :render;
import :sound_mananger;
import :sound_task;
import :sqex_logo_scene;
import :text_manager;


export namespace ctext::hooks {
	void InitialiseHooks() {
		InitialiseDetchmanResourceHooks();
	}

	void EnableHooks() {
		EnableCtrHooks();
		EnableCtrResourceManagerHooks();
		EnableDetchmanResourceHooks();
		EnableFieldImplHooks();
		EnableRenderHooks();
		EnableSoundManagerHooks();
		EnableSoundTaskHooks();
		EnableSqexLogoSceneHooks();

#ifdef FEATURE_VOICE_ACTING
		EnableMsgWindowHooks();
		EnableNameInputSceneHooks();
		EnableTextManagerHooks();
#endif
	}

	void UninitialiseHooks() {
		UninitialiseDetchmanResourceHooks();
	}
}