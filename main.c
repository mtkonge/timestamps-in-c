#include <stdio.h>
#include <string.h>
#include <time.h>
#include "timespan.h"
#include <stdbool.h>


typedef struct Initializer {
     bool isInitialized;
     time_t value;
}Initializer;

typedef struct CheckinData {
    Initializer checkin_date[8];
    Initializer checkout_date[8];
} CheckinData;

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

int which_month(int time, int dateInMonths[]) {
    int days = time / 86400;
    for(int i = 0; i < 11; i++) {
        if (days > dateInMonths[i]) {
            days -= dateInMonths[i];
            continue;
        }
        return i+1;
    }
    return 69;
}

int days_from_january_till_month(int dateInMonths[], int month) {
    int days = 0;
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

    currentDate.day = (secondsFromEpoch % 31557600 - (days_from_january_till_month(dateInMonths, currentDate.month)))/86400;

    return currentDate;
}

void date_print(Date date)
{
    printf(
        "Your time: %d:%d:%d\n",
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
    CheckinData checkinData;
    int checkout_length = sizeof checkinData.checkout_date / sizeof *checkinData.checkout_date;
    TimeSpan timeSpan = { .hours = 0, .minutes = 0, .seconds = 0 };
    Date date = {.day = 0, .month = 0, .year = 0};
    int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Date EPOCH = {.day = 1, .month = 1, .year = 1970};
    
    

    for (int i = 0; i < checkout_length; i++) {
        checkinData.checkout_date[i].isInitialized = false;     
    }

    char buffer[128] = "";
    while (1) {
        printf("> ");
        fgets(buffer, 128, stdin);
        sanitize_input(buffer);
        if (!strncmp("checkin", buffer, 7)) {
            checkinTime = time(NULL);
            date = date_encoder(checkinTime, EPOCH, daysInMonths);
            date_print(date);
            timespan_print(timeSpan);
        }
        if (!strncmp("checkout", buffer, 8)) {
            timespan_decoder(&timeSpan);
            timeSpan.seconds += calc_checkout_time(time(NULL), checkinTime);
            timespan_encoder(&timeSpan);
            timespan_print(timeSpan);
        }
        if (!strncmp("total", buffer, 5)) {
            for (int i = 0; i < checkout_length; i++) {
                if (checkinData.checkout_date[i].isInitialized == true)
                    printf("%ld\n", checkinData.checkout_date[i].value);
            }
        }
    }
}
