module;

#include "helpers.hpp"

export module ctext.hooks:msg_window;

import ct.addr;
import ct.ui;
import ctext.voice_acting_manager;

using namespace ct::addr;
using namespace ct::ui;


namespace {
	C_FN_HOOK_A(
		void, MsgWindow, Close,
		MSG_WINDOW_CLOSE,
		bool, a2
	) {
		ctext::VoiceActingManager::Get().Stop();

		C_CALL_ORIG(a2);
	}

	C_FN_HOOK_A(
		void, MsgWindow, setup,
		MSG_WINDOW_SETUP
	) {
		ctext::VoiceActingManager::Get().PlayNextPage();

		C_CALL_ORIG();
	}
}


export namespace ctext::hooks {
	void EnableMsgWindowHooks() {
		ENABLE_C_FN_HOOK(MsgWindow, Close);
		ENABLE_C_FN_HOOK(MsgWindow, setup);
	}
}