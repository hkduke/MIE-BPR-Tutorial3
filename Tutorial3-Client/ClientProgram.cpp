#include "stdafx.h"
#include "ClientProgram.h"


ClientProgram::ClientProgram(){
	this->client = new Client("80");
	this->io = new InputOutput();
}


ClientProgram::~ClientProgram(){
	if (this->client->close() == -1) {
		std::cout << "Error closing the client" << std::endl;
	}
	delete this->client;
	delete this->io;
}

void ClientProgram::run() {
	if (this->client->create() == -1) {
		return;
	}
	while (true) {
		Message m;
		io->getMessage(&m);
		if (m.op == Operations::EXIT) {
			return;
		}
		this->client->sendData((char*)&m, sizeof(m));

		this->client->receiveData((char *)&m, sizeof(m));

		io->showMessage(&m);
	}
}