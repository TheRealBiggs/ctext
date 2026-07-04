module;

#include "helpers.hpp"

export module ctext.hooks:render;

import ct.addr;
import ctext.config;


namespace {
	FN_HOOK_A(
		__fastcall, void, DrawExclamationMark,
		ct::addr::DRAW_EXCLAMATION_MARK,
		int, x, int, y/*, int, spriteIdx*/
	) {
		// Do nothing
	}
}


export namespace ctext::hooks {
	void EnableRenderHooks() {
		if (ctext::Config::Get().MiscDisableFieldActionIndicator)
			ENABLE_FN_HOOK(DrawExclamationMark);
	}
}