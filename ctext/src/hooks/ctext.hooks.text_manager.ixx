module;

#include "helpers.hpp"

export module ctext.hooks:text_manager;

import ct;
import ct.addr;
import ctext.voice_acting_manager;

import std;

using namespace ct;
using namespace ct::addr;


namespace {
	C_FN_HOOK_A(
		std::string*, TextManager, getMsg,
		TEXT_MANAGER_GET_MSG,
		std::string*, res, int, msgFileId, int, msgId
	) {
		auto dialogue = C_CALL_ORIG(res, msgFileId, msgId);

		ctext::VoiceActingManager::Get().Setup(msgFileId, msgId, *dialogue);	

		return dialogue;
	}
}


export namespace ctext::hooks {
	void EnableTextManagerHooks() {
		ENABLE_C_FN_HOOK(TextManager, getMsg);
	}
}