module;

#include <quickjs/quickjs.h>

export module ctext.script_manager;

import ctext.singleton;


export namespace ctext {
	class ScriptManager final : public Singleton<ScriptManager> {
		friend class Singleton<ScriptManager>;


	public:



	private:
		ScriptManager() {

		}
	};
}