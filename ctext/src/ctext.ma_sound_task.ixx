module;

#include "helpers.hpp"

export module ctext.ma_sound_task;

import ct;
import ct.audio;
import ctext.audio_manager;


export namespace ctext {
	class MASoundTask final : public ct::audio::SoundTask {
	public:
		MASoundTask(uint32_t id) : ct::audio::SoundTask(id) {
			
		}

		virtual ~MASoundTask() override {

		}


		virtual void init(ct::audio::SoundObj* sound, int a2) override {
			this->sound = sound;
			this->int8 = a2;
			this->dword10 = 1;
		}

		virtual void dispose() override {
			sound = nullptr;

			ctext::AudioManager::Get().Stop(maId);

			isPlaying = false;
			isPaused = false;
			isStopped = true;
		}

		virtual void update() override {
			if (!ctext::AudioManager::Get().IsPlaying(maId)) {
				isPlaying = false;
				isPaused = false;
				isStopped = true;
			}
		}

		virtual void play(float value) override {
			if (isPlaying)
				return;

			if (sound->isOneShot)
				maId = ctext::AudioManager::Get().PlayOneShot(sound->data, sound->dataLength);
			else
				maId = ctext::AudioManager::Get().PlayLooping(sound->data, sound->dataLength, value);

			isPlaying = true;
			isPaused = false;
			isStopped = false;
		}

		virtual void stop() override {
			if (sound->type == ct::audio::SoundObj::SoundType::BGM) {
				if (sound->id == 0x45)
					ct::audio::resumePrevBgm = true;
				else {
					ct::audio::prevBgmId = sound->id;
					ct::audio::prevBgmTime = getCurrentTime();
				}
			}

			ctext::AudioManager::Get().Stop(maId);

			isPlaying = false;
			isPaused = false;
			isStopped = true;
		}

		virtual void pause() override {
			isPlaying = false;
			isPaused = true;
			isStopped = false;
		}

		virtual void setPitch(float value) override {
			LOG_DEBUG("SoundTask::setPitch()");
		}

		virtual void setVolume(float value) override {
			volume = value;

			auto* cc = ct::ChronoCanvas::getInstance();

			value = cc->soundManager.masterVolume / 100.0f * value;

			if (sound->type == ct::audio::SoundObj::SoundType::BGM) {
				value = cc->soundManager.bgmVolume / 100.0f * value;
				value = cc->soundManager.masterBGMVolume / 100.0f * value;
			} else {
				value = cc->soundManager.bgmVolume / 100.0f * value;
				value = cc->soundManager.masterBGMVolume / 100.0f * value;
			}

			ctext::AudioManager::Get().SetVolume(maId, value);
		}

		virtual void updateVolume() override {
			setVolume(volume);
		}

		virtual float getCurrentTime() override {
			return ctext::AudioManager::Get().GetTime(maId);
		}


	private:
		int maId;
	};
}