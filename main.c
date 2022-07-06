#include <stdio.h>
#include <string.h>

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

void timestamp_hours(TimeStamp* timeStamp)
{

    timeStamp->minutes = (int)timeStamp->seconds / 60 % 60;
    timeStamp->hours = (int)timeStamp->seconds / 60 / 60;
    timeStamp->seconds = timeStamp->seconds % 60;    

}

int main()
{
    TimeStamp timeStamp = {.seconds = 28394 };
    char buffer[128] = "";
    printf("> ");
    fgets(buffer, 128, stdin);
    sanitizeInput(buffer);
    if (!strncmp("checkin", buffer, 7)) {
        timestamp_hours(&timeStamp);
        printTimeStamp(timeStamp);
    }
}
