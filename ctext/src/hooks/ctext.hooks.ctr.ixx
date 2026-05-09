module;

#include "helpers.hpp"

#include <cocos/2d/CCLabel.h>

export module ctext.hooks:ctr;

import ctext.config;

import std;


namespace {
	std::unordered_map<int, cocos2d::TTFConfig> ttfConfigs;


	cocos2d::TTFConfig& GetTtfConfig(int fontSize) {
		if (!ttfConfigs.contains(fontSize)) {
			auto path = std::filesystem::current_path();
			path /= ctext::Config::Get().CustomFont;

			cocos2d::TTFConfig ttfConfig;
			ttfConfig.fontSize = static_cast<float>(fontSize);
			ttfConfig.fontFilePath = path.generic_string();

			ttfConfigs[fontSize] = std::move(ttfConfig);
		}

		return ttfConfigs[fontSize];
	}


	HOOK_RET(ctr_CreateLabel, __fastcall, cocos2d::Label*, std::string const& text, int fontSize) {
		const auto& cfg = ctext::Config::Get();

		cocos2d::Label* label = nullptr;

		if (cfg.UseCustomFont) {
			const auto& ttfConfig = GetTtfConfig(cfg.UseFixedFontSize ? cfg.FixedFontSize : fontSize);
			label = cocos2d::Label::create();
			label->setTTFConfig(ttfConfig);
			label->setString(text);
		} else
			label = CALL_ORIG(ctr_CreateLabel, text, cfg.UseFixedFontSize ? cfg.FixedFontSize : fontSize);

		if (cfg.ForceNearestFilter)
			label->getFontAtlas()->setAliasTexParameters();

		return label;
	}
}


export namespace ctext::hooks {
	void EnableCtrHooks() {
		ENABLE_HOOK(ctr_CreateLabel, 0xFA90);
	}
}