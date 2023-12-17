#include "stdafx.h"
#include <wininet.h>
#pragma comment(lib,"Wininet.lib")

using std::string;

#pragma comment(lib,"ws2_32.lib")


HINSTANCE hInst;
WSADATA wsaData;

void mParseUrl(char *mUrl, string &serverName, string &filepath, string &filename);
SOCKET connectToServer(char *szServerName, WORD portNum);
int getHeaderLength(char *content);
char *readUrl2(char *szUrl, long &bytesReturnedOut, char **headerOut);
char appVersion[100] = "2.1.4 of 2023-12-17 (update)";

void check4Updates()
{
	printf("\nChecking for updates...\n");
	const int bufLen = 1024;
	char *szUrl = "https://advantrigoncalcwebsite.on.drv.tw/atc_site/atc_version.html";
	long fileSize;
	char *memBuffer, *headerBuffer;
	char Url[128] = "";
	strcat(Url, "https://advantrigoncalcwebsite.on.drv.tw/atc_site/atc_version.html");
	wchar_t wtext[20];
	mbstowcs(wtext, Url, strlen(Url) + 1);//Plus null
	LPWSTR ptr = wtext;
	boolean bConnect = InternetCheckConnection(ptr, FLAG_ICC_FORCE_CONNECTION, 0);


	if (bConnect)
	{
		memBuffer = headerBuffer = NULL;

		if (WSAStartup(0x101, &wsaData) == 0) {
			memBuffer = readUrl2(szUrl, fileSize, &headerBuffer);
			if (isContained("<p>", memBuffer)) {
				int i = 0, j = strEnd;
				char currentVersion[100] = "";
				while (memBuffer[j] != '<'&&j < abs((int)strlen(memBuffer))) {
					currentVersion[i] = memBuffer[j];
					j++; i++;
				}
				currentVersion[i] = '\0';
				printf("\nCurrent version: %s\n", currentVersion);
				if (!isEqual(appVersion, currentVersion)) {
					printf("\n\nThere is an update available!\n\n");
					printf("\n\nYou can now ask by commands to download Advanced Trigonometry Calculator v%s!\n\n", currentVersion);
					printf("\nIf you want to update to the latest version. Enter the command(s) that best serve your desire:\n\n o \"update\" for Setup x86 \n o \"update x64\" for Setup x64 \n o \"update portable\" for Zip file. \n\nThanks for use Advanced Trigonometry Calculator!\n\n\n");
				}
				else {
					puts("\nYou have the latest version! :)\n");
				}
			}
			if (fileSize != 0)
			{
				delete(memBuffer);
				delete(headerBuffer);
			}
		}
		WSACleanup();
	}
	else {
		puts("\nNo Internet connection available!");
	}
}


void mParseUrl(char *mUrl, string &serverName, string &filepath, string &filename)
{
	string::size_type n;
	string url = mUrl;

	if (url.substr(0, 7) == "http://")
		url.erase(0, 7);

	if (url.substr(0, 8) == "https://")
		url.erase(0, 8);

	n = url.find('/');
	if (n != string::npos)
	{
		serverName = url.substr(0, n);
		filepath = url.substr(n);
		n = filepath.rfind('/');
		filename = filepath.substr(n + 1);
	}

	else
	{
		serverName = url;
		filepath = "/";
		filename = "";
	}
}

SOCKET connectToServer(char *szServerName, WORD portNum)
{
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	SOCKET conn;

	conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (conn == INVALID_SOCKET)
		return NULL;

	if (inet_addr(szServerName) == INADDR_NONE)
	{
		hp = gethostbyname(szServerName);
	}
	else
	{
		addr = inet_addr(szServerName);
		hp = gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);
	}

	if (hp == NULL)
	{
		closesocket(conn);
		return NULL;
	}

	server.sin_addr.s_addr = *((unsigned long*)hp->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);
	if (connect(conn, (struct sockaddr*)&server, sizeof(server)))
	{
		closesocket(conn);
		return NULL;
	}
	return conn;
}

int getHeaderLength(char *content)
{
	const char *srchStr1 = "\r\n\r\n", *srchStr2 = "\n\r\n\r";
	char *findPos;
	int ofset = -1;

	findPos = strstr(content, srchStr1);
	if (findPos != NULL)
	{
		ofset = findPos - content;
		ofset += strlen(srchStr1);
	}

	else
	{
		findPos = strstr(content, srchStr2);
		if (findPos != NULL)
		{
			ofset = findPos - content;
			ofset += strlen(srchStr2);
		}
	}
	return ofset;
}

char *readUrl2(char *szUrl, long &bytesReturnedOut, char **headerOut)
{
	const int bufSize = 512;
	char readBuffer[bufSize], sendBuffer[bufSize], tmpBuffer[bufSize];
	char *tmpResult = NULL, *result;
	SOCKET conn;
	string server, filepath, filename;
	long totalBytesRead, thisReadSize, headerLen;

	mParseUrl(szUrl, server, filepath, filename);

	///////////// step 1, connect //////////////////////
	conn = connectToServer((char*)server.c_str(), 80);
	srand(time(0));
	int num = (rand() % 1234567890) + 1;
	///////////// step 2, send GET request /////////////
	sprintf(tmpBuffer, "GET %s?temp=%d HTTP/1.0", filepath.c_str(), num);
	strcpy(sendBuffer, tmpBuffer);
	strcat(sendBuffer, "\r\n");
	sprintf(tmpBuffer, "Host: %s", server.c_str());
	strcat(sendBuffer, tmpBuffer);
	strcat(sendBuffer, "\r\n");
	strcat(sendBuffer, "\r\n");
	send(conn, sendBuffer, strlen(sendBuffer), 0);

	///////////// step 3 - get received bytes ////////////////
	// Receive until the peer closes the connection
	totalBytesRead = 0;
	while (1)
	{
		memset(readBuffer, 0, bufSize);
		thisReadSize = recv(conn, readBuffer, bufSize, 0);

		if (thisReadSize <= 0)
			break;

		tmpResult = (char*)realloc(tmpResult, thisReadSize + totalBytesRead);

		memcpy(tmpResult + totalBytesRead, readBuffer, thisReadSize);
		totalBytesRead += thisReadSize;
	}

	headerLen = getHeaderLength(tmpResult);
	long contenLen = totalBytesRead - headerLen;
	result = new char[contenLen + 1];
	memcpy(result, tmpResult + headerLen, contenLen);
	result[contenLen] = 0x0;
	char *myTmp;

	myTmp = new char[headerLen + 1];
	strncpy(myTmp, tmpResult, headerLen);
	myTmp[headerLen] = NULL;
	delete(tmpResult);
	*headerOut = myTmp;

	bytesReturnedOut = contenLen;
	closesocket(conn);
	return(result);
}