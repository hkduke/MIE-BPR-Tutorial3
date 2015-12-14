#include "stdafx.h"
#include "ClientProgram.h"


ClientProgram::ClientProgram(){
	this->client = new Client("80");
	if (this->client->create() == -1) {
		std::cout << "Error creating the client." << std::endl;
	}
}


ClientProgram::~ClientProgram(){
	if (this->client->close() == -1) {
		std:cout << "Error closing the client" << std::endl;
	}
	delete this->client;
}

void ClientProgram::run() {
	while (true) {
		Message m;
		InputOutput::getMessage(&m);
		if (m.op == Operations::EXIT) {
			std::cout << "chau gracias por usar este gran programa" << std::endl;
			return;
		}
		this->client->sendData((char*)&m, sizeof(m));

		this->client->receiveData((char *)&m, sizeof(m));

		InputOutput::showMessage(&m);
	}
}