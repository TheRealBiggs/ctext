module;

#include <cocos/base/ccTypes.h>
#include <cocos/renderer/CCGLProgramState.h>

export module ct:field_impl;


export namespace ct {
	struct Battle;
	struct FieldMap;
	struct MsgWindow;
	struct UnkStructA;
	struct UnkStructB;


	class FieldImpl {
	public:
		UnkStructA* usa0;
		unsigned char gap0[60];
		UnkStructB* usb40;
		unsigned int dword44;
		unsigned char gap1[2056];
		unsigned int* dword850;
		int* dword854;
		unsigned int* dword858;
		unsigned int dword85C;
		unsigned char gap2[8];
		unsigned int dword868;
		unsigned char bytearr[256];
		unsigned char gap3[512];
		unsigned char byteB6C;
		unsigned char gap4[3];
		unsigned int dwordB70;
		unsigned char byteB74;
		unsigned char gapp[3];
		unsigned int dwordB78;
		unsigned int dwordB7C;
		unsigned int dwordB80;
		unsigned int dwordB84;
		unsigned char gap5[8];
		unsigned char byteB90;
		unsigned char gap6[11];
		FieldMap* fieldMap;
		unsigned int dwordBA0;
		unsigned char gap7[20];
		unsigned int dwordBB8;
		unsigned int dwordBBC;
		unsigned short wordBC0;
		unsigned char gap8[2];
		unsigned int dwordBC4;
		unsigned int dwordBC8;
		unsigned int dwordBCC;
		unsigned short wordBD0;
		unsigned char gap9[2];
		unsigned int dwordBD4;
		unsigned int dwordBD8;
		unsigned int dwordBDC;
		unsigned short wordBE0;
		unsigned char byteBE2;
		unsigned char byteBE3;
		unsigned int dwordBE4;
		unsigned int dwordBE8;
		unsigned int dwordBEC;
		unsigned int dwordBF0;
		unsigned int dwordBF4;
		unsigned char dwordBF8;
		unsigned char gapA[3];
		MsgWindow* msgWindow;
		Battle* battle;
		unsigned int dwordC04;
		BYTE gapB[4];
		cocos2d::GLProgramState* glProgStateC0C;
		cocos2d::Texture2D* texC10;
		void* tex1DataC14;
		BYTE gapC[8];
		BYTE gapD[4];
		cocos2d::GLProgramState* glProgStateC24;
		cocos2d::Texture2D* texC28;
		void* tex1DataC2C;
		BYTE gapE[8];
		unsigned int dwordC38;
		unsigned int dwordC3C;
		float secondsPerFrameC40;
		float floatC44;
		float floatC48;
		float floatC4C;
		float floatC50;
		unsigned char gapF[32];
		unsigned short wordC74;
		unsigned char byteC76;
		cocos2d::Color4B colorC77;
		unsigned char gap10[8];
		unsigned int dwordC84;
		unsigned char gap11[420];
		unsigned int dwordE2C;
		unsigned int dwordE30;
		unsigned int dwordE34;
		unsigned int dwordE38;
		unsigned int dwordE3C;
		unsigned int dwordE40;
		unsigned int dwordE44;
		unsigned int dwordE48;
		unsigned int dwordE4C;
		unsigned int dwordE50;
		unsigned int dwordE54;
		unsigned int dwordE58;
		unsigned int dwordE5C;
		unsigned int dwordE60;
		unsigned int dwordE64;
		unsigned int dwordE68;
		unsigned int dwordE6C;
		unsigned int dwordE70;
		unsigned int dwordE74;
		unsigned int dwordE78;
		unsigned int dwordE7C;
		unsigned int dwordE80;
		unsigned int dwordE84;
	};
}