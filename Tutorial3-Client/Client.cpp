#include "stdafx.h"
#include "Client.h"


Client::Client(char* port) {
	this->port = port;
	this->theSocket = INVALID_SOCKET;
}

Client::~Client(){

}

int Client::create() {
	WSADATA wsaData;
	struct addrinfo *result = NULL, *ptr = NULL;
	struct addrinfo hints;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return -1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("127.0.0.1", this->port, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return -1;
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		this->theSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (this->theSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return -1;
		}

		iResult = connect(this->theSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(this->theSocket);
			this->theSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (this->theSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return -1;
	}
	return 0;
}

int Client::sendData(char* data, int size) {
	int iResult;
	iResult = send(this->theSocket, data, size, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(this->theSocket);
		WSACleanup();
		return -1;
	}
	return iResult;
}

int Client::receiveData(char* buffer, int size) {
	int iResult = recv(this->theSocket, buffer, size, 0);
	
	if (iResult == 0) printf("Connection closed\n");
	else if (iResult < 0) printf("recv failed with error: %d\n", WSAGetLastError());

	return iResult;
}


int Client::close() {
	int iResult;
	// shutdown the connection since no more data will be sent
	iResult = shutdown(this->theSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(this->theSocket);
		WSACleanup();
		return -1;
	}
	// cleanup
	closesocket(this->theSocket);
	WSACleanup();
	return 0;
}