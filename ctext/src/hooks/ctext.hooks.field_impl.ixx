module;

#include "helpers.hpp"

export module ctext.hooks:field_impl;

import ct;
import ctext.config;


namespace {
	HOOK_CLSFN(FieldImpl_UserScrollDiagonal, ct::FieldImpl, int x, int y, bool a3, bool a4, bool a5) {
		auto* dword854 = _this->dword854;
		dword854[36] = x;
		dword854[37] = y;

		dword854[38] += x;
		dword854[41] += y;

		dword854[40] = dword854[38];
		dword854[43] = dword854[41];
	}
}


export namespace ctext::hooks {
	void EnableFieldImplHooks() {
		if (ctext::Config::Get().RevertDiagonalMovement)
			ENABLE_HOOK(FieldImpl_UserScrollDiagonal, 0x175DA0);
	}
}