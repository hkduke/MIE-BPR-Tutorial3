#include "stdafx.h"
#include "InputOutput.h"


InputOutput::InputOutput(){
}


InputOutput::~InputOutput(){
}

vector<string> split(const string &s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

void InputOutput::getMessage(Message* m) {
	
	int op = 0;
	while (op < Operations::GET_SYSTEM_TIME || op > Operations::EXIT) {
		cout << "1 - " << Operations::GET_SYSTEM_TIME_STRING << endl;
		cout << "2 - " << Operations::SET_SYSTEM_TIME_STRING << endl;
		cout << "3 - " << Operations::EXIT_STRING << endl;

		cout << "Enter the desired operation number: ";
		string input;
		getline(cin, input);
		op = InputOutput::getNumber(input);
		if (op == Operations::SET_SYSTEM_TIME) {
			InputOutput::getDatetime(m);
		}
	}
	m->op = op;
}

void InputOutput::getDate(Message* m) {
	using namespace boost::gregorian;
	string input;
	while (true) {
		cout << "Enter the date (dd-mm-yyyy) :";
		getline(cin, input);

		vector<string> splitedString = split(input, '-');
		if (splitedString.size() == 3) {
			try {
				date d(from_uk_string(input));
				m->day = d.day();
				m->month = d.month();
				m->year = d.year();
				return;
			}
			catch (out_of_range e){
				cout << "Invalid date ("<< e.what() <<"), please enter again" << endl;
			}
		}
		
	}
}

void InputOutput::getTime(Message* m) {
	string input;
	int min, hour;
	while (true) {
		cout << "Enter the Time (hh::mm) : ";
		getline(cin, input);

		vector<string> splitedString = split(input, ':');
		if (splitedString.size() == 2 && isInteger(splitedString[0]) && isInteger(splitedString[1])) {
			hour = InputOutput::getNumber(splitedString[0]);
			min = InputOutput::getNumber(splitedString[1]);
			if (hour > 0 && hour < 24 && min > 0 && min < 60) {
				m->min = min;
				m->hour = hour;
				return;
			}
			cout << "Invalid time, please retry" << endl;
		}

	}
}

void InputOutput::getDatetime(Message* m) {
	InputOutput::getDate(m);
	InputOutput::getTime(m);
}


bool InputOutput::isInteger(const string & s) {
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
	char * p;
	strtol(s.c_str(), &p, 10);
	return (*p == 0);
}

int InputOutput::getNumber(string input) {
	if (isInteger(input)) {
		string::size_type sz;
		int i_dec = stoi(input, &sz);
		return i_dec;
	}
	return -1;
}

void InputOutput::showMessage(Message* m) {
	if (m->op == Operations::GET_SYSTEM_TIME) {
		cout << "aca hay que mostrar la hora" << endl;
		InputOutput::showDatetime(m);
	}
	else if (m->op == Operations::SET_SYSTEM_TIME) {
		cout << "aca hay que decir si salio todo bien" << endl;
		if (m->result == 1) {
			cout << "The date and time has changed correctly" << endl;
			InputOutput::showDatetime(m);
		}
	}
	else if (m->op == Operations::EXIT) {
		cout << "Good Bye!" << endl;
	}

	cout << "=======================================================" << endl;
}

void InputOutput::showDatetime(Message* m) {
	cout << "The time is " << m->hour << ":" << m->min << endl;
	cout << "The date is " << m->day << "/" << m->month << "/" << m->year << endl;
}