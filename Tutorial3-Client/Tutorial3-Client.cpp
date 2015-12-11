// Tutorial3-Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"

#pragma comment(lib, "Ws2_32.lib")


int main() {
	printf("soy el clientillo \n");

	Client c = Client("80");
	int res = c.create();
	int res2 = c.sendData("hola");
	string s = c.receiveData();
	std::cout << "recibi esto wacho " << s << std::endl;

	system("pause");

    return 0;
}

