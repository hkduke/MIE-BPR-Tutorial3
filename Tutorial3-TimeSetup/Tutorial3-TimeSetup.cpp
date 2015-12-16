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

	showTime();
	SYSTEMTIME st;
	if (argc > 1) {
		Parser::parseTime(string(argv[1]), &st);
	} else {
		return -1;
	}
	int res = Clock::setTime(st);
	showTime();
	return res;
}

