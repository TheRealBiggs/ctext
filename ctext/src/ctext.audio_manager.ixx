module;

#include <miniaudio.h>
#include <cstdint>

export module ctext.audio_manager;

import ctext.singleton;

import std;


export namespace ctext {
	class AudioManager final : public Singleton<AudioManager> {
	public:
		AudioManager() {
			engine = new ma_engine();
			ma_engine_init(nullptr, engine);
		}

		~AudioManager() {
			ma_engine_uninit(engine);
			delete engine;
		}

		int PlayOneShot(const std::string& filepath) {
			auto* sound = BorrowSound();

			if (!InitialiseSoundFromFile(sound, filepath))
				return -1;			

			auto id = nextSoundId++;

			SetupEndCallback(sound, id);

			if (!StartSound(sound))
				return -1;

			activeSounds[id] = sound;

			return id;
		}

		int PlayOneShot(const uint8_t* data, size_t dataLen) {
			auto* sound = BorrowSound();

			if (!InitialiseSoundFromData(sound, data, dataLen))
				return -1;

			auto id = nextSoundId++;

			SetupEndCallback(sound, id);

			if (!StartSound(sound))
				return -1;

			activeSounds[id] = sound;

			return id;
		}

		int PlayLooping(const std::string& filepath, uint64_t loopStart, uint64_t loopEnd) {
			auto* sound = BorrowSound();

			if (!InitialiseSoundFromFile(sound, filepath))
				return -1;

			if (!SetupSoundLoop(sound, loopStart, loopEnd))
				return -1;

			if (!StartSound(sound))
				return -1;
			
			auto id = nextSoundId++;

			activeSounds[id] = sound;

			return id;
		}

		int PlayLooping(const uint8_t* data, size_t dataLen, uint64_t loopStart, uint64_t loopEnd) {
			auto* sound = BorrowSound();

			if (!InitialiseSoundFromData(sound, data, dataLen))
				return -1;

			if (!SetupSoundLoop(sound, loopStart, loopEnd))
				return -1;

			if (!StartSound(sound))
				return -1;

			auto id = nextSoundId++;

			activeSounds[id] = sound;

			return id;
		}

		void Stop(int id) {
			if (!activeSounds.contains(id))
				return;

			auto* sound = activeSounds[id];
			ma_sound_stop(sound);

			activeSounds.erase(id);
			soundPool.push_back(sound);
		}

		void SetVolume(int id, float volume) {
			if (!activeSounds.contains(id))
				return;

			ma_sound_set_volume(activeSounds[id], volume);
		}

		int GetTime(int id) {
			if (!activeSounds.contains(id))
				return -1;

			return static_cast<int>(ma_sound_get_time_in_pcm_frames(activeSounds[id]));
		}

		bool IsPlaying(int id) {
			if (!activeSounds.contains(id))
				return false;

			return ma_sound_is_playing(activeSounds[id]);
		}


	private:
		inline ma_sound* BorrowSound() {
			ma_sound* sound;

			if (!soundPool.empty()) {
				sound = soundPool.front();
				soundPool.pop_front();

				ma_sound_uninit(sound);
				sound->pEndCallbackUserData = nullptr;
				sound->endCallback = nullptr;
			} else
				sound = new ma_sound;

			return sound;
		}

		inline bool InitialiseSoundFromFile(ma_sound* sound, const std::string& filepath) {
			auto res = ma_sound_init_from_file(engine, filepath.c_str(), 0, nullptr, nullptr, sound);

			if (res != ma_result::MA_SUCCESS) {
				soundPool.push_back(sound);

				return false;
			}

			return true;
		}

		inline bool InitialiseSoundFromData(ma_sound* sound, const uint8_t* data, size_t dataLen) {
			auto* decoder = new ma_decoder;
			auto res = ma_decoder_init_memory(data, dataLen, nullptr, decoder);

			if (res != ma_result::MA_SUCCESS)
				return false;

			res = ma_sound_init_from_data_source(engine, decoder, 0, nullptr, sound);

			if (res != ma_result::MA_SUCCESS) {
				soundPool.push_back(sound);

				return false;
			}

			return true;
		}

		inline void SetupEndCallback(ma_sound* sound, uint32_t id) {
			sound->pEndCallbackUserData = reinterpret_cast<void*>(id);
			sound->endCallback = [](void* userData, ma_sound* sound) {
				auto id = reinterpret_cast<uint32_t>(userData);

				AudioManager::Get().activeSounds.erase(id);
				AudioManager::Get().soundPool.push_back(sound);
			};
		}

		inline bool SetupSoundLoop(ma_sound* sound, uint64_t loopStart, uint64_t loopEnd) {
			if (loopStart != -1) {
				auto* source = ma_sound_get_data_source(sound);

				if (loopEnd == -1) {
					ma_uint64 length;
					auto res = ma_data_source_get_length_in_pcm_frames(source, &length);

					if (res != ma_result::MA_SUCCESS) {
						ma_sound_uninit(sound);
						soundPool.push_back(sound);

						return false;
					}

					loopEnd = length;
				}

				auto res = ma_data_source_set_loop_point_in_pcm_frames(source, loopStart, loopEnd);

				if (res != ma_result::MA_SUCCESS) {
					ma_sound_uninit(sound);

					return false;
				}
			}

			ma_sound_set_looping(sound, true);

			return true;
		}

		inline bool StartSound(ma_sound* sound) {
			auto res = ma_sound_start(sound);

			if (res != ma_result::MA_SUCCESS) {
				soundPool.push_back(sound);

				return false;
			}

			return true;
		}


		ma_engine* engine;

		std::atomic<uint32_t> nextSoundId = 0;
		std::deque<ma_sound*> soundPool;
		std::unordered_map<uint32_t, ma_sound*> activeSounds;
	};
}