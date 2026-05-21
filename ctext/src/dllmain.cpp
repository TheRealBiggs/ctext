#include <MinHook.h>

#include <cstdio>

#include <Windows.h>

import ctext.hooks;
import ctext.config;


// For DisableThreadLibraryCalls, LoadLibrary, GetSystemDirectory
#pragma comment(lib, "kernel32.lib")

#pragma comment(lib, "lib/libcocos2d.lib")


void* baseAddress;


#ifdef ENABLE_LOGGING 

void CreateDebugConsole() {
	AllocConsole();
	FILE* _;
	freopen_s(&_, "CONOUT$", "w", stdout);
	freopen_s(&_, "CONOUT$", "w", stderr);
}

void DestroyDebugConsole() {
	FreeConsole();
}

#else

#define CreateDebugConsole() __noop
#define DestroyDebugConsole() __noop

#endif


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hModule);
			baseAddress = GetModuleHandle(nullptr);

			CreateDebugConsole();
			MH_Initialize();
			ctext::Config::Get().Initialise();

			ctext::hooks::InitialiseHooks();
			ctext::hooks::EnableHooks();

			break;
		}

		case DLL_PROCESS_DETACH:
			ctext::hooks::UninitialiseHooks();

			MH_Uninitialize();
			DestroyDebugConsole();

			break;
	}

	return TRUE;
}