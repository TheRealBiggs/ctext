module;

#include "helpers.hpp"

export module ctext.hooks:name_input_scene;

import ct.addr;
import ct.scene;

using namespace ct::addr;
using namespace ct::scene;


namespace {
	C_FN_HOOK_A(
		void, NameInputScene, update,
		NAME_INPUT_SCENE_UPDATE,
		float, delta
	) {
		SceneManager::popScene();
	}
}


export namespace ctext::hooks {
	void EnableNameInputSceneHooks() {
		ENABLE_C_FN_HOOK(NameInputScene, update);
	}
}