export module ct.audio;

export import :sound_manager;
export import :sound_obj;
export import :sound_task;


export namespace ct::audio {
	bool resumePrevBgm = false;
	int prevBgmId = 0;
	float prevBgmTime = 0;
}