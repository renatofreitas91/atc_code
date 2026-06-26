#include "stdafx.h"
#include "stdafx.h"
#include <winhttp.h>

using std::string;


HINSTANCE hInst;


char* appVersion = getDynamicCharArrayFixedLenght((char*)"2.1.7 of 2026-06-09", 100);

#pragma comment(lib, "winhttp.lib")

std::string HttpGetRequest(const std::wstring& server, const std::wstring& path) {
	// Initialize WinHTTP session
	HINTERNET hSession = WinHttpOpen(L"WinHTTP Example/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	if (!hSession) {
		std::cerr << "Failed to open WinHTTP session\n";
		return "";
	}

	// Specify the target server and open a connection
	HINTERNET hConnect = WinHttpConnect(hSession, server.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);

	if (!hConnect) {
		std::cerr << "Failed to connect to server\n";
		WinHttpCloseHandle(hSession);
		return "";
	}

	// Create an HTTPS request handle
	HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path.c_str(),
		NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

	if (!hRequest) {
		std::cerr << "Failed to open request\n";
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return "";
	}

	// Send the request
	BOOL bResults = WinHttpSendRequest(hRequest,
		WINHTTP_NO_ADDITIONAL_HEADERS, 0,
		WINHTTP_NO_REQUEST_DATA, 0,
		0, 0);

	if (!bResults) {
		std::cerr << "Failed to send request\n";
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return "";
	}

	// Wait for the response
	bResults = WinHttpReceiveResponse(hRequest, NULL);
	if (!bResults) {
		std::cerr << "Failed to receive response\n";
	}
	else {
		// Read the response data
		DWORD dwSize = 0;
		DWORD dwDownloaded = 0;
		std::string response;

		do {
			// Check for available data
			dwSize = 0;
			WinHttpQueryDataAvailable(hRequest, &dwSize);

			if (dwSize > 0) {
				std::string chunk(dwSize, '\0');
				if (WinHttpReadData(hRequest, &chunk[0], dwSize, &dwDownloaded)) {
					chunk.resize(dwDownloaded);
					response += chunk;
				}
			}

		} while (dwSize > 0);

		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return response;
	}

	// Cleanup
	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);
	return 	"";
}




std::string getLocationFromHeader(const std::string& header) {
	// Search for the "Location" header
	std::string locationKey = "Location: ";
	size_t startPos = header.find(locationKey);

	// If "Location" header is found
	if (startPos != std::string::npos) {
		// Move the start position to the beginning of the value
		startPos += locationKey.length();

		// Find the end of the line (where the header value ends)
		size_t endPos = header.find("\r\n", startPos);
		if (endPos == std::string::npos) {
			endPos = header.find("\n", startPos);
		}

		// Extract the URL from the header
		return header.substr(startPos, endPos - startPos);
	}

	// If not found, return an empty string
	return "";
}

void check4Updates()
{
	printf("\nChecking for updates...\n");
	std::wstring server = L"advantrigoncalc.sourceforge.io";
	std::wstring path = L"/atc_version.html";

	// Perform the HTTP GET request

	std::string memBuffer = HttpGetRequest(server, path);
	size_t start = memBuffer.find("<p>");
	if (start != std::string::npos) {
		start += 3;
		size_t end = memBuffer.find('<', start);
		if (end == std::string::npos) {
			end = memBuffer.length();
		}
		char* currentVersion = getDynamicCharArray("", "currentVersion");
		std::string version = memBuffer.substr(start, end - start);
		sprintf(currentVersion, "%s", version.c_str());
		printf("\nCurrent version: %s\n", currentVersion);
		if (!isEqual(appVersion, currentVersion)) {
			printf("\n\nThere is an update available!\n\n");
			printf("\n\nYou can now ask by commands to download Advanced Trigonometry Calculator v%s!\n\n", currentVersion);
			printf("\nIf you want to update to the latest version. Enter the command(s) that best serve your desire:\n\n o \"update\" for Setup x86 \n o \"update x64\" for Setup x64 \n o \"update portable\" for Zip file. \n\nThanks for use Advanced Trigonometry Calculator!\n\n\n");
		}
		else {
			puts("\nYou have the latest version! :)\n");
		}
		_delete(currentVersion, "currentVersion");
		currentVersion = nullptr;
	}

}





