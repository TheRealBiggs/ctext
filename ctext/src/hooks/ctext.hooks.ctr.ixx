module;

#include "helpers.hpp"

#include <cocos/2d/CCLabel.h>

export module ctext.hooks:ctr;

import ct.addr;
import ctext.config;

import std;

using namespace ct::addr;


namespace {
	std::unordered_map<int, cocos2d::TTFConfig> ttfConfigs;


	cocos2d::TTFConfig& GetTtfConfig(int fontSize) {
		if (!ttfConfigs.contains(fontSize)) {
			auto path = std::filesystem::current_path();
			path /= ctext::Config::Get().FontCustomFont;

			cocos2d::TTFConfig ttfConfig;
			ttfConfig.fontSize = static_cast<float>(fontSize);
			ttfConfig.fontFilePath = path.generic_string();

			ttfConfigs[fontSize] = std::move(ttfConfig);
		}

		return ttfConfigs[fontSize];
	}


	FN_HOOK_A(
		__fastcall, cocos2d::Label*, ctr_CreateLabel,
		CTR_CREATE_LABEL,
		std::string const&, text, int, fontSize
	) {
		const auto& cfg = ctext::Config::Get();

		cocos2d::Label* label = nullptr;

		if (cfg.FontUseCustomFont) {
			const auto& ttfConfig = GetTtfConfig(cfg.FontUseFixedFontSize ? cfg.FontFixedFontSize : fontSize);
			label = cocos2d::Label::create();
			label->setTTFConfig(ttfConfig);
			label->setString(text);
		} else
			label = CALL_ORIG(ctr_CreateLabel, text, cfg.FontUseFixedFontSize ? cfg.FontFixedFontSize : fontSize);

		if (cfg.FontForceNearestFilter)
			label->getFontAtlas()->setAliasTexParameters();

		return label;
	}
}


export namespace ctext::hooks {
	void EnableCtrHooks() {
		const auto& cfg = ctext::Config::Get();

		if (cfg.FontUseCustomFont || cfg.FontUseFixedFontSize || cfg.FontForceNearestFilter)
			ENABLE_FN_HOOK(ctr_CreateLabel);
	}
}