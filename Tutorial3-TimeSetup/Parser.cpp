#include "stdafx.h"
#include "Parser.h"

char Parser::delimiter = '|';

Parser::Parser(){
}


Parser::~Parser(){
}

vector<string> Parser::split(const string &s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

void Parser::parseTime(string timeString, SYSTEMTIME* st) {
	vector<string> att = Parser::split(timeString, Parser::delimiter);
	string min = att[0];
	string hour = att[1];
	string day = att[2];
	string month = att[3];
	string year = att[4];

	st->wMinute = stoi(min);
	st->wHour = stoi(hour);
	st->wDay = stoi(day);
	st->wMonth = stoi(month);
	st->wYear = stoi(year);
}