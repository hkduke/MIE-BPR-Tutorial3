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

int main(){
	showTime();

	Server s = Server(80);
	int res = s.create();
		
	printf("%d", res);

	s.listenConnections();

	string receivedata = s.receiveData();
	std::cout << "recibi esto wacho " << receivedata << std::endl;

	s.sendData("puto");


	system("pause");
    return 0;
}

