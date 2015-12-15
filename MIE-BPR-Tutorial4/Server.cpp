#include "stdafx.h"
#include "Server.h"

#define DEFAULT_BUFLEN 512


Server::Server(int port){
	this->port = port;
	this->theSocket = INVALID_SOCKET;
	this->clientSocket = INVALID_SOCKET;
}

Server::~Server(){

}

int Server::create() {
	WSADATA wsaData;
	int iResult = 0;

	sockaddr_in service;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup() failed with error: %d\n", iResult);
		return -1;
	}

	this->theSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->theSocket == INVALID_SOCKET) {
		wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(this->port);

	iResult = bind(this->theSocket, (SOCKADDR *)& service, sizeof(service));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"bind function failed with error %d\n", WSAGetLastError());
		iResult = closesocket(this->theSocket);
		if (iResult == SOCKET_ERROR)
			wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	if (listen(this->theSocket, SOMAXCONN) == SOCKET_ERROR) {
		wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
		return -1;
	}

	return 0;
}

int Server::listenConnections() {
	this->clientSocket = accept(this->theSocket, NULL, NULL);
	if (this->clientSocket == INVALID_SOCKET) {
		wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
		closesocket(this->theSocket);
		WSACleanup();
		return 1;
	}
	else
		wprintf(L"Client connected.\n");

	return 0;
}

int Server::sendData(char* data, int size) {
	int iSendResult = 0;
	iSendResult = send(this->clientSocket, data, size, 0);
	if (iSendResult == SOCKET_ERROR) {
		wprintf(L"send failed with error: %ld\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return -1;
	}
	return iSendResult;
}

int Server::receiveData(char* buffer, int size) {
	int iResult = 0;
	iResult = recv(this->clientSocket, buffer, size, 0);
	if (iResult < 0) {
		printf("Error in recv: %d\n", iResult);
	}
	return iResult;
}


int Server::close() {
	int iResult = closesocket(this->theSocket);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	return 0;
}