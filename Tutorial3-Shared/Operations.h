#pragma once
class Operations {
public:
	static const int GET_SYSTEM_TIME = 1;
	static const int SET_SYSTEM_TIME = 2;
	static const int SELECT_FORMAT = 3;
	static const int EXIT = 4;

	static constexpr const char* GET_SYSTEM_TIME_STRING = "Get system time";
	static constexpr const char* SET_SYSTEM_TIME_STRING = "Set system time";
	static constexpr const char* SELECT_FORMAT_STRING = "Select format";
	static constexpr const char* EXIT_STRING = "Exit";

};