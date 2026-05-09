module;

#include "helpers.hpp"

export module ctext.hooks:name_input_scene;

import ct.scene;


namespace {
	HOOK_CLSFN(NameInputScene_update, ct::scene::NameInputScene, float delta) {
		ct::scene::SceneManager::popScene();
	}
}


export namespace ctext::hooks {
	void EnableNameInputSceneHooks() {
		ENABLE_HOOK(NameInputScene_update, 0x2C2C50);
	}
}