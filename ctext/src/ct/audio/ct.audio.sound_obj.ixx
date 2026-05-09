module;

#include <cstdint>

export module ct.audio:sound_obj;


export namespace ct::audio {
	class SoundObj {
	public:
		enum class SoundType {
			BGM,
			SE_1,
			SE_2
		};
		

		int id;
		uint32_t dword4;
		uint32_t dwordarr8[2];
		SoundType type;
		bool isOneShot;
		uint32_t volume;
		uint8_t* data;
		size_t dataLength;
		uint8_t gap[4];
	};
}