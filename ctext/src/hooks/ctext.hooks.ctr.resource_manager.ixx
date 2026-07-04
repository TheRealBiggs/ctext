module;

#include "helpers.hpp"

#include <cocos/platform/CCImage.h>

export module ctext.hooks:ctr.resource_manager;

import ct.addr;
import ctext.config;

import std;

using namespace ct::addr;


namespace {
	FN_HOOK_A(
		__fastcall, cocos2d::Texture2D*, ctr_ResourceManager_createTexture,
		CTR_RESOURCE_MANAGER_CREATE_TEXTURE,
		std::string*, filename, cocos2d::Image*, image
	) {
		auto* res = CALL_ORIG(ctr_ResourceManager_createTexture, filename, image);

		if (res != nullptr)
			res->setTexParameters({ GL_NEAREST, GL_NEAREST, GL_CLAMP, GL_CLAMP });

		return res;
	}
}


namespace ctext::hooks {
	void EnableCtrResourceManagerHooks() {
		if (ctext::Config::Get().GraphicsForceNearestFilter)
			ENABLE_FN_HOOK(ctr_ResourceManager_createTexture);
	}
}