module;

#include <cstdint>

export module ct.audio:sound_manager;

import :sound_task;

import std;


export namespace ct::audio {
	class SoundManager {
	public:
		std::list<SoundTask*> tasks;
		uint32_t nextSoundTaskId;
		int masterVolume;
		int masterBGMVolume;
		int masterSEVolume;
		int bgmVolume;
		int seVolume;
		uint8_t byte20;
	};
}