module;

#include <nlohmann/json.hpp>

export module ctext.config;

import ctext.singleton;

import std;


export namespace ctext {
	class Config final : public Singleton<Config> {
	public:
		void Initialise() {
			std::ifstream file("ctext.json");
			auto cfg = nlohmann::json::parse(file, nullptr, true, true, true);

			RevertDiagonalMovement = cfg["fixes"]["revert_diagonal_movement"];

			ForceNearestFilter = cfg["font"]["force_nearest_filter"];
			UseCustomFont = cfg["font"]["use_custom_font"];
			CustomFont = cfg["font"]["custom_font"];
			UseFixedFontSize = cfg["font"]["use_fixed_font_size"];
			FixedFontSize = cfg["font"]["fixed_font_size"];

			ModLoadOrder = cfg["mods"]["load_order"];

			file.close();
		}


		bool RevertDiagonalMovement;

		bool ForceNearestFilter;
		bool UseCustomFont;
		std::string CustomFont;
		bool UseFixedFontSize;
		int FixedFontSize;

		std::vector<std::string> ModLoadOrder;
	};
}