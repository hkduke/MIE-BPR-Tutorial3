#pragma once

using namespace std;

class InputOutput{
	public:
		InputOutput();
		~InputOutput();

		static void getMessage(Message* m);
		static void showMessage(Message* m);
		
	private:
		static void getTime(Message* m);
		static void getDate(Message* m);
		static void getDatetime(Message* m);
		static int getNumber(string input);
		static bool isInteger(const string & s);
};

