#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static FARPROC resolveKernel32(const char* name) {
	HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
	return kernel32 != NULL ? GetProcAddress(kernel32, name) : NULL;
}

extern "C" BOOL WINAPI atcInitializeCriticalSectionEx(
	LPCRITICAL_SECTION criticalSection,
	DWORD spinCount,
	DWORD flags) {
	typedef BOOL(WINAPI* Function)(LPCRITICAL_SECTION, DWORD, DWORD);
	Function nativeFunction = reinterpret_cast<Function>(
		resolveKernel32("InitializeCriticalSectionEx"));
	if (nativeFunction != NULL) {
		return nativeFunction(criticalSection, spinCount, flags);
	}

	(void)flags;
	return InitializeCriticalSectionAndSpinCount(criticalSection, spinCount);
}

extern "C" DWORD WINAPI atcFlsAlloc(PFLS_CALLBACK_FUNCTION callback) {
	typedef DWORD(WINAPI* Function)(PFLS_CALLBACK_FUNCTION);
	Function nativeFunction = reinterpret_cast<Function>(resolveKernel32("FlsAlloc"));
	if (nativeFunction != NULL) {
		return nativeFunction(callback);
	}

	(void)callback;
	return TlsAlloc();
}

extern "C" BOOL WINAPI atcFlsFree(DWORD index) {
	typedef BOOL(WINAPI* Function)(DWORD);
	Function nativeFunction = reinterpret_cast<Function>(resolveKernel32("FlsFree"));
	return nativeFunction != NULL ? nativeFunction(index) : TlsFree(index);
}

extern "C" PVOID WINAPI atcFlsGetValue(DWORD index) {
	typedef PVOID(WINAPI* Function)(DWORD);
	Function nativeFunction = reinterpret_cast<Function>(resolveKernel32("FlsGetValue"));
	return nativeFunction != NULL ? nativeFunction(index) : TlsGetValue(index);
}

extern "C" BOOL WINAPI atcFlsSetValue(DWORD index, PVOID value) {
	typedef BOOL(WINAPI* Function)(DWORD, PVOID);
	Function nativeFunction = reinterpret_cast<Function>(resolveKernel32("FlsSetValue"));
	return nativeFunction != NULL ? nativeFunction(index, value) : TlsSetValue(index, value);
}

extern "C" BOOL WINAPI atcIsThreadAFiber() {
	typedef BOOL(WINAPI* Function)();
	Function nativeFunction = reinterpret_cast<Function>(resolveKernel32("IsThreadAFiber"));
	return nativeFunction != NULL ? nativeFunction() : FALSE;
}
