#pragma once

typedef struct message {
	long to;
	long from;
	int op;
	bool cont;
	int min;
	int hour;
	int day;
	int month;
	int year;
}Message;