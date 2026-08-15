#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define _WINMM_

#include <windows.h>
#include <mmsystem.h>

namespace {

using JoyGetPosExFn = MMRESULT(WINAPI*)(UINT, LPJOYINFOEX);
using JoyGetNumDevsFn = UINT(WINAPI*)();

INIT_ONCE winmmInitOnce = INIT_ONCE_STATIC_INIT;
JoyGetPosExFn realJoyGetPosEx;
JoyGetNumDevsFn realJoyGetNumDevs;

BOOL CALLBACK LoadSystemWinmm(PINIT_ONCE, PVOID, PVOID*) {
	wchar_t path[MAX_PATH];
	const UINT length = GetSystemDirectoryW(path, MAX_PATH);
	if (!length || length + 11 >= MAX_PATH)
		return FALSE;

	lstrcatW(path, L"\\winmm.dll");
	const HMODULE module = LoadLibraryW(path);
	if (!module)
		return FALSE;

	realJoyGetPosEx = reinterpret_cast<JoyGetPosExFn>(GetProcAddress(module, "joyGetPosEx"));
	realJoyGetNumDevs = reinterpret_cast<JoyGetNumDevsFn>(GetProcAddress(module, "joyGetNumDevs"));
	return realJoyGetPosEx && realJoyGetNumDevs;
}

DWORD WINAPI LoadCTExt(PVOID) {
	LoadLibraryW(L"ctext.dll");
	return 0;
}

} // namespace

extern "C" MMRESULT WINAPI joyGetPosEx(UINT id, LPJOYINFOEX info) {
	if (!InitOnceExecuteOnce(&winmmInitOnce, LoadSystemWinmm, nullptr, nullptr))
		return MMSYSERR_ERROR;

	return realJoyGetPosEx(id, info);
}

extern "C" UINT WINAPI joyGetNumDevs() {
	if (!InitOnceExecuteOnce(&winmmInitOnce, LoadSystemWinmm, nullptr, nullptr))
		return 0;

	return realJoyGetNumDevs();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(module);
		QueueUserWorkItem(LoadCTExt, nullptr, WT_EXECUTEDEFAULT);
	}

	return TRUE;
}
