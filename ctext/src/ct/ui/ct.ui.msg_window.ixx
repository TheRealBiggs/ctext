module;

#include <cstdint>

export module ct.ui:msg_window;


export namespace ct::ui {
	class MsgWindow {
	public:
		uint8_t gap0[0x2C0];
		int currentLineNoMaybe;
		int pageStartLineNoMaybe;
	};
}