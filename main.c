#include <stdio.h>
#include <string.h>
#include <time.h>
#include "timespan.h"
#include <stdbool.h>


typedef struct Initializer {
     bool isInitialized;
     time_t value;
}Initializer;

typedef struct Checks {
    Initializer checkin_date[8];
    Initializer checkout_date[8];
} Checks;

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

int which_month(int time, int dateInMonths[]) {
    int days = time / 86400;
    for (int i = 0; i < 11; i++) {
        if (days > dateInMonths[i]) {
            days -= dateInMonths[i];
            continue;
        }
        return i+1;
    }
    return 69;
}

Date date_encoder(int secondsFromEpoch, Date EPOCH, int dateInMonths[]) {
    Date currentDate = 
    {
        .year = EPOCH.year + secondsFromEpoch / 31557600,
        .month = which_month(secondsFromEpoch % 31557600, dateInMonths),
        .day = 0
    };
    return currentDate;
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
    Checks checks;
    int checkout_length = sizeof checks.checkout_date / sizeof *checks.checkout_date;
    TimeSpan timeSpan = { .hours = 0, .minutes = 0, .seconds = 0 };
    int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    #define Date EPOCH = {.day = 1, .month = 1, .year = 1970};
    

    for (int i = 0; i < checkout_length; i++) {
        checks.checkout_date[i].isInitialized = false;     
    }

    char buffer[128] = "";
    while (1) {
        printf("> ");
        fgets(buffer, 128, stdin);
        sanitize_input(buffer);
        if (!strncmp("checkin", buffer, 7)) {
            int something = time(NULL);
            printf("%d\n", something);
            checkinTime = time(NULL);
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
                if (checks.checkout_date[i].isInitialized == true)
                    printf("%ld\n", checks.checkout_date[i].value);
            }
        }
    }
}
