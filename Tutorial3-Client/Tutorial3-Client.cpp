// Tutorial3-Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib, "Ws2_32.lib")


int main() {
	printf("soy el clientillo \n");

	Message mSent;
	//InputOutput::getMessage(&mSent);
	mSent.op = 12;

	Client c = Client("80");
	int res = c.create();
	
	std::cout << "El cliente manda esta operacion" << mSent.op << std::endl;
	int resSend = c.sendData((char*) &mSent, sizeof(mSent));

	Message mRec;
	int resRec = c.receiveData((char *) &mRec, sizeof(mRec));
	std::cout << "El cliente recibe esta operacion" << mRec.op << std::endl;

	system("pause");

    return 0;
}

