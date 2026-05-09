#include "build_config.hpp"


#ifdef FEATURE_LOGO_HOOK


#include "hooks/sqexlogo_hook.hpp"

#include "helpers.hpp"
#include "scenes/logo_scene.hpp"

#include "mod_api/mod_api_impl.hpp"
#include "mod_api/scene_manager_impl.hpp"
#include "mod_api/node_impl.hpp"

#include <cocos/cocos2d.h>
#include <MinHook.h>


namespace {
	typedef void* (__cdecl* SqexLogoScene__create)();


	SqexLogoScene__create origSqexLogoScene__create = nullptr;


	void* __cdecl hookSqexLogoScene__create() {
		auto scene = new ctext::LogoScene();
		scene->init();
		scene->autorelease();

		return scene;
	}
}


void EnableSqexLogoHook() {
	void* target = ADDR_AS(SqexLogoScene__create, 0x2CC3C0);

	auto res = MH_CreateHook(target, &hookSqexLogoScene__create, (LPVOID*)&origSqexLogoScene__create);
	res = MH_EnableHook(target);
}


#endif