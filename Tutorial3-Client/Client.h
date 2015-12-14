#pragma once

class Client
{
	public:
		Client(char* port);
		~Client();

		int create();
		int sendData(char* data, int size);
		int receiveData(char* buffer, int size);
		int close();

	private:
		char* port;
		SOCKET theSocket;
};

