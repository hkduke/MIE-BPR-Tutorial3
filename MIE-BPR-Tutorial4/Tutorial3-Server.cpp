// MIE-BPR-Tutorial4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Server.h"


int main(){

	Worker w = Worker();
	w.run();

	system("pause");
    return 0;
}

