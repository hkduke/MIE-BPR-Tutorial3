#include "stdafx.h"
#include "PrivilegeManager.h"


PrivilegeManager::PrivilegeManager(){
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		printf("OpenProcessToken() failed with code %d\n", GetLastError());
	}
}


PrivilegeManager::~PrivilegeManager(){
	CloseHandle(hToken);
}

BOOL SetPrivilege(
	HANDLE hToken,          // access token handle
	LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
	BOOL bEnablePrivilege   // to enable or disable privilege
	)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(
		NULL,            // lookup privilege on local system
		lpszPrivilege,   // privilege to lookup 
		&luid))        // receives LUID of privilege
	{
		printf("LookupPrivilegeValue error: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// Enable the privilege or disable all privileges.

	if (!AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		printf("AdjustTokenPrivileges error: %u\n", GetLastError());
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)

	{
		printf("The token does not have the specified privilege. \n");
		return FALSE;
	}

	return TRUE;
}

int PrivilegeManager::addPrivilege(LPCWSTR privilegeName) {
	SetPrivilege(this->hToken, privilegeName, true);
	/*TOKEN_PRIVILEGES tp;
	DWORD    dwSize = sizeof(TOKEN_PRIVILEGES);
	LUID     luid;

	if (!LookupPrivilegeValue(NULL, privilegeName, &luid)) {
		printf("LookupPrivilege() failed with code %d\n", GetLastError());
		return -1;
	}

	ZeroMemory(&tp, sizeof(tp));
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), &originalTokenPrivileges, &dwSize)) {
		printf("AdjustTokenPrivileges() failed with code %d\n", GetLastError());
		return -1;
	}
	*/
	return 0;
}

int PrivilegeManager::removePrivileges() {
	/*DWORD    dwSize = sizeof(TOKEN_PRIVILEGES);
	AdjustTokenPrivileges(hToken, FALSE, &originalTokenPrivileges, dwSize, NULL, NULL);
	if (GetLastError() != ERROR_SUCCESS) {
		printf("AdjustTokenPrivileges() failed with code %d\n", GetLastError());
		return -1;
	}*/
	SetPrivilege(this->hToken, SE_SYSTEMTIME_NAME, false);
	return 0;
}
