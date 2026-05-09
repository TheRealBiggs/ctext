module;

#include "build_config.hpp"
#include "helpers.hpp"

#include <cocos/2d/CCLayer.h>

export module ctext.hooks:sqexlogo;


#ifdef FEATURE_LOGO_HOOK


namespace {
	HOOK_RET(SqexLogoScene, __cdecl, cocos2d::Layer*) {
		auto scene = new ctext::LogoScene();
		scene->init();
		scene->autorelease();

		return scene;
	}
}


export namespace ctext::hooks {

}


#endif