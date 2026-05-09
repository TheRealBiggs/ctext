module;

#include "helpers.hpp"

#include <cocos/2d/CCScene.h>

export module ct.scene:scene_manager;

import std;


export namespace ct::scene {
	class SceneManager final {
	public:
		ADDR_AS_STATIC_ACCESSOR(bool, isDemoOn, 0x41BDD7);
		ADDR_AS_STATIC_ACCESSOR(int, nowScene, 0x41C3E8);
		ADDR_AS_STATIC_ACCESSOR(std::vector<cocos2d::Scene*>, sceneStack, 0x41F994);

		static ADDR_AS_FUNC(cocos2d::Scene*, __fastcall, create, 0x297860, int, id, int, a2);
		static ADDR_AS_FUNC(void, __fastcall, NextScene, 0x297B60, int, a1);
		static ADDR_AS_FUNC(void, __fastcall, pushScene, 0x298410, int, id, int, a2);
		static ADDR_AS_FUNC(void, __fastcall, popScene, 0x298470);
		static ADDR_AS_FUNC(void, __fastcall, popAllScenes, 0x2984E0);
	};
}