

#include "pch.h"


int strStart = 0, strEnd = 0;
float scale = 1;
using namespace std;
char atcPath[DIM] = "", charMaster[DIM] = "";
int x, y, maxX, maxY, saveX, saveY;
int horizontal = 0;
int vertical = 0;
int Horizontal = 0;
int Vertical = 0;
int sizeX = 0, sizeY = 0;
POINT p;
bool toRestore = false;

int main() {
	getATCPath();
	FILE *test = NULL;
	char path_atc[DIM] = "";
	sprintf(path_atc, "%s\\atc.txt", atcPath);
	test = fopen(path_atc, "r");
	if (test == NULL) {
		char path_atc[DIM] = "";
		sprintf(path_atc, "%s\\atc_commander.txt", atcPath);
		test = fopen(path_atc, "w");
		fclose(test);
		char commandF[DIM] = "";
		sprintf(commandF, "%s\\atc.exe", atcPath);
		std::string S = string(commandF);
		std::wstring STEMP = std::wstring(S.begin(), S.end());
		LPCWSTR SW = STEMP.c_str();
		ShellExecute(NULL, _T("open"), SW, NULL, NULL, SW_SHOW);
	}
	else {
		char deleteFile[DIM] = "";
		fclose(test);
		sprintf(deleteFile, "del \"%s\"", path_atc);
		system(deleteFile);
	}
	ShowConsoleCursor(FALSE);
	system("title ATC Commander");
	int pressed = 0;
	HWND w;
	w = GetConsoleWindow();
	setFontSize(12, 16);
	window();
	GetWindowPos(&x, &y, &maxX, &maxY);
	colors();
	system("MODE con cols=96 lines=38");
	while (true) {
		GetWindowPos(&x, &y, &maxX, &maxY);
		GetCursorPos(&p);
		if (toRestore == false) {
			cls();
			toRestore = true;
			puts("\n			SETTINGS");
			currentSettings();
			puts("\n			ENVIRONMENT");
			atcEnvironment();
			puts("\n			FOLDERS");
			atcFolders();
			puts("\n			CALCULATIONS");
			atcCalculations();
			puts("\n			TIME");
			atcTime();
			puts("\n			HANDLING PC");
			atcHandlingPC();
		}
		saveX = p.x;
		saveY = p.y;
		FILE * to_exit = NULL;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\exit.txt", atcPath);
		to_exit = fopen(toOpen, "r");
		if (to_exit != NULL) {
			fclose(to_exit);
			char toExit[DIM] = "";
			sprintf(toExit, "del \"%s\"", toOpen);
			system(toExit);
			exit(0);
		}
		POINT w;
		GetCursorPos(&w);
		if (WindowFromPoint(w) == GetConsoleWindow()) {
			while (maxX - (maxX - p.x) - x >= horizontalConversion(413) && maxX - (maxX - p.x) - x <= horizontalConversion(470) && maxY - (maxY - p.y) - y >= verticalConversion(70) && maxY - (maxY - p.y) - y < verticalConversion(80)) {
				changecursor();
				if (toRestore) {
					puts("Radian");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					mode(1);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(480) && maxX - (maxX - p.x) - x <= horizontalConversion(535) && maxY - (maxY - p.y) - y >= verticalConversion(70) && maxY - (maxY - p.y) - y < verticalConversion(80)) {
				changecursor();
				if (toRestore) {
					puts("Degree");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					mode(2);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(548) && maxX - (maxX - p.x) - x <= horizontalConversion(611) && maxY - (maxY - p.y) - y >= verticalConversion(70) && maxY - (maxY - p.y) - y < verticalConversion(80)) {
				changecursor();
				if (toRestore) {
					puts("Gradian");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					mode(3);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(413) && maxX - (maxX - p.x) - x <= horizontalConversion(478) && maxY - (maxY - p.y) - y >= verticalConversion(80) && maxY - (maxY - p.y) - y < verticalConversion(90)) {
				changecursor();
				if (toRestore) {
					puts("Numerical Systems: Enable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					numSystemsController(1);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(490) && maxX - (maxX - p.x) - x <= horizontalConversion(565) && maxY - (maxY - p.y) - y >= verticalConversion(80) && maxY - (maxY - p.y) - y < verticalConversion(90)) {
				changecursor();
				if (toRestore) {
					puts("Numerical Systems: Disable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					numSystemsController(0);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(413) && maxX - (maxX - p.x) - x <= horizontalConversion(478) && maxY - (maxY - p.y) - y >= verticalConversion(90) && maxY - (maxY - p.y) - y < verticalConversion(100)) {
				changecursor();
				if (toRestore) {
					puts("SI Prefixes: Enable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					siPrefixController(1);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(490) && maxX - (maxX - p.x) - x <= horizontalConversion(565) && maxY - (maxY - p.y) - y >= verticalConversion(90) && maxY - (maxY - p.y) - y < verticalConversion(100)) {
				changecursor();
				if (toRestore) {
					puts("SI Prefixes: Disable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					siPrefixController(0);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(413) && maxX - (maxX - p.x) - x <= horizontalConversion(478) && maxY - (maxY - p.y) - y >= verticalConversion(110) && maxY - (maxY - p.y) - y < verticalConversion(120)) {
				changecursor();
				if (toRestore) {
					puts("Actual Time Response: Enable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					actualTimeController(1);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(490) && maxX - (maxX - p.x) - x <= horizontalConversion(565) && maxY - (maxY - p.y) - y >= verticalConversion(110) && maxY - (maxY - p.y) - y < verticalConversion(120)) {
				changecursor();
				if (toRestore) {
					puts("Actual Time Response: Disable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					actualTimeController(0);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(413) && maxX - (maxX - p.x) - x <= horizontalConversion(478) && maxY - (maxY - p.y) - y >= verticalConversion(120) && maxY - (maxY - p.y) - y < verticalConversion(130)) {
				changecursor();
				if (toRestore) {
					puts("Verbose Resolution: Enable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					verboseResolutionController(1);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(490) && maxX - (maxX - p.x) - x <= horizontalConversion(565) && maxY - (maxY - p.y) - y >= verticalConversion(120) && maxY - (maxY - p.y) - y < verticalConversion(130)) {
				changecursor();
				if (toRestore) {
					puts("Verbose Resolution: Disable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					verboseResolutionController(0);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(68) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("clean");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("clean");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(74) && maxX - (maxX - p.x) - x <= horizontalConversion(135) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("exit");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					restorecursor();
					sendToATC("exit");
					exit(0);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(141) && maxX - (maxX - p.x) - x <= horizontalConversion(211) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("about");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("about");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(218) && maxX - (maxX - p.x) - x <= horizontalConversion(364) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("clean history");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("clean history");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(372) && maxX - (maxX - p.x) - x <= horizontalConversion(490) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("user guide");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("user guide");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(497) && maxX - (maxX - p.x) - x <= horizontalConversion(578) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("update");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("update");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(582) && maxX - (maxX - p.x) - x <= horizontalConversion(702) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("update x64");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("update x64");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(706) && maxX - (maxX - p.x) - x <= horizontalConversion(865) && maxY - (maxY - p.y) - y >= verticalConversion(170) && maxY - (maxY - p.y) - y < verticalConversion(180)) {
				changecursor();
				if (toRestore) {
					puts("update portable");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("update portable");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(107) && maxY - (maxY - p.y) - y >= verticalConversion(185) && maxY - (maxY - p.y) - y < verticalConversion(195)) {
				changecursor();
				if (toRestore) {
					puts("reset all");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("reset all");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(112) && maxX - (maxX - p.x) - x <= horizontalConversion(260) && maxY - (maxY - p.y) - y >= verticalConversion(185) && maxY - (maxY - p.y) - y < verticalConversion(195)) {
				changecursor();
				if (toRestore) {
					puts("reset all now");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("reset all now");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(266) && maxX - (maxX - p.x) - x <= horizontalConversion(422) && maxY - (maxY - p.y) - y >= verticalConversion(185) && maxY - (maxY - p.y) - y < verticalConversion(195)) {
				changecursor();
				if (toRestore) {
					puts("reset settings");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("reset settings");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(430) && maxX - (maxX - p.x) - x <= horizontalConversion(624) && maxY - (maxY - p.y) - y >= verticalConversion(185) && maxY - (maxY - p.y) - y < verticalConversion(195)) {
				changecursor();
				if (toRestore) {
					puts("reset settings now");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("reset settings now");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(630) && maxX - (maxX - p.x) - x <= horizontalConversion(712) && maxY - (maxY - p.y) - y >= verticalConversion(185) && maxY - (maxY - p.y) - y < verticalConversion(195)) {
				changecursor();
				if (toRestore) {
					puts("colors");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("colors");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(716) && maxX - (maxX - p.x) - x <= horizontalConversion(840) && maxY - (maxY - p.y) - y >= verticalConversion(185) && maxY - (maxY - p.y) - y < verticalConversion(195)) {
				changecursor();
				if (toRestore) {
					puts("dimensions");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("dimensions");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(78) && maxY - (maxY - p.y) - y >= verticalConversion(198) && maxY - (maxY - p.y) - y < verticalConversion(208)) {
				changecursor();
				if (toRestore) {
					puts("window");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("window");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(82) && maxX - (maxX - p.x) - x <= horizontalConversion(174) && maxY - (maxY - p.y) - y >= verticalConversion(198) && maxY - (maxY - p.y) - y < verticalConversion(208)) {
				changecursor();
				if (toRestore) {
					puts("run atc");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("run atc");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(179) && maxX - (maxX - p.x) - x <= horizontalConversion(310) && maxY - (maxY - p.y) - y >= verticalConversion(198) && maxY - (maxY - p.y) - y < verticalConversion(208)) {
				changecursor();
				if (toRestore) {
					puts("restart atc");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("restart atc");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(314) && maxX - (maxX - p.x) - x <= horizontalConversion(404) && maxY - (maxY - p.y) - y >= verticalConversion(198) && maxY - (maxY - p.y) - y < verticalConversion(208)) {
				changecursor();
				if (toRestore) {
					puts("history");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("history");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(410) && maxX - (maxX - p.x) - x <= horizontalConversion(556) && maxY - (maxY - p.y) - y >= verticalConversion(198) && maxY - (maxY - p.y) - y < verticalConversion(208)) {
				changecursor();
				if (toRestore) {
					puts("predefine txt");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("predefine txt");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(562) && maxX - (maxX - p.x) - x <= horizontalConversion(674) && maxY - (maxY - p.y) - y >= verticalConversion(198) && maxY - (maxY - p.y) - y < verticalConversion(208)) {
				changecursor();
				if (toRestore) {
					puts("solve txt");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("solve txt");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(678) && maxX - (maxX - p.x) - x <= horizontalConversion(870) && maxY - (maxY - p.y) - y >= verticalConversion(198) && maxY - (maxY - p.y) - y < verticalConversion(208)) {
				changecursor();
				if (toRestore) {
					puts("see abbreviations");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("see abbreviations");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(241) && maxY - (maxY - p.y) - y >= verticalConversion(210) && maxY - (maxY - p.y) - y < verticalConversion(222)) {
				changecursor();
				if (toRestore) {
					puts("eliminate abbreviations");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("eliminate abbreviations");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(242) && maxX - (maxX - p.x) - x <= horizontalConversion(450) && maxY - (maxY - p.y) - y >= verticalConversion(210) && maxY - (maxY - p.y) - y < verticalConversion(222)) {
				changecursor();
				if (toRestore) {
					puts("enable txt detector");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("enable txt detector");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(458) && maxX - (maxX - p.x) - x <= horizontalConversion(642) && maxY - (maxY - p.y) - y >= verticalConversion(210) && maxY - (maxY - p.y) - y < verticalConversion(222)) {
				changecursor();
				if (toRestore) {
					puts("eliminate strings");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("eliminate strings");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(652) && maxX - (maxX - p.x) - x <= horizontalConversion(778) && maxY - (maxY - p.y) - y >= verticalConversion(210) && maxY - (maxY - p.y) - y < verticalConversion(222)) {
				changecursor();
				if (toRestore) {
					puts("see strings");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("see strings");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(784) && maxX - (maxX - p.x) - x <= horizontalConversion(870) && maxY - (maxY - p.y) - y >= verticalConversion(210) && maxY - (maxY - p.y) - y < verticalConversion(222)) {
				changecursor();
				if (toRestore) {
					puts("donate");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("donate");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(155) && maxY - (maxY - p.y) - y >= verticalConversion(214) && maxY - (maxY - p.y) - y < verticalConversion(234)) {
				changecursor();
				if (toRestore) {
					puts("auto solve txt");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("auto solve txt");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(161) && maxX - (maxX - p.x) - x <= horizontalConversion(298) && maxY - (maxY - p.y) - y >= verticalConversion(214) && maxY - (maxY - p.y) - y < verticalConversion(234)) {
				changecursor();
				if (toRestore) {
					puts("atc from cmd");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("atc from cmd");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(304) && maxX - (maxX - p.x) - x <= horizontalConversion(442) && maxY - (maxY - p.y) - y >= verticalConversion(214) && maxY - (maxY - p.y) - y < verticalConversion(234)) {
				changecursor();
				if (toRestore) {
					puts("atc over cmd");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("atc over cmd");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(449) && maxX - (maxX - p.x) - x <= horizontalConversion(586) && maxY - (maxY - p.y) - y >= verticalConversion(214) && maxY - (maxY - p.y) - y < verticalConversion(234)) {
				changecursor();
				if (toRestore) {
					puts("atc facebook");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("atc facebook");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(592) && maxX - (maxX - p.x) - x <= horizontalConversion(758) && maxY - (maxY - p.y) - y >= verticalConversion(214) && maxY - (maxY - p.y) - y < verticalConversion(234)) {
				changecursor();
				if (toRestore) {
					puts("atc sourceforge");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("atc sourceforge");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(765) && maxX - (maxX - p.x) - x <= horizontalConversion(927) && maxY - (maxY - p.y) - y >= verticalConversion(214) && maxY - (maxY - p.y) - y < verticalConversion(234)) {
				changecursor();
				if (toRestore) {
					puts("current settings");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("current settings");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(115) && maxY - (maxY - p.y) - y >= verticalConversion(286) && maxY - (maxY - p.y) - y < verticalConversion(299)) {
				changecursor();
				if (toRestore) {
					puts("atc folder");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("atc folder");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(122) && maxX - (maxX - p.x) - x <= horizontalConversion(249) && maxY - (maxY - p.y) - y >= verticalConversion(286) && maxY - (maxY - p.y) - y < verticalConversion(299)) {
				changecursor();
				if (toRestore) {
					puts("source code");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("source code");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(255) && maxX - (maxX - p.x) - x <= horizontalConversion(355) && maxY - (maxY - p.y) - y >= verticalConversion(286) && maxY - (maxY - p.y) - y < verticalConversion(299)) {
				changecursor();
				if (toRestore) {
					puts("to solve");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("to solve");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(362) && maxX - (maxX - p.x) - x <= horizontalConversion(538) && maxY - (maxY - p.y) - y >= verticalConversion(286) && maxY - (maxY - p.y) - y < verticalConversion(299)) {
				changecursor();
				if (toRestore) {
					puts("scripts examples");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("scripts examples");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(544) && maxX - (maxX - p.x) - x <= horizontalConversion(700) && maxY - (maxY - p.y) - y >= verticalConversion(286) && maxY - (maxY - p.y) - y < verticalConversion(299)) {
				changecursor();
				if (toRestore) {
					puts("user functions");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("user functions");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(708) && maxX - (maxX - p.x) - x <= horizontalConversion(800) && maxY - (maxY - p.y) - y >= verticalConversion(286) && maxY - (maxY - p.y) - y < verticalConversion(299)) {
				changecursor();
				if (toRestore) {
					puts("strings");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("strings");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(146) && maxY - (maxY - p.y) - y >= verticalConversion(338) && maxY - (maxY - p.y) - y < verticalConversion(350)) {
				changecursor();
				if (toRestore) {
					puts("see variables");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("see variables");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(150) && maxX - (maxX - p.x) - x <= horizontalConversion(335) && maxY - (maxY - p.y) - y >= verticalConversion(338) && maxY - (maxY - p.y) - y < verticalConversion(350)) {
				changecursor();
				if (toRestore) {
					puts("renamed variables");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("renamed variables");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(342) && maxX - (maxX - p.x) - x <= horizontalConversion(546) && maxY - (maxY - p.y) - y >= verticalConversion(338) && maxY - (maxY - p.y) - y < verticalConversion(350)) {
				changecursor();
				if (toRestore) {
					puts("eliminate variables");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("eliminate variables");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(554) && maxX - (maxX - p.x) - x <= horizontalConversion(680) && maxY - (maxY - p.y) - y >= verticalConversion(338) && maxY - (maxY - p.y) - y < verticalConversion(350)) {
				changecursor();
				if (toRestore) {
					puts("see results");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("see results");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(688) && maxX - (maxX - p.x) - x <= horizontalConversion(882) && maxY - (maxY - p.y) - y >= verticalConversion(338) && maxY - (maxY - p.y) - y < verticalConversion(350)) {
				changecursor();
				if (toRestore) {
					puts("eliminate results");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("eliminate results");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(276) && maxY - (maxY - p.y) - y >= verticalConversion(350) && maxY - (maxY - p.y) - y < verticalConversion(365)) {
				changecursor();
				if (toRestore) {
					puts("triangles rectangles solver");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("triangles rectangles solver");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(286) && maxX - (maxX - p.x) - x <= horizontalConversion(537) && maxY - (maxY - p.y) - y >= verticalConversion(350) && maxY - (maxY - p.y) - y < verticalConversion(365)) {
				changecursor();
				if (toRestore) {
					puts("arithmetic matrix solver");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("arithmetic matrix solver");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(544) && maxX - (maxX - p.x) - x <= horizontalConversion(778) && maxY - (maxY - p.y) - y >= verticalConversion(350) && maxY - (maxY - p.y) - y < verticalConversion(365)) {
				changecursor();
				if (toRestore) {
					puts("financial calculations");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("financial calculations");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(786) && maxX - (maxX - p.x) - x <= horizontalConversion(927) && maxY - (maxY - p.y) - y >= verticalConversion(350) && maxY - (maxY - p.y) - y < verticalConversion(365)) {
				changecursor();
				if (toRestore) {
					puts("graph settings");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("graph settings");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(220) && maxY - (maxY - p.y) - y >= verticalConversion(366) && maxY - (maxY - p.y) - y < verticalConversion(376)) {
				changecursor();
				if (toRestore) {
					puts("geometry calculations");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("geometry calculations");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(227) && maxX - (maxX - p.x) - x <= horizontalConversion(471) && maxY - (maxY - p.y) - y >= verticalConversion(366) && maxY - (maxY - p.y) - y < verticalConversion(376)) {
				changecursor();
				if (toRestore) {
					puts("statistics calculations");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("statistics calculations");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(478) && maxX - (maxX - p.x) - x <= horizontalConversion(692) && maxY - (maxY - p.y) - y >= verticalConversion(366) && maxY - (maxY - p.y) - y < verticalConversion(376)) {
				changecursor();
				if (toRestore) {
					puts("physics calculations");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("physics calculations");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(697) && maxX - (maxX - p.x) - x <= horizontalConversion(880) && maxY - (maxY - p.y) - y >= verticalConversion(366) && maxY - (maxY - p.y) - y < verticalConversion(376)) {
				changecursor();
				if (toRestore) {
					puts("unit conversions");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("unit conversions");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(284) && maxY - (maxY - p.y) - y >= verticalConversion(377) && maxY - (maxY - p.y) - y < verticalConversion(388)) {
				changecursor();
				if (toRestore) {
					puts("microeconomics calculations");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("microeconomics calculations");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(58) && maxY - (maxY - p.y) - y >= verticalConversion(423) && maxY - (maxY - p.y) - y < verticalConversion(442)) {
				changecursor();
				if (toRestore) {
					puts("time");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("time");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(64) && maxX - (maxX - p.x) - x <= horizontalConversion(166) && maxY - (maxY - p.y) - y >= verticalConversion(423) && maxY - (maxY - p.y) - y < verticalConversion(442)) {
				changecursor();
				if (toRestore) {
					puts("calendar");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("calendar");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(10) && maxX - (maxX - p.x) - x <= horizontalConversion(96) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("shutdown");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("shutdown");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(102) && maxX - (maxX - p.x) - x <= horizontalConversion(240) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("shutdown now");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					restorecursor();
					sendToATC("shutdown now");
					exit(0);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(246) && maxX - (maxX - p.x) - x <= horizontalConversion(367) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("restart pc");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("restart pc");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(372) && maxX - (maxX - p.x) - x <= horizontalConversion(530) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("restart pc now");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					restorecursor();
					sendToATC("restart pc now");
					exit(0);
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(534) && maxX - (maxX - p.x) - x <= horizontalConversion(643) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("hibernate");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("hibernate");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(650) && maxX - (maxX - p.x) - x <= horizontalConversion(740) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("log off");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("log off");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(746) && maxX - (maxX - p.x) - x <= horizontalConversion(816) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("sleep");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("sleep");
					break;
				}
				sleepRF();
			}
			while (maxX - (maxX - p.x) - x >= horizontalConversion(822) && maxX - (maxX - p.x) - x <= horizontalConversion(886) && maxY - (maxY - p.y) - y >= verticalConversion(476) && maxY - (maxY - p.y) - y < verticalConversion(492)) {
				changecursor();
				if (toRestore) {
					puts("lock");
				}
				toRestore = false;
				if (GetKeyState(VK_LBUTTON) < 0) {
					sendToATC("lock");
					break;
				}
				sleepRF();
			}
		}
		if (toRestore) {
			restorecursor();
		}
		Sleep(500);
	}
}

int verticalConversion(int Y) {
	int newY = 0;
	newY = (int)(((Y*sizeY) / (float)527)*scale);
	return newY;
}

int horizontalConversion(int X) {
	int newX = 0;
	newX = (int)(((X*sizeX) / (float)939)*scale);
	return newX;
}

void sleepRF() {
	Sleep(25);
	GetWindowPos(&x, &y, &maxX, &maxY);
	GetCursorPos(&p);
}

void restorecursor()
{
	SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0); NULL;
}

void changecursor()
{
	HCURSOR hcHand = LoadCursor(0, IDC_HAND);
	HCURSOR hcHandCopy = CopyCursor(hcHand);
	BOOL ret = SetSystemCursor(hcHandCopy, 32512);
	DestroyCursor(hcHand);
}

void setFontSize(int x, int y) {
	/*BOOL WINAPI GetCurrentConsoleFont(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFO lpConsoleCurrentFont);
	COORD WINAPI GetConsoleFontSize(HANDLE hConsoleOutput, DWORD nFont);
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFO GETFONT;
	GetCurrentConsoleFont(StdHandle, FALSE, &GETFONT);
	COORD Fontsize = GetConsoleFontSize(StdHandle, GETFONT.nFont);
	SHORT Font_X = Fontsize.X;
	SHORT Font_Y = Fontsize.Y;
	if (Font_X != 12 || Font_Y != 16)
	{
		printf("\nx-> %d\ny-> %d\n", Font_X, Font_Y);
		puts("\nSeems that your font size is not ready.\nPlease change the properties settings for this window to Raster Fonts and select 12x16.\nRestart ATC window after that to changes take effect.");
		system("pause");
		exit(0);
	}*/

	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = x;
	lpConsoleCurrentFontEx->dwFontSize.Y = y;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, lpConsoleCurrentFontEx);
}

void MouseMove(int x, int y)
{
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x * (65535.0f / fScreenWidth);
	double fy = y * (65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;
	::SendInput(1, &Input, sizeof(INPUT));
}

void GetWindowPos(int *x, int *y, int *maxX, int *maxY) {
	RECT rect = { NULL };
	if (GetWindowRect(GetConsoleWindow(), &rect)) {
		*x = rect.left;
		*y = rect.top;
		*maxX = rect.right;
		*maxY = rect.bottom;
	}
}

void cls()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(hConsole,
		(TCHAR) ' ',
		dwConSize,
		coordScreen,
		&cCharsWritten))
	{
		return;
	}
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}
	if (!FillConsoleOutputAttribute(hConsole,
		csbi.wAttributes,
		dwConSize,
		coordScreen,
		&cCharsWritten))
	{
		return;
	}
	SetConsoleCursorPosition(hConsole, coordScreen);
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

void currentSettings() {
	FILE *open = NULL;
	puts("");
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\mode.txt", atcPath);
	open = fopen(toOpen, "r");
	char info[DIM] = "";
	int state = 0;
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = atoi(info);
		switch (state) {
		case 1:
			puts("Mode------------------------------------> RADIAN Degree Gradian");
			break;
		case 2:
			puts("Mode------------------------------------> Radian DEGREE Gradian");
			break;
		case 3:
			puts("Mode------------------------------------> Radian Degree GRADIAN");
			break;
		}
	}
	else {
		puts("Mode------------------------------------> Radian DEGREE Gradian");
	}
	open = NULL;
	sprintf(toOpen, "%s\\numSystems.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = atoi(info);
		switch (state) {
		case 0:
			puts("Numerical Systems Response--------------> Enabled DISABLED");
			break;
		case 1:
			puts("Numerical Systems Response--------------> ENABLED Disabled");
			break;
		}
	}
	else {
		puts("Numerical Systems Response--------------> Enabled DISABLED");
	}
	open = NULL;
	sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = atoi(info);
		switch (state) {
		case 0:
			puts("SI Prefixes Response--------------------> Enabled DISABLED");
			break;
		case 1:
			puts("SI Prefixes Response--------------------> ENABLED Disabled");
			break;
		}
	}
	else {
		puts("SI Prefixes Response--------------------> Enabled DISABLED");
	}
	open = NULL;
	sprintf(toOpen, "%s\\actualTime.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = atoi(info);
		switch (state) {
		case 0:
			puts("Actual Time Response--------------------> Enabled DISABLED");
			break;
		case 1:
			puts("Actual Time Response--------------------> ENABLED Disabled");
			break;
		}
	}
	else {
		puts("Actual Time Response--------------------> Enabled DISABLED");
	}
	open = NULL;
	sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = atoi(info);
		switch (state) {
		case 0:
			puts("Verbose Resolution----------------------> Enabled DISABLED");
			break;
		case 1:
			puts("Verbose Resolution----------------------> ENABLED Disabled");
			break;
		}
	}
	else {
		puts("Verbose Resolution----------------------> Enabled DISABLED");
	}
}

bool isContained(char to_find[DIM], char string[DIM]) {
	int i = 0, j = 0;
	if (strlen(charMaster) == 0) {
		for (i = 0; i < abs((int)strlen(string)); i++) {
			for (j = 0; j < abs((int)strlen(to_find)); j++) {
				if (to_find[j] == string[i] && j == 0) {
					strStart = i;
					while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
						j++;
						i++;
					}
					if (j == strlen(to_find)) {
						strEnd = i;
						return true;
					}
					else {
						i = strStart;
						break;
					}
				}
			}
		}
	}
	else {
		if (isEqual("nothingL", charMaster)) {
			for (i = 0; i < abs((int)strlen(string)); i++) {
				for (j = 0; j < abs((int)strlen(to_find)); j++) {
					if (to_find[j] == string[i] && j == 0 && verifyLetter(string[i - 1]) == (bool)false && verifyNumber(string[i - 1]) == (bool)false) {
						strStart = i;
						while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
							j++;
							i++;
						}
						if (j == strlen(to_find)) {
							strEnd = i;
							return true;
						}
						else {
							i = strStart;
							break;
						}
					}
				}
			}
		}
		else {
			if (isEqual("nothingR", charMaster)) {
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
								j++;
								i++;
							}
							if (j == strlen(to_find) && verifyLetter(string[i - 1]) == (bool)false && verifyNumber(string[i - 1]) == (bool)false) {
								strEnd = i;
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
			}
			else {
				char saveTo_find[DIM] = "";
				sprintf(saveTo_find, to_find);
				sprintf(to_find, "%s%s", charMaster, saveTo_find);
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
								j++;
								i++;
							}
							if (j == strlen(to_find)) {
								strEnd = i;
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
				sprintf(to_find, "%s%s", saveTo_find, charMaster);
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
								j++;
								i++;
							}
							if (j == strlen(to_find)) {
								strEnd = i;
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool verifyNumber(char number) {
	char numbers[DIM] = "_0.123456789E";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

bool isEqual(char to_find[DIM], char string[DIM]) {
	int i = 0;
	while (to_find[i] == string[i] && string[i] != '\0') {
		i++;
	}
	if (to_find[i] == string[i] && to_find[i] == '\0') {
		return true;
	}
	return false;
}

bool verifyLetter(char letter) {
	char letters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			return true;
		}
	}
	return false;
}

void ShowConsoleCursor(bool bShow)
{
	static HANDLE hOut;
	static BOOL firstTime = TRUE;
	CONSOLE_CURSOR_INFO cursorInfo;
	if (firstTime)
	{
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		firstTime = FALSE;
	}
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = bShow;
	SetConsoleCursorInfo(hOut, &cursorInfo);
}

void mode(int option) {
	FILE *open = NULL;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\mode.txt", atcPath);
	while (open == NULL) {
		open = fopen(toOpen, "w");
	}
	fprintf(open, "%d", option);
	fclose(open);
}

void numSystemsController(int state) {
	FILE *open;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\numSystems.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void siPrefixController(int state) {
	FILE *open;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void actualTimeController(int state) {
	FILE *open;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\actualTime.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void verboseResolutionController(int state) {
	FILE *open;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void atcEnvironment() {
	char text[5000] = "";
	sprintf(text, "%s\nclean | exit | about | clean history | user guide | update | update x64 | update portable", text);
	sprintf(text, "%s\nreset all | reset all now | reset settings | reset settings now | colors | dimensions", text);
	sprintf(text, "%s\nwindow | run atc | restart atc | history | predefine txt | solve txt | see abbreviations", text);
	sprintf(text, "%s\neliminate abbreviations | enable txt detector | eliminate strings | see strings | donate", text);
	sprintf(text, "%s\nauto solve txt | atc from cmd | atc over cmd | atc facebook | atc sourceforge | current settings", text);
	int i = 0;
	while (i < abs((int)strlen(text))) {
		if (text[i] == '|') {
			text[i] = (char)179;
		}
		i++;
	}
	puts(text);
}

void atcFolders() {
	char text[5000] = "";
	sprintf(text, "%s\natc folder | source code | to solve | scripts examples | user functions | strings", text);
	int i = 0;
	while (i < abs((int)strlen(text))) {
		if (text[i] == '|') {
			text[i] = (char)179;
		}
		i++;
	}
	puts(text);
}

void atcCalculations() {
	char text[5000] = "";
	sprintf(text, "%s\nsee variables | renamed variables | eliminate variables | see results | eliminate results", text);
	sprintf(text, "%s\ntriangles rectangles solver | arithmetic matrix solver | financial calculations | graph settings", text);
	sprintf(text, "%sgeometry calculations | statistics calculations | physics calculations | unit conversions", text);
	sprintf(text, "%s\nmicroeconomics calculations", text);
	int i = 0;
	while (i < abs((int)strlen(text))) {
		if (text[i] == '|') {
			text[i] = (char)179;
		}
		i++;
	}
	puts(text);
}

void atcTime() {
	char text[5000] = "";
	sprintf(text, "%s\ntime | calendar", text);
	int i = 0;
	while (i < abs((int)strlen(text))) {
		if (text[i] == '|') {
			text[i] = (char)179;
		}
		i++;
	}
	puts(text);
}

void atcHandlingPC() {
	char text[5000] = "";
	sprintf(text, "%s\nshutdown | shutdown now | restart pc | restart pc now | hibernate | log off | sleep | lock", text);
	int i = 0;
	while (i < abs((int)strlen(text))) {
		if (text[i] == '|') {
			text[i] = (char)179;
		}
		i++;
	}
	puts(text);
}

void sendToATC(char command[100]) {
	FILE *write = NULL;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\sendCommand.txt", atcPath);
	write = fopen(toOpen, "w");
	while (write == NULL) {
		write = fopen(toOpen, "w");
	}
	fputs(command, write);
	fclose(write);
}
void window() {
	FILE *open;
	char setting[DIM] = "";
	int i = 0, e = 0;
	int x, y, width, height, a = 1;
	char value[DIM];
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\window.txt", atcPath);
	system("MODE con cols=4000 lines=4000");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	GetWindowPos(&x, &y, &maxX, &maxY);
	horizontal = maxX;
	vertical = maxY;
	GetScale();
	system("MODE con cols=96 lines=38");
	GetWindowPos(&x, &y, &maxX, &maxY);
	sizeX = maxX;
	sizeY = maxY;
	if (fopen(toOpen, "r") == NULL) {
		HWND a;
		a = GetConsoleWindow();
		MoveWindow(a, Horizontal + abs(Horizontal - horizontal) - maxX, Vertical - abs(Vertical - vertical) - maxY, 1000, 1000, FALSE);
	}
	else {
		open = fopen(toOpen, "r");
		for (i = 0; (setting[i] = fgetc(open)) != EOF; i++) {
			value[e] = setting[i];
			if (setting[i] != '\n') {
				e++;
			}
			if (value[e] == '\n'&&a == 1) {
				value[e] = '\0';
				x = atoi(value);
				a = 2; e = 0;
			}
			if (value[e] == '\n'&&a == 2) {
				value[e] = '\0';
				y = atoi(value);
				a = 3; e = 0;
			}
			if (value[e] == '\n'&&a == 3) {
				value[e] = '\0';
				width = atoi(value);
				a = 4; e = 0;
			}
			if (value[e] == '\n'&&a == 4) {
				value[e] = '\0';
				height = atoi(value);
				a = 5; e = 0;
			}
		}
		HWND w;
		w = GetConsoleWindow();
		MoveWindow(w, (int)x + 70, (int)y + 70, (int)width, (int)height, FALSE);
	}
}

void colors() {
	FILE *open = NULL;
	char setting[DIM];
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\colors.txt", atcPath);
	if (fopen(toOpen, "r") == NULL) {
		system("color 73");
	}
	else {
		open = fopen(toOpen, "r");
		fgets(setting, 9, open);
		fclose(open);
		system(setting);
	}
}

void GetScale()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Horizontal = desktop.right;
	Vertical = desktop.bottom;
	int vert[50] = { 1080,1050,1024,960,900,864,800,768,720,600 };
	int horiz[50] = { 1920,1680,1600,1440,1400,1366,1360,1280,1152,1024,800 };
	float scale = 0;
	int saveVert = 0, saveHoriz = 0;
	int i = 0;
	for (i = 0; i < 11; i++) {
		if (Horizontal <= horiz[i] && Horizontal > horiz[i + 1]) {
			saveHoriz = horiz[i];
		}
	}
	int new_horizontal = 0;
	if (Horizontal != saveHoriz) {
		new_horizontal = (int)(Horizontal * 1.25);
		for (i = 0; i < 11; i++) {
			if (new_horizontal <= horiz[i] && new_horizontal > horiz[i + 1]) {
				saveHoriz = horiz[i];
			}
		}
		if (new_horizontal != saveHoriz) {
			new_horizontal = (int)(Horizontal * 1.50);
			for (i = 0; i < 11; i++) {
				if (new_horizontal <= horiz[i] && new_horizontal > horiz[i + 1]) {
					saveHoriz = horiz[i];
				}
			}
			if (new_horizontal != saveHoriz) {
				new_horizontal = (int)(Horizontal * 1.75);
				for (i = 0; i < 11; i++) {
					if (new_horizontal <= horiz[i] && new_horizontal > horiz[i + 1]) {
						saveHoriz = horiz[i];
					}
				}
				if (new_horizontal == saveHoriz) {
					scale = 1.75;
				}
			}
			else {
				if (new_horizontal == saveHoriz) {
					scale = 1.5;
				}
			}
		}
		else {
			if (new_horizontal == saveHoriz) {
				scale = 1.25;
			}
		}
	}
	else {
		if (new_horizontal == saveHoriz) {
			scale = 1.0;
		}
	}
}

boolean IsPreviousToWindowsVista()
{
	boolean previousToVista = false;

	OSVERSIONINFOEX osversion;
	ZeroMemory(&osversion, sizeof(OSVERSIONINFOEX));
	osversion.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((OSVERSIONINFO*)&osversion))
	{
		const DWORD VistaVersion = 6;
		if ((osversion.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osversion.dwMajorVersion < VistaVersion))
		{
			previousToVista = true;
		}
	}
	return previousToVista;
}