#pragma once
class PrivilegeManager{
	public:
		PrivilegeManager();
		~PrivilegeManager();

		BOOL addPrivilege(LPCWSTR privilegeName);
		BOOL removePrivilege(LPCWSTR privilegeName);
		int removePrivileges();
		BOOL setPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);

	private:
		HANDLE hToken;
		TOKEN_PRIVILEGES originalTokenPrivileges;
};

