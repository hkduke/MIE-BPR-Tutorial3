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
	//----------------------
	// Create a SOCKET for listening for incoming connection requests.
	this->theSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->theSocket == INVALID_SOCKET) {
		wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
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
	//----------------------
	// Listen for incoming connection requests 
	// on the created socket
	if (listen(this->theSocket, SOMAXCONN) == SOCKET_ERROR) {
		wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
		return -1;
	}
	wprintf(L"Listening on socket...\n");

	//WSACleanup();
	return 0;
}

int Server::listenConnections() {
	
	//SOCKET AcceptSocket;
	wprintf(L"Waiting for client to connect...\n");

	//----------------------
	// Accept the connection.
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

int Server::sendData(string data) {
	int iSendResult = 0;
	iSendResult = send(this->clientSocket, data.c_str(), data.length(), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return -1;
	}
	printf("Bytes sent: %d\n", iSendResult);
	return iSendResult;
}

string Server::receiveData() {
	int iResult = 0;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	iResult = recv(this->clientSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		printf("Bytes received: %d\n", iResult);
	}
	string res = (string(recvbuf));
	res.resize(iResult);
	return res;
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