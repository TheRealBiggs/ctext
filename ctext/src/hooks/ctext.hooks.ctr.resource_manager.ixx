module;

#include "helpers.hpp"

#include <cocos/platform/CCImage.h>

export module ctext.hooks:ctr.resource_manager;

import ctext.config;

import std;


namespace {
	HOOK_RET(ctr_ResourceManager_createTexture, __fastcall, cocos2d::Texture2D*, std::string* filename, cocos2d::Image* image) {
		auto* res = CALL_ORIG(ctr_ResourceManager_createTexture, filename, image);

		if (res != nullptr)
			res->setTexParameters({ GL_NEAREST, GL_NEAREST, GL_CLAMP, GL_CLAMP });

		return res;
	}
}


namespace ctext::hooks {
	void EnableCtrResourceManagerHooks() {
		if (ctext::Config::Get().GraphicsForceNearestFilter)
			ENABLE_HOOK(ctr_ResourceManager_createTexture, 0x19AC50);
	}
}