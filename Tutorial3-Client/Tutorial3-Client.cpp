// Tutorial3-Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib, "Ws2_32.lib")


int main() {
	printf("soy el clientillo \n");

	ClientProgram cp = ClientProgram();
	cp.run();

	system("pause");

    return 0;
}

