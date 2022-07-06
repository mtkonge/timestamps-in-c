#include <stdio.h>
#include <string.h>
#include <time.h>
#include "timespan.h"

typedef struct Checks {
    time_t checkin_date;
    time_t checkout_date;
} Checks;





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
    time_t epochTime = time(NULL);
    int checkinTime;
    // Checks checks;
    TimeSpan timeSpan = { .hours = 20, .minutes = 12, .seconds = 29 };

    char buffer[128] = "";
    while (1) {
        printf("> ");
        fgets(buffer, 128, stdin);
        sanitize_input(buffer);
        if (!strncmp("checkin", buffer, 7)) {
            
            checkinTime = epochTime;
            timespan_print(timeSpan);

        }
        if (!strncmp("checkout", buffer, 8)) {
            timespan_decoder(&timeSpan);
            timeSpan.seconds += calc_checkout_time(epochTime, checkinTime);
            timespan_encoder(&timeSpan);
            timespan_print(timeSpan);
        }
        if (!strncmp("total", buffer, 5)) {
            

            // printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
    }
}
