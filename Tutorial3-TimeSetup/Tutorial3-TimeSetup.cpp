// Tutorial3-TimeSetup.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;


int showTime() {
	SYSTEMTIME st;
	GetSystemTime(&st);
	printf("The system time is: %02d:%02d %d/%d/%d\n", st.wHour, st.wMinute, st.wDay, st.wMonth , st.wYear);
	return 0;
}

int main(int argc, char *argv[]) {

	printf("argc = %d \n", argc);
	for (int i = 0; i < argc; i++) {
		std::cout << "argv[" << i << "] = " << std::string(argv[i]) << std::endl;
	}

	showTime();
	SYSTEMTIME st;
	if (argc > 1) {
		Parser::parseTime(string(argv[1]), &st);
	} else {
		Parser::parseTime(string("59|23|23|12|1864"), &st);
	}
	Clock::setTime(st);
	showTime();

	system("pause");

    return 0;
}

