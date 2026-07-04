module;

#include "helpers.hpp"

#include <cocos/renderer/CCTexture2D.h>

export module ct.ctr:resource_manager;

import ct.addr;

using namespace ct::addr;


export namespace ct::ctr {
	class ResourceManager {
	public:
		FN_CC(
			__fastcall, cocos2d::Texture2D*, createTexture,
			CTR_RESOURCE_MANAGER_CREATE_TEXTURE,
			std::string*, filename, cocos2d::Image*, image
		);
	};
}