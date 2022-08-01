#include <stdio.h>
#include <string.h>
#include <time.h>
#include "timespan.h"
#include <stdbool.h>


typedef struct Date {
    int day;
    int month;
    int year;
} Date;

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
    };

    currentDate.day = (secondsFromEpoch - (currentDate.year - EPOCH.year) * 31557600)/86400 - days_from_january_till_month(dateInMonths, currentDate.month) ;
    return currentDate;
}

void date_print(char text[], Date date)
{
    printf(
        "%s: %d:%d:%d\n",
        text,
        date.day,
        date.month,
        date.year);
}

void sanitize_input(char buffer[128])
{
    for (int i = 0; i < strlen(buffer); i++)
        if (buffer[i] == '\n')
            buffer[i] = '\0';
}

int calc_checkout_time(time_t epochTime, int seconds)
{
    return epochTime - seconds;
}

int main()
{
    int checkinTime;
    TimeSpan timeSpan = { .hours = 0, .minutes = 0, .seconds = 0 };
    int dateCounter = 0;
    Date history[64] = {{.day = 0, .month = 0, .year = 0}};
    int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Date EPOCH = {.day = 1, .month = 1, .year = 1970};
    
    char buffer[128] = "";
    while (1) {
        printf("> ");
        fgets(buffer, 128, stdin);
        sanitize_input(buffer);
        if (!strncmp("checkin", buffer, 7)) {
            checkinTime = time(NULL);
            history[dateCounter] = date_encoder(checkinTime, EPOCH, daysInMonths);
            date_print("You checked in at", history[dateCounter]);
            dateCounter++;
        }
        if (!strncmp("checkout", buffer, 8)) {
            timespan_decoder(&timeSpan);
            timeSpan.seconds += calc_checkout_time(time(NULL), checkinTime);
            timespan_encoder(&timeSpan);
            history[dateCounter] = date_encoder(checkinTime, EPOCH, daysInMonths);
            date_print("You checked out at", history[dateCounter]);
            dateCounter++;
            timespan_print(timeSpan);
        }
        if (!strncmp("history", buffer, 7)) {
            int historyLength = sizeof history / sizeof *history;
            for (int i = 0; i < historyLength; i++) {
                if (history[i].year == 0) {
                    break;
                }
                if (i % 2)
                date_print("checkout", history[i]);
                else {
                date_print("checkin", history[i]);
                }
                
            }
        }
    }
}
