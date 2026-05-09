module;

#include "helpers.hpp"

export module ctext.hooks:msg_window;

import ct.ui;
import ctext.voice_acting_manager;


namespace {
	HOOK_CLSFN(MsgWindow_Close, ct::ui::MsgWindow, bool a2) {
		ctext::VoiceActingManager::Get().Stop();

		CALL_ORIG(MsgWindow_Close, _this, a2);
	}

	HOOK_CLSFN(MsgWindow_setup, ct::ui::MsgWindow) {
		ctext::VoiceActingManager::Get().PlayNextPage();

		CALL_ORIG(MsgWindow_setup, _this);
	}
}


export namespace ctext::hooks {
	void EnableMsgWindowHooks() {
		ENABLE_HOOK(MsgWindow_Close, 0x195C70);
		ENABLE_HOOK(MsgWindow_setup, 0x195E30);
	}
}