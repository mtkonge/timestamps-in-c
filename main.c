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
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
} Date;

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
    TimeSpan timeSpan = { .hours = 20, .minutes = 12, .seconds = 29 };
    

    for (int i = 0; i < checkout_length; i++) {
        checks.checkout_date[i].isInitialized = false;     
    }

    char buffer[128] = "";
    while (1) {
        printf("> ");
        fgets(buffer, 128, stdin);
        sanitize_input(buffer);
        if (!strncmp("checkin", buffer, 7)) {
            
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
            int checkout_length = sizeof checks.checkout_date / sizeof *checks.checkout_date;
            for (int i = 0; i < checkout_length; i++) {
                if (checks.checkout_date[i].isInitialized == true)
                    printf("%ld\n", checks.checkout_date[i].value);
            }
            // printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
    }
}
