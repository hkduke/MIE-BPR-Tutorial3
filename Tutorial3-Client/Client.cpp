#include "stdafx.h"
#include "Client.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "80"


Client::Client(int port) {
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
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return -1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return -1;
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		// Create a SOCKET for connecting to server
		this->theSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (this->theSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return -1;
		}

		// Connect to server.
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

int Client::sendData(string buffer) {
	char *sendbuf = "this is a test";
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	// Send an initial buffer
	iResult = send(this->theSocket, buffer.c_str(), (int)buffer.length(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(this->theSocket);
		WSACleanup();
		return -1;
	}
	printf("Bytes Sent: %ld\n", iResult);
	return iResult;
}

string Client::receiveData() {
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = recv(this->theSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed with error: %d\n", WSAGetLastError());

	string res = (string(recvbuf));
	res.resize(iResult);
	return res;
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