module;

#include "helpers.hpp"

#include <cstdint>

export module ct:chrono_canvas;

import ct.audio;

import std;


export namespace ct {
	class ChronoCanvas {
	public:
		struct UnkStructA {
			uint32_t dword0;
			uint32_t dword4;
			uint32_t dword8;
			uint32_t dwordC;
			uint32_t dword10;
			uint32_t dword14;
			uint32_t dword18;
			uint32_t dword1C;
			uint32_t dword20;
			uint32_t dword24;
			uint32_t dword28;
			uint32_t dword2C;
			uint32_t dword30;
			uint32_t dword34;
			uint32_t dword38;
			uint32_t dword3C;
		};

#pragma pack(push, 1)
		struct UnkStructB {
			uint32_t dword0;
			uint32_t dword4;
			uint32_t dword8;
			uint32_t dwordC;
			uint32_t dword10;
			uint32_t dword14;
			uint32_t dword18;
			uint32_t dword1C;
			uint32_t dword20;
			uint32_t dword24;
			uint32_t dword28;
			uint32_t dword2C;
			uint32_t dword30;
			uint32_t dword34;
			uint32_t dwordarr38[22];
			uint32_t dwordarr90[22];
			uint32_t dwordarrE8[22];
			uint32_t dword140;
			uint32_t dword144;
			uint32_t dword148;
			uint32_t dword14C;
			uint32_t dword150;
			uint32_t dword154;
			uint32_t dword158;
			uint32_t dword15C;
			uint32_t dword160;
			uint32_t dword164;
			uint32_t dword168;
			uint32_t dword16C;
			uint32_t dword170;
			uint64_t qword174;
			uint64_t qword17C;
			uint64_t qword184;
			uint64_t qword18C;
			uint64_t qword194;
			uint64_t qword19C;
			uint64_t qword1A4;
			uint64_t qword1AC;
			uint32_t dword1B4;
		};
#pragma pack(pop)

		struct UnkStructC {
			uint8_t gap[256];
		};

#pragma pack(push, 1)
		struct UnkStructD {
			uint32_t dwordarr0[19];
			uint32_t interfaceType;
			uint32_t dwordarr4C[12];
		};
#pragma pack(pop)


		static ChronoCanvas* getInstance() {
			return *ADDR_AS(ChronoCanvas**, 0x41B4C4);
		}


		audio::SoundManager soundManager;
		uint32_t dword24;
		uint8_t gap1[6368];
		std::string defaultCharacterNames[7];
		uint8_t gap2[6];
		__declspec(align(1)) uint32_t dword19B6;
		uint8_t gap3[19934];
		uint32_t dword6798;
		uint8_t gap4[240];
		uint32_t dword688C;
		uint8_t gap5[16];
		uint32_t dword68A0;
		uint8_t gap6[22695];
		UnkStructA usb_a_arrC14C[1];
		uint8_t gap77[10175];
		uint8_t gap7[5202];
		uint32_t dwordFDA0;
		uint8_t gap88[3032];
		uint8_t byte10980;
		uint8_t gap8[3];
		bool bool10980;
		uint8_t gap9999[3];
		uint8_t byte10984;
		uint8_t gap999[3];
		uint8_t byte10988;
		uint8_t gap99[7];
		uint32_t dword10990;
		uint32_t dword10994;
		uint8_t gap_0[16];
		int int109A8;
		int int109AC;
		int int109B0;
		uint8_t gap9[1488];
		uint8_t byte10F84;
		uint8_t gapA[1];
		uint16_t word10F86;
		uint8_t gapB[72];
		uint32_t dword10FD0;
		uint8_t gapC[56];
		uint32_t dword1100C;
		uint8_t gapD[56];
		uint32_t dword11048;
		uint8_t gapE[100];
		uint32_t dword110B0;
		uint8_t gapF[332];
		uint32_t dword11200;
		uint8_t gapG[3772];
		int currentFieldId;
		uint8_t gapH[88];
		uint8_t byte1211C;
		uint8_t gapI[7];
		uint32_t dword12124;
		uint8_t gapJ[4220];
		uint8_t byte131A4;
		uint8_t gapK[167];
		int activePartyMemberIds[3];
		int inactivePartyMemberIds[4];
		uint8_t gapL[20];
		uint32_t dword1327C;
		uint8_t gapM[728];
		uint32_t dword13558;
		uint8_t gapN[2612];
		UnkStructD configMaybe;
		uint8_t gapO[84];
		uint32_t dword14064;
		uint8_t gapP[6968];
		uint32_t dword15BA0;
		uint8_t gapQ[28364];
		uint32_t dword1CA70;
		uint8_t gapR[56];
		UnkStructA usb_a1CAB0;
		uint8_t gapS[84];
		UnkStructB usb_b1CB40;
		UnkStructC* usbp1CCF8;
		uint8_t gap[12];
	};
}