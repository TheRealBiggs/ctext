module;

#include <cstdint>

export module ct.audio:sound_task;

import :sound_obj;


export namespace ct::audio {
	class SoundTask {
	public:
		inline SoundTask(uint32_t id)
			: id(id), int8(-1), sound(nullptr), dword10(0), isPlaying(false), isPaused(false), isStopped(false),
			  byte17(0) {

		}

		virtual ~SoundTask() {
		
		};

		virtual void init(ct::audio::SoundObj* sound, int a2) = 0;
		virtual void dispose() = 0;
		virtual void update() = 0;
		virtual void play(float a1) = 0;
		virtual void stop() = 0;
		virtual void pause() = 0;
		virtual void setPitch(float a1) = 0;
		virtual void setVolume(float a1) = 0;
		virtual void updateVolume() = 0;
		virtual float getCurrentTime() = 0;


		uint32_t id;
		int int8;
		SoundObj* sound;
		uint32_t dword10;
		bool isPlaying;
		bool isPaused;
		bool isStopped;
		uint8_t byte17;
		uint8_t gap[8];
		float volume;
	};
}