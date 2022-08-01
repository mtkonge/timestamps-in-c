#include "date.h"
#include <stdio.h>



int which_month(int time, int dateInMonths[]) {
    int days = time / 86400;
    for(int i = 0; i < 11; i++) {
        if (dateInMonths[i] == days) {
            return i+2;
        }
        if (days > dateInMonths[i]) {
            days -= dateInMonths[i];
            continue;
        }
        return i+1;
    }
    return 69;
}

int days_from_january_till_month(int dateInMonths[], int month) {
    int days = -1;
    for(int i = 0; i < month-1; i++) {
        days += dateInMonths[i];
    }

    return days;
}

Date date_encoder(int secondsFromEpoch, Date EPOCH, int dateInMonths[]) {
    
    Date currentDate = 
    {
        .year = EPOCH.year + secondsFromEpoch / 31557600,
        .month = which_month(secondsFromEpoch % 31557600, dateInMonths),
        .hour = 0,
        .minute = 0
    };

    currentDate.day = (secondsFromEpoch - (currentDate.year - EPOCH.year) * 31557600)/86400 - days_from_january_till_month(dateInMonths, currentDate.month);
    currentDate.hour = ((secondsFromEpoch - (currentDate.year - EPOCH.year) * 31557600) - (days_from_january_till_month(dateInMonths, currentDate.month) + currentDate.day)*86400)/3600;
    currentDate.minute = (((secondsFromEpoch - (currentDate.year - EPOCH.year) * 31557600) - (days_from_january_till_month(dateInMonths, currentDate.month) + currentDate.day)*86400) - currentDate.hour * 3600)/60;
    currentDate.hour += 2;
    return currentDate;
}

void date_print(char text[], Date date)
{
    printf(
        "%s: %d:%d:%d:%d:%d\n",
        text,
        date.hour,
        date.minute,
        date.day,
        date.month,
        date.year);
}