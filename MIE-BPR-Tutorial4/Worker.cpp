#include "stdafx.h"
#include "Worker.h"

using namespace std;

Worker::Worker(){
	string portString = readConfigurationFile();
	int port = atoi(portString.c_str());

	this->server = new Server(port);
	if (this->server->create() == -1) {
		cout << "Error creating the server" << endl;
	}
	cout << "Server running" << endl;
}


Worker::~Worker(){
	if (this->server->close() == -1) {
		cout << "Error closing the server" << endl;
	}
	delete this->server;
}

string Worker::readConfigurationFile() {
	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);
	wstringstream ss;
	ss << localAppData << L"\\Clock\\conf.txt";
	this->createConfigurationFile(localAppData);

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
	printf("The file conf.txt in the folder AppData/Clock does not exists, creating it...");

	this->createConfigurationFile(localAppData);

	return string("80");

}

int Worker::createConfigurationFile(const wchar_t* path) {
	wstringstream ss;
	ss << path << L"\\Clock";
	BOOL res = CreateDirectory(ss.str().c_str(), NULL);

	ss << "\\conf.txt";
	HANDLE h = CreateFile(ss.str().c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	
	string value = "80";
	DWORD dwBytesWritten = 0;
	WriteFile(h, value.c_str(), value.size(), &dwBytesWritten, NULL);

	CloseHandle(h);

	return 0;
}

void Worker::run() {
	while (true) {
		this->server->listenConnections();
		int resRec = 1;
		while (resRec > 0) {

			Message m;
			resRec = this->server->receiveData((char*)&m, sizeof(m));
			if (resRec == 0) break;
			std::cout << "El server recibe esta operacion " << m.op << std::endl;

			reply(&m);
			int resSent = this->server->sendData((char*)&m, sizeof(m));
		}
	}
}

void Worker::reply(Message* m) {
	if (m->op == Operations::GET_SYSTEM_TIME) {
		getSystemTime(m);
	}
	else if (m->op == Operations::SET_SYSTEM_TIME) {
		setSystemTime(m);
	}
}

void Worker::getSystemTime(Message* m) {
	SYSTEMTIME st;
	GetSystemTime(&st);
	m->min = st.wMinute;
	m->hour = st.wHour;
	m->day = st.wDay;
	m->month = st.wMonth;
	m->year = st.wYear;

	m->result = 1;
}

wstring s2ws(const std::string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

string Worker::serializeTime(Message* m) {
	stringstream ss;
	ss << m->min << '|' << m->hour << '|' << m->day << '|' << m->month << '|' << m->year; //min|hour|day|month|year
	return ss.str();
}

int showTime() {
	SYSTEMTIME st;
	GetSystemTime(&st);
	printf("The system time is: %02d:%02d %d/%d/%d\n", st.wHour, st.wMinute, st.wDay, st.wMonth, st.wYear);
	return 0;
}

void Worker::setSystemTime(Message* m) {
	string program = "..\\Debug\\Tutorial3-TimeSetup.exe";
	string newTime = serializeTime(m);
	
	wstring wline = s2ws(program);
	wstring wtime = s2ws(newTime);

	/*STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	GetStartupInfo(&si);
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	if (CreateProcess(NULL, (LPWSTR)wline.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) != 0) {
		::WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
	}*/

	SHELLEXECUTEINFO sinfo;
	memset(&sinfo, 0, sizeof(SHELLEXECUTEINFO));
	sinfo.cbSize = sizeof(SHELLEXECUTEINFO);
	sinfo.fMask = SEE_MASK_FLAG_DDEWAIT |
		SEE_MASK_NOCLOSEPROCESS;
	sinfo.hwnd = NULL;
	sinfo.lpFile = (LPCWSTR) wline.c_str();
	sinfo.lpParameters = (LPCWSTR) wtime.c_str();
	sinfo.lpVerb = _TEXT("runas"); // <<-- this is what makes a UAC prompt show up
	sinfo.nShow = SW_SHOW;
	int res = ShellExecuteEx(&sinfo);
	if (res != 0) {
		WaitForSingleObject(sinfo.hProcess, INFINITE);
		CloseHandle(sinfo.hProcess);
	}
	wprintf(L"shellexecuteex with error: %ld\n", WSAGetLastError());

	showTime();

	m->result = 1;
}