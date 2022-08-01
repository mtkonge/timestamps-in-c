#ifndef DATE_H
#define DATE_H

typedef struct Date {
    int minute;
    int hour;
    int day;
    int month;
    int year;
} Date;

int which_month(int time, int dateInMonths[]);

int days_from_january_till_month(int dateInMonths[], int month);

Date date_encoder(int secondsFromEpoch, Date EPOCH, int dateInMonths[]);

void date_print(char text[], Date date);

#endif