#pragma once

typedef struct message {
	int op;

	int min;
	int hour;
	
	int day;
	int month;
	int year;
}Message;