module;

#include "helpers.hpp"

export module ctext.hooks:text_manager;

import ct;
import ctext.voice_acting_manager;

import std;


namespace {
	HOOK_CLSFN_RET(TextManager__getMsg, std::string*, ct::TextManager, std::string* res, int msgFileId, int msgId) {
		auto dialogue = CALL_ORIG(TextManager__getMsg, _this, res, msgFileId, msgId);

		ctext::VoiceActingManager::Get().Setup(msgFileId, msgId, *dialogue);	

		return dialogue;
	}
}


export namespace ctext::hooks {
	void EnableTextManagerHooks() {
		ENABLE_HOOK(TextManager__getMsg, 0x1B92D0);
	}
}