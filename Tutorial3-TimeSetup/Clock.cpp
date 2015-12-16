#include "stdafx.h"
#include "Clock.h"


Clock::Clock() {
}


Clock::~Clock() {
}

int Clock::setTime(SYSTEMTIME st) {
	SYSTEMTIME time;
	GetSystemTime(&time);
	time.wMinute = st.wMinute;
	time.wHour = st.wHour;
	time.wDay = st.wDay;
	time.wMonth = st.wMonth;
	time.wYear = st.wYear;

	PrivilegeManager manager = PrivilegeManager();

	//if (manager.removePrivileges() == -1) {
	//	return -1;
	//}

	//if (manager.addPrivilege(SE_SYSTEMTIME_NAME) == -1) {
	//	return -1;
	//}

	//if (manager.removePrivilege(SE_SYSTEMTIME_NAME) == -1) {
	//	return -1;
	//}

	if (!SetSystemTime(&time)) {
		printf("SetSystemTime() failed with code %d\n", GetLastError());
		return -1;
	}

	
	return 0;

}
