#pragma once
class PrivilegeManager{
	public:
		PrivilegeManager();
		~PrivilegeManager();

		int addPrivilege(LPCWSTR privilegeName);
		int removePrivileges();

	private:
		HANDLE hToken;
		TOKEN_PRIVILEGES originalTokenPrivileges;
};

