module;

#include "helpers.hpp"

#include <cocos/2d/CCLayer.h>

export module ctext.hooks:sqex_logo_scene;

import ct.addr;
import ctext.config;
import ctext.scenes;

using namespace ct::addr;


namespace {
	FN_HOOK_A(
		__cdecl, cocos2d::Layer*, SqexLogoScene_create,
		SQEX_LOGO_SCENE_CREATE
	) {
		auto scene = new ctext::scenes::LogoScene();
		scene->init();
		scene->autorelease();

		return scene;
	}
}


export namespace ctext::hooks {
	void EnableSqexLogoSceneHooks() {
		ENABLE_FN_HOOK(SqexLogoScene_create);
	}
}