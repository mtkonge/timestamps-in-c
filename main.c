#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct TimeStamp {
    int seconds;
    int minutes;
    int hours;
} TimeStamp;

void printTimeStamp(TimeStamp timeStamp)
{
    printf(
        "Your time: %d:%d:%d\n",
        timeStamp.hours,
        timeStamp.minutes,
        timeStamp.seconds);
}

void sanitizeInput(char buffer[128])
{
    for (int i = 0; i < strlen(buffer); i++)
        if (buffer[i] == '\n')
            buffer[i] = '\0';
}

void timestamp_encoder(TimeStamp* timeStamp)
{
    timeStamp->minutes = timeStamp->minutes + timeStamp->seconds / 60 % 60;
    timeStamp->hours = timeStamp->hours + timeStamp->seconds / 3600;
    timeStamp->seconds = timeStamp->seconds % 60;
}
void timestamp_decoder(TimeStamp* timeStamp)
{
    timeStamp->seconds = timeStamp->hours * 3600 + timeStamp->minutes * 60 + timeStamp->seconds;
    timeStamp->minutes = 0;
    timeStamp->hours = 0;
}

int secondsSinceEpoch()
{
    return time(NULL);
}

int calcCheckoutTime(int seconds)
{
    return secondsSinceEpoch() - seconds;
}

int main()
{
    int checkinTime;
    TimeStamp timeStamp = { .hours = 20, .minutes = 12, .seconds = 29 };
    char buffer[128] = "";
    while (1) {
        printf("> ");
        fgets(buffer, 128, stdin);
        sanitizeInput(buffer);
        if (!strncmp("checkin", buffer, 7)) {
            checkinTime = secondsSinceEpoch();
            printTimeStamp(timeStamp);
        }
        if (!strncmp("checkout", buffer, 8)) {
            timestamp_decoder(&timeStamp);
            timeStamp.seconds += calcCheckoutTime(checkinTime);
            timestamp_encoder(&timeStamp);
            printTimeStamp(timeStamp);
        }
    }
}
