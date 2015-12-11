// MIE-BPR-Tutorial4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Server.h"

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

