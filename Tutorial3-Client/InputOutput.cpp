#include "stdafx.h"
#include "InputOutput.h"


InputOutput::InputOutput(){
	this->selectedFormat = 1;
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
		cout << Operations::GET_SYSTEM_TIME << " - " << Operations::GET_SYSTEM_TIME_STRING << endl;
		cout << Operations::SET_SYSTEM_TIME << " - " << Operations::SET_SYSTEM_TIME_STRING << endl;
		cout << Operations::SELECT_FORMAT << " - " << Operations::SELECT_FORMAT_STRING << endl;
		cout << Operations::EXIT<<" - " << Operations::EXIT_STRING << endl;

		cout << "Enter the desired operation number: ";
		string input;
		getline(cin, input);
		op = this->getNumber(input);
		if (op == Operations::SET_SYSTEM_TIME) {
			this->getDatetime(m);
		}
	}
	cout << "-------------------------------------------------------" << endl;

	if (op == Operations::EXIT) cout << "Good Bye!" << endl;

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
			hour = this->getNumber(splitedString[0]);
			min = this->getNumber(splitedString[1]);
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
	this->getDate(m);
	this->getTime(m);
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
		this->showDatetime(m);
	}
	else if (m->op == Operations::SET_SYSTEM_TIME) {
		if (m->result == 0) {
			cout << "The date and time has changed correctly" << endl;
			this->showDatetime(m);
		}
		else {
			cout << "There was a problem changing the date and the time" << endl;
		}
	}
	else if (m->op == Operations::SELECT_FORMAT) {
		this->selectFormat();
	}

	cout << "=======================================================" << endl;
}

void InputOutput::selectFormat() {
	while (true) {
		cout << "Select the desired format of the date" << endl;
		cout << "1 - DD-MM-YYYY (31-01-2002)" << endl;
		cout << "2 - YYYY-mmm-DD (2002 - Jan - 01)" << endl;
		cout << "3 - YYYYMMDD (20020131)" << endl;
		cout << "4 - YYYY-MM-DD (2002-01-31)" << endl;
		string input;
		getline(cin, input);
		int op = this->getNumber(input);
		if (op >= 1 && op <= 4) {
			this->selectedFormat = op;
			break;
		}
	}
}

void InputOutput::showDatetime(Message* m) {
	using namespace boost::gregorian;
	cout << "The time is " << m->hour << ":" << m->min << endl;
	stringstream ss;
	ss << m->day << "-" << m->month << "-" << m->year;
	date d(from_uk_string(ss.str()));
	if (this->selectedFormat == 2) cout << "The date is " << to_simple_string(d) << endl;
	else if (this->selectedFormat == 3) cout << "The date is " << to_iso_string(d) << endl;
	else if (this->selectedFormat == 4) cout << "The date is " << to_iso_extended_string(d) << endl;
	else cout << "The date is " << m->day << "/" << m->month << "/" << m->year << endl;
}