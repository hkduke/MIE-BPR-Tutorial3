#pragma once

#include "stdafx.h"

using namespace std;

class Parser{
	public:
		Parser();
		~Parser();

		static void parseTime(string str, SYSTEMTIME* st);

	private:
		static char delimiter;
		static vector<string> split(const string &s, char delim);

};

