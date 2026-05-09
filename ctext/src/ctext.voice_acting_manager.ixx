module;

#include "helpers.hpp"

#include <cstdint>
#include <cstring>
#include <ranges>

export module ctext.voice_acting_manager;

import ct;
import ctext.singleton;
import ctext.audio_manager;

import std;

using namespace std::literals;


namespace {
	static const char* KEY_PREFIXES[] = {
		"CMES0", "CMES1", "CMES2", "CMES3", "CMES4", "CMES5",
		"KMES0", "KMES1", "KMES2",
		"MESI0",
		"MESK0", "MESK1", "MESK2", "MESK3", "MESK4",
		"MESS0",
		"MEST0", "MEST1", "MEST2", "MEST3", "MEST4", "MEST5",
		"MSG01", "MSG02", "MSG03", "MSG04",
		"EXMS0", "EXMS1", "EXMS2", "EXMS3",
		"QUES0",
		"STAF",
		"COMU0",
	};

	static const char* CHARACTER_NAMES[] = {
		"crono", "marle", "lucca", "robo", "frog", "ayla", "magus"
	};
}


export namespace ctext {
	class VoiceActingManager final : public Singleton<VoiceActingManager> {
	public:
		void Setup(int msgFileId, int msgId, const std::string& dialogue) {
			if (msgFileId < 27 || msgFileId > 59)
				return;

			Stop();

			currentTxtFileId = msgFileId;
			currentTxtKey = msgId;

			auto* cc = ct::ChronoCanvas::getInstance();

			// Get speaker
			int i = 0;

			if (dialogue._Starts_with("<NAME_PT")) {
				auto partyIndex = dialogue[8] - '1';
				auto charId = cc->activePartyMemberIds[partyIndex];
				speakerId = charId;

				i = 8;
			}

			// Generate page filenames
			auto pages = std::views::split(dialogue, "<PAGE>"sv);
			auto j = 0;

			for (const auto page : pages) {
				std::string_view view(page.data());
				int o = 0;
				char suffix[260];
				suffix[0] = '\0';

				if (speakerId != -1) {
					auto charName = CHARACTER_NAMES[speakerId];

					strcat_s(suffix, "_");
					strcat_s(suffix, charName);
				}

				while ((o = view.find("<NAME_PT", i)) != std::string::npos) {
					auto partyIndex = view[o + 8] - '1';
					auto charId = cc->activePartyMemberIds[partyIndex];
					auto charName = CHARACTER_NAMES[charId];

					strcat_s(suffix, "_");
					strcat_s(suffix, charName);

					i = o + 8;
				}

				i = 0;

				// TODO: Replace with `std::format()`
				char path[260];
				sprintf_s(path, "voice/FLD_%s_%03d_page%d%s.mp3", KEY_PREFIXES[msgFileId - 27], msgId, j++ + 1, suffix);

				pageNames.push_back(path);
			}

			LOG_DEBUG("VA_HOOK: " << pageNames[0].c_str());
		}

		void PlayNextPage() {
			ctext::AudioManager::Get().Stop(currentSoundId);

			if (currentPage >= pageNames.size())
				return;

			auto& path = pageNames[currentPage++];

			LOG_DEBUG("VA_HOOK: " <<  path.c_str());

			if (std::filesystem::exists(path))
				currentSoundId = ctext::AudioManager::Get().PlayOneShot(path.c_str());
		}

		void Stop() {
			ctext::AudioManager::Get().Stop(currentSoundId);

			currentTxtFileId = -1;
			currentTxtKey = -1;
			currentPage = 0;
			speakerId = -1;
			pageNames.clear();
		}


	private:
		int currentTxtFileId = -1;
		int currentTxtKey = -1;
		unsigned int currentPage = 0;
		int speakerId = -1;

		uint32_t currentSoundId;

		std::vector<std::string> pageNames;
	};
}