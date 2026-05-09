module;

#include "helpers.hpp"

export module ct.input:virtual_controller;


export namespace ct::input {
	class VirtualController {
	public:
		enum Actions {
			CONTROLLER_ACTION_X		= 1 << 0,
			CONTROLLER_ACTION_START	= 1 << 1,
			CONTROLLER_ACTION_UNK	= 1 << 2,
			CONTROLLER_ACTION_A		= 1 << 3,
			CONTROLLER_ACTION_R		= 1 << 4,
			CONTROLLER_ACTION_L		= 1 << 5,
			CONTROLLER_ACTION_Y		= 1 << 6,
			CONTROLLER_ACTION_B		= 1 << 7,
			CONTROLLER_ACTION_RIGHT = 1 << 8,
			CONTROLLER_ACTION_LEFT	= 1 << 9,
			CONTROLLER_ACTION_DOWN	= 1 << 10,
			CONTROLLER_ACTION_UP	= 1 << 11
		};


		static VirtualController* getInstance() {
			auto* instance = *ADDR_AS(VirtualController**, 0x3FB30C);

			if (instance == nullptr)
				instance = ADDR_AS(VirtualController*, 0x41C3DC);

			return instance;
		}

		static void setInstance(VirtualController* instance) {
			*ADDR_AS(VirtualController**, 0x3FB30C) = instance;
		}


		virtual ~VirtualController() = 0;

		virtual Actions getKey() = 0;
		virtual int getKeyTrg() = 0;
		virtual int getKeyRelease() = 0;
		virtual int getKeyRepeat() = 0;
		virtual void Clear() = 0;
		virtual void RepeatClear() = 0;
		virtual bool isConnected() = 0;
		virtual void setEnableCancelKey(bool) = 0;
	};
}