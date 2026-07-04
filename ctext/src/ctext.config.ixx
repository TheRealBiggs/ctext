module;

#include <nlohmann/json.hpp>

export module ctext.config;

import ctext.singleton;

import std;


export namespace ctext {
	class Config final : public Singleton<Config> {
		friend class Singleton<Config>;


	public:
		bool FixesRevertDiagonalMovement;
		bool FixesFixBgmResumeAfterBattle;

		bool GraphicsForceNearestFilter;

		bool FontForceNearestFilter;
		bool FontUseCustomFont;
		std::string FontCustomFont;
		bool FontUseFixedFontSize;
		int FontFixedFontSize;

		bool MiscDisableFieldActionIndicator;

		bool ModsEnabled;
		bool ModsEnableCtpLoading;
		std::vector<std::string> ModsLoadOrder;


	private:
		Config() {
			std::ifstream file("ctext.json");
			auto cfg = nlohmann::json::parse(file, nullptr, true, true, true);

			FixesRevertDiagonalMovement = cfg["fixes"]["revert_diagonal_movement"];
			FixesFixBgmResumeAfterBattle = cfg["fixes"]["fix_bgm_resume_after_battle"];

			GraphicsForceNearestFilter = cfg["graphics"]["force_nearest_filter"];

			FontForceNearestFilter = cfg["font"]["force_nearest_filter"];
			FontUseCustomFont = cfg["font"]["use_custom_font"];
			FontCustomFont = cfg["font"]["custom_font"];
			FontUseFixedFontSize = cfg["font"]["use_fixed_font_size"];
			FontFixedFontSize = cfg["font"]["fixed_font_size"];

			MiscDisableFieldActionIndicator = cfg["misc"]["disable_field_action_indicator"];

			ModsEnabled = cfg["mods"]["enabled"];
			ModsEnableCtpLoading = cfg["mods"]["enable_ctp_loading"];
			ModsLoadOrder = cfg["mods"]["load_order"];

			file.close();
		}
	};
}