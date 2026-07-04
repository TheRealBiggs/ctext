module;

#include "helpers.hpp"

#include <cocos/2d/CCScene.h>

export module ct.scene:scene_manager;

import ct.addr;

import std;

using namespace ct::addr;


export namespace ct::scene {
	class SceneManager final {
	public:
		ACSR(
			bool, isDemoOn,
			SCENE_MANAGER_IS_DEMO_ON
		);
		ACSR(
			int, nowScene,
			SCENE_MANAGER_NOW_SCENE
		);
		ACSR(
			std::vector<cocos2d::Scene*>, sceneStack,
			SCENE_MANAGER_SCENE_STACK
		);

		FN_CC(
			__fastcall, cocos2d::Scene*, create,
			SCENE_MANAGER_CREATE,
			int, id, int, a2
		);
		FN_CC(
			__fastcall, void, NextScene,
			SCENE_MANAGER_NEXT_SCENE,
			int, a1
		);
		FN_CC(
			__fastcall, void, pushScene,
			SCENE_MANAGER_PUSH_SCENE,
			int, id, int, a2
		);
		FN_CC(
			__fastcall, void, popScene,
			SCENE_MANAGER_POP_SCENE
		);
		FN_CC(
			__fastcall, void, popAllScenes,
			SCENE_MANAGER_POP_ALL_SCENES
		);
	};
}