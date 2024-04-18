#ifndef PROJECT_FUNCS_H
#define PROJECT_FUNCS_H
#include "structs.h"
#include "main.h"

int compareDates(Date date1,Date date2);
int compareHour(int hour1, int hour2);
int compareminute(int minute1, int minute2);
int compareTime(Hour time1 , Hour time2);
int compareTimeDate(Date date1, Date date2, Hour time1 , Hour time2);
int isValidName(char *str);
int isValidDate(int day, int month, int year);
int isValidHour(int hours, int minutes, int reservationType);

#endif
