#include <stdio.h>
#include <string.h>
#include <time.h>
#include "timespan.h"
#include <stdbool.h>
#include "date.h"

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
    bool hasCheckedIn = false;
    
    char buffer[128] = "";
    while (1) {
        printf("> ");
        fgets(buffer, 128, stdin);
        sanitize_input(buffer);
        if (!strncmp("checkin", buffer, 7)) {
            if (!hasCheckedIn) {
            checkinTime = time(NULL);
            history[dateCounter] = date_encoder(checkinTime, EPOCH, daysInMonths);
            date_print("You checked in at", history[dateCounter]);
            dateCounter++;
            hasCheckedIn = true;
            }
            else {
                printf("You already have checked in\n");
            }
        }
        if (!strncmp("checkout", buffer, 8)) {
            if (hasCheckedIn) {
            timespan_decoder(&timeSpan);
            timeSpan.seconds += calc_checkout_time(time(NULL), checkinTime);
            timespan_encoder(&timeSpan);
            history[dateCounter] = date_encoder(checkinTime, EPOCH, daysInMonths);
            date_print("You checked out at", history[dateCounter]);
            dateCounter++;
            timespan_print(timeSpan);
            hasCheckedIn = false;

            }
            else {
                printf("You have not checked in\n");
            }
        }
        if (!strncmp("history", buffer, 7)) {
            int historyLength = sizeof history / sizeof *history;
            for (int i = 0; i < historyLength; i++) {
                if (history[i].year == 0) {
                    break;
                }
                if (i % 2)
                date_print("checkout", history[i]);
                else 
                date_print("checkin", history[i]);
                
            }
            timespan_print(timeSpan);
        }
    }
}
