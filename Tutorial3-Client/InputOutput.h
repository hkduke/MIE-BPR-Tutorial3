#pragma once

using namespace std;

class InputOutput{
	public:
		InputOutput();
		~InputOutput();

		void getMessage(Message* m);
		void showMessage(Message* m);
		
	private:
		void getTime(Message* m);
		void getDate(Message* m);
		void getDatetime(Message* m);
		int getNumber(string input);
		bool isInteger(const string & s);
		void showDatetime(Message* m);
		void selectFormat();

		int selectedFormat;
};

