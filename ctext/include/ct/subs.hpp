#pragma once

#include "helpers.hpp"

#include <string>


namespace cocos2d {
	class Texture2D;
	class Image;
}


namespace ct {
	ADDR_AS_FUNC(void, __fastcall, sub_297B60, 0x297B60, int, a);	// SceneManager::NextScene
	ADDR_AS_FUNC(cocos2d::Texture2D*, __fastcall, sub_19AC50, 0x19AC50, const std::string&, filename, cocos2d::Image&, image); // ctr::ResourceManager::createTexture
	ADDR_AS_FUNC(void*, __fastcall, sub_19E500, 0x19E500, unsigned int, a1, unsigned int, a2);	// SoundObj::createSound
}