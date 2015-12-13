#pragma once
class Clock{
public:
	Clock();
	~Clock();

	static int setTime(SYSTEMTIME st);
};

