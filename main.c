#include <stdio.h>
#include <string.h>

typedef struct TimeStamp {
    int hours;
    int minutes;
    int seconds;
} TimeStamp;

void printTimeStamp(TimeStamp timeStamp)
{
    printf(
        "%d:%d:%d\n",
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

void TimeStampFromSeconds(TimeStamp timeStamp, int seconds)
{
    printf("not implemented");
}

int main()
{
    TimeStamp timeStamp = { .hours = 23, .minutes = 24, .seconds = 58 };
    char buffer[128] = "";
    printf("> ");
    fgets(buffer, 128, stdin);
    sanitizeInput(buffer);
    if (!strncmp("checkin", buffer, 7)) {
        printTimeStamp(timeStamp);
    }
    printf("you typed \"%s\"\n", buffer);
}
