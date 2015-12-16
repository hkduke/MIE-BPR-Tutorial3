#include "stdafx.h"
#include "PrivilegeManager.h"


PrivilegeManager::PrivilegeManager(){
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		printf("OpenProcessToken() failed with code %d\n", GetLastError());
	}
}

PrivilegeManager::~PrivilegeManager(){
	CloseHandle(hToken);
}

BOOL PrivilegeManager::setPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege ) {
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue( NULL, lpszPrivilege, &luid)) {
		printf("LookupPrivilegeValue error: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if (!AdjustTokenPrivileges( hToken,	FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)) {
		printf("AdjustTokenPrivileges error: %u\n", GetLastError());
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
		printf("The token does not have the specified privilege. \n");
		return FALSE;
	}

	return TRUE;
}

BOOL PrivilegeManager::addPrivilege(LPCWSTR privilegeName) {
	return PrivilegeManager::setPrivilege(this->hToken, privilegeName, true);
}

BOOL PrivilegeManager::removePrivilege(LPCWSTR privilegeName) {
	return PrivilegeManager::setPrivilege(this->hToken, privilegeName , false);
}


int PrivilegeManager::removePrivileges() {
	TOKEN_PRIVILEGES originalTokenPrivileges;
	DWORD    dwSize = sizeof(TOKEN_PRIVILEGES);

	int res = AdjustTokenPrivileges(hToken, TRUE, NULL, NULL, NULL, NULL);

	if (! res) {
		printf("AdjustTokenPrivileges() failed with code %d\n", GetLastError());
		return -1;
	}
}