#include "stdafx.h"
// crash_handler.cpp
// Compilar com toolset que suporte XP se necessário (ex.: v141_xp ou v140_xp)
// Usa apenas Win32 APIs compatíveis com Windows XP.

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <sstream>
#if defined(_MSC_VER)
#include <intrin.h>
#endif

static std::string GetExeDirectory()
{
	char* path = getDynamicCharArrayFixedLenght("", MAX_PATH);
	DWORD len = GetModuleFileNameA(NULL, path, MAX_PATH);
	if (len == 0 || len == MAX_PATH) {
		_delete(path, "path");
		path = nullptr;
		return std::string(".\\"); // fallback
	}
	// remove filename from path
	std::string s(path, path + len);
	_delete(path, "path");
	path = nullptr;
	size_t pos = s.find_last_of("\\/");
	if (pos == std::string::npos) return std::string(".\\");
	return s.substr(0, pos + 1); // includes trailing backslash
}

static void WriteTextToFile(const char* filename, const std::string& text)
{
	// usa CreateFile/WriteFile para maior robustez em cenários de crash
	HANDLE h = CreateFileA(filename,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (h == INVALID_HANDLE_VALUE) return;
	DWORD written = 0;
	WriteFile(h, text.c_str(), (DWORD)text.size(), &written, NULL);
	CloseHandle(h);
}

LONG WINAPI CrashHandler(EXCEPTION_POINTERS* ep)
{
	std::ostringstream ss;
	ss << "==== ATC Crash Report ====\r\n";
	ss << "ExceptionCode: 0x" << std::hex << ep->ExceptionRecord->ExceptionCode << "\r\n";
	ss << "ExceptionFlags: 0x" << std::hex << ep->ExceptionRecord->ExceptionFlags << "\r\n";
	ss << "ExceptionAddress: " << std::hex << (uintptr_t)ep->ExceptionRecord->ExceptionAddress << "\r\n";
	ss << "NumberParameters: " << std::dec << ep->ExceptionRecord->NumberParameters << "\r\n";
	for (DWORD i = 0; i < ep->ExceptionRecord->NumberParameters; ++i) {
		ss << "  Param[" << i << "]: 0x" << std::hex << ep->ExceptionRecord->ExceptionInformation[i] << "\r\n";
	}

#if defined(_M_X64) || defined(__x86_64__)
	// registadores principais (x64)
	ss << "Rax: 0x" << std::hex << ep->ContextRecord->Rax << "\r\n";
	ss << "Rbx: 0x" << std::hex << ep->ContextRecord->Rbx << "\r\n";
	ss << "Rcx: 0x" << std::hex << ep->ContextRecord->Rcx << "\r\n";
	ss << "Rdx: 0x" << std::hex << ep->ContextRecord->Rdx << "\r\n";
	ss << "Rsi: 0x" << std::hex << ep->ContextRecord->Rsi << "\r\n";
	ss << "Rdi: 0x" << std::hex << ep->ContextRecord->Rdi << "\r\n";
	ss << "Rbp: 0x" << std::hex << ep->ContextRecord->Rbp << "\r\n";
	ss << "Rsp: 0x" << std::hex << ep->ContextRecord->Rsp << "\r\n";
	ss << "Rip: 0x" << std::hex << ep->ContextRecord->Rip << "\r\n";
#else
	// registadores principais (x86)
	ss << "Eax: 0x" << std::hex << ep->ContextRecord->Eax << "\r\n";
	ss << "Ebx: 0x" << std::hex << ep->ContextRecord->Ebx << "\r\n";
	ss << "Ecx: 0x" << std::hex << ep->ContextRecord->Ecx << "\r\n";
	ss << "Edx: 0x" << std::hex << ep->ContextRecord->Edx << "\r\n";
	ss << "Esi: 0x" << std::hex << ep->ContextRecord->Esi << "\r\n";
	ss << "Edi: 0x" << std::hex << ep->ContextRecord->Edi << "\r\n";
	ss << "Ebp: 0x" << std::hex << ep->ContextRecord->Ebp << "\r\n";
	ss << "Esp: 0x" << std::hex << ep->ContextRecord->Esp << "\r\n";
	ss << "Eip: 0x" << std::hex << ep->ContextRecord->Eip << "\r\n";
#endif

	ss << "\r\nTimestamp (GetTickCount): " << std::dec << GetTickCount() << "\r\n";

	// cria path para exception.txt na pasta do exe
	std::string dir = GetExeDirectory();
	std::string fullpath = dir + "exception.txt";

	WriteTextToFile(fullpath.c_str(), ss.str());

	// opcional: mostrar mensagem ao utilizador (não fazer UI complexa em crash)
	// MessageBoxA(NULL, "ATC encontrou um erro grave. O ficheiro exception.txt foi gravado.", "ATC - Crash", MB_OK | MB_ICONERROR);

	// indica ao sistema para continuar com o handler padrão (ou termina)
	return EXCEPTION_EXECUTE_HANDLER;
}

// Handler para exceções C++ não tratadas (std::terminate)
void TerminateHandler()
{
	std::ostringstream ss;
	ss << "==== ATC terminate() called (unhandled C++ exception) ====\r\n";

	// tenta obter exe dir
	std::string dir = GetExeDirectory();
	std::string fullpath = dir + "exception.txt";

	// tenta escrever uma nota
	WriteTextToFile(fullpath.c_str(), ss.str());

	// fallback: chamar abort para garantir que processo termina
	abort();
}
void checkCPUFeatures()
{
	int* cpuInfo = getDynamicArray<int>(4);

	__cpuid(cpuInfo, 1);

	bool sse = (cpuInfo[3] & (1 << 25)) != 0;
	bool sse2 = (cpuInfo[3] & (1 << 26)) != 0;
	bool sse3 = (cpuInfo[2] & (1 << 0)) != 0;
	bool ssse3 = (cpuInfo[2] & (1 << 9)) != 0;
	bool sse41 = (cpuInfo[2] & (1 << 19)) != 0;
	bool sse42 = (cpuInfo[2] & (1 << 20)) != 0;

	// AVX detection requires more registers – XP will fail so detect statically
	bool avx = false;

	printf("=== CPU Feature Diagnostic (XP Compatible) ===\n\n");

	printf("CPU Vendor String: ");

	char* vendor = getDynamicCharArrayFixedLenght("", 13);
	int* vendorInfo = getDynamicArray<int>(4);
	__cpuid(vendorInfo, 0);
	memcpy(vendor + 0, &vendorInfo[1], 4);
	memcpy(vendor + 4, &vendorInfo[3], 4);
	memcpy(vendor + 8, &vendorInfo[2], 4);
	vendor[12] = 0;

	printf("%s\n\n", vendor);

	printf("SSE:   %s\n", sse ? "SUPPORTED" : "NOT SUPPORTED");
	printf("SSE2:  %s\n", sse2 ? "SUPPORTED" : "NOT SUPPORTED");
	printf("SSE3:  %s\n", sse3 ? "SUPPORTED" : "NOT SUPPORTED");
	printf("SSSE3: %s\n", ssse3 ? "SUPPORTED" : "NOT SUPPORTED");
	printf("SSE4.1:%s\n", sse41 ? "SUPPORTED" : "NOT SUPPORTED");
	printf("SSE4.2:%s\n", sse42 ? "SUPPORTED" : "NOT SUPPORTED");
	printf("AVX:   %s\n", avx ? "SUPPORTED" : "NOT SUPPORTED");

	_delete(cpuInfo, "cpuInfo");
	cpuInfo = nullptr;
	_delete(vendorInfo, "vendorInfo");
	vendorInfo = nullptr;
	_delete(vendor, "vendor");
	vendor = nullptr;

	printf("\nPress Enter to exit...");
	getchar();
}
void InstallCrashHandlers()
{
	checkCPUFeatures();
	system("pause");
	// handler para structured exceptions (access violations, illegal instructions, ...)
	SetUnhandledExceptionFilter(CrashHandler);

	std::set_terminate(TerminateHandler);

	
}
