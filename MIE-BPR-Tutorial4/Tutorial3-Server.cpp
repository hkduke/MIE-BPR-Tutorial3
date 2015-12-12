// MIE-BPR-Tutorial4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Server.h"

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

std::wstring s2ws(const std::string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

int callProcessToChangeTime() {
	string program = "Tutorial3-TimeSetup.exe";
	string newTime = "40|13|12|3|2013";//min|hour|day|month|year

	string line = program + " " + newTime;
	wstring wline = s2ws(line);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	GetStartupInfo(&si);
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	if (CreateProcess(NULL, (LPWSTR) wline.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) != 0) {
		::WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
	}

	return 0;
}


int main(){
	callProcessToChangeTime();
	string portString = readConfigurationFile();
	int port = atoi(portString.c_str());
	Server s = Server(port);
	int res = s.create();
	
	s.listenConnections();

	string receivedata = s.receiveData();
	std::cout << "El server recibe esto " << receivedata << std::endl;

	s.sendData("puto");


	system("pause");
    return 0;
}

