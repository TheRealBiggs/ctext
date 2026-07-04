module;

#include "helpers.hpp"

export module ctext.hooks:field_impl;

import ct;
import ct.addr;
import ctext.config;

using namespace ct;
using namespace ct::addr;


namespace {
	C_FN_HOOK_A(
		void, FieldImpl, UserScrollDiagonal,
		FIELD_IMPL_USER_SCROLL_DIAGONAL,
		int, x, int, y, bool, a3, bool, a4, bool, a5
	) {
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
		if (ctext::Config::Get().FixesRevertDiagonalMovement)
			ENABLE_C_FN_HOOK(FieldImpl, UserScrollDiagonal);
	}
}