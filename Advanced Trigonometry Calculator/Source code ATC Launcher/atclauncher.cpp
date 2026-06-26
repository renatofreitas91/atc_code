// atclauncher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
char atcPath[DIM] = "";

int main()
{
	WCHAR path[260];
	GetModuleFileName(NULL, path, 260);
	HWND console = FindWindow(L"ConsoleWindowClass", path);
	if (IsWindow(console))
		ShowWindow(console, SW_HIDE);
	getATCPath();
	if (RegisterHotKey(
		NULL,
		1,
		MOD_CONTROL | MOD_ALT | MOD_NOREPEAT,
		0x4B))
	{
	}
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			char path4ATC[DIM] = "";
			sprintf(path4ATC, "%s\\atc.exe", atcPath);
			using namespace std;
			std::string s = string(path4ATC);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
			exit(0);
		}
	}
	return 0;
}

void getATCPath() {
	FILE *aPath = NULL;
	aPath = fopen("atc_path.txt", "r");
	if (aPath == NULL) {
		aPath = fopen("atc_path.txt", "w");
		TCHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);
		wcstombs(atcPath, NPath, wcslen(NPath) + 1);
		fprintf(aPath, "%s", atcPath);
		fclose(aPath);
	}
	else {
		fgets(atcPath, DIM, aPath);
		fclose(aPath);
		if (atcPath[strlen(atcPath) - 2] == ' ') {
			atcPath[strlen(atcPath) - 2] = '\0';
		}
		FILE *test = NULL;
		char testPath[DIM] = "";
		sprintf(testPath, "%s\\License.txt", atcPath);
		test = fopen(testPath, "r");
		if (test == NULL) {
			test = fopen("atc_path.txt", "w");
			TCHAR NPath[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, NPath);
			wcstombs(atcPath, NPath, wcslen(NPath) + 1);
			fprintf(test, "%s", atcPath);
			fclose(test);
		}
	}
}
