// MIE-BPR-Tutorial4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Server.h"

int changeTime(const SYSTEMTIME time) {
	HANDLE      hToken;     /* process token */
	TOKEN_PRIVILEGES tp;    /* token provileges */
	TOKEN_PRIVILEGES oldtp;    /* old token privileges */
	DWORD    dwSize = sizeof(TOKEN_PRIVILEGES);
	LUID     luid;
	
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)){
		printf("OpenProcessToken() failed with code %d\n", GetLastError());
		return 1;
	}
	if (!LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &luid)) {
		printf("LookupPrivilege() failed with code %d\n", GetLastError());
		CloseHandle(hToken);
		return 1;
	}

	ZeroMemory(&tp, sizeof(tp));
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	/* Adjust Token privileges */
	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES),
		&oldtp, &dwSize))
	{
		printf("AdjustTokenPrivileges() failed with code %d\n", GetLastError());
		CloseHandle(hToken);
		return 1;
	}
	/* Set time */
	if (!SetSystemTime(&time)){
		printf("SetSystemTime() failed with code %d\n", GetLastError());
		CloseHandle(hToken);
		return 1;
	}

	/* disable SE_SYSTEMTIME_NAME again */
	AdjustTokenPrivileges(hToken, FALSE, &oldtp, dwSize, NULL, NULL);
	if (GetLastError() != ERROR_SUCCESS){
		printf("AdjustTokenPrivileges() failed with code %d\n", GetLastError());
		CloseHandle(hToken);
		return 1;
	}

	CloseHandle(hToken);

}

int showTime() {
	SYSTEMTIME st;

	GetSystemTime(&st);
	printf("The system time is: %02d:%02d\n", st.wHour, st.wMinute);
	return 0;
}

string readConfigurationFile() {
	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);
	wstringstream ss;
	ss << localAppData << L"\\Clock\\conf.txt";

	ifstream file;
	file.open(ss.str().c_str());
	if (file) {
		char output[100];
		if (file.is_open()) {
			while (!file.eof()) {
				file >> output;
			}
		}
		file.close();
		CoTaskMemFree(static_cast<void*>(localAppData));
		return string(output);
	}
	printf("el archivo no existe");
	return string("80");
	
}

int main(){
	showTime();

	SYSTEMTIME st;
	GetSystemTime(&st);
	//st.wHour++;
	changeTime(st);
	showTime();

	string portString = readConfigurationFile();
	int port = atoi(portString.c_str());
	Server s = Server(port);
	int res = s.create();
	
	s.listenConnections();

	string receivedata = s.receiveData();
	std::cout << "recibi esto wacho " << receivedata << std::endl;

	s.sendData("puto");


	system("pause");
    return 0;
}

