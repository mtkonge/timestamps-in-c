#include "timespan.h"
#include <stdio.h>

void timespan_print(TimeSpan timeSpan)
{
    printf(
        "Your time: %d:%d:%d\n",
        timeSpan.hours,
        timeSpan.minutes,
        timeSpan.seconds);
}


void timespan_encoder(TimeSpan* timeSpan)
{
    timeSpan->minutes = timeSpan->minutes + timeSpan->seconds / 60 % 60;
    timeSpan->hours = timeSpan->hours + timeSpan->seconds / 3600;
    timeSpan->seconds = timeSpan->seconds % 60;
    


}

void timespan_decoder(TimeSpan* timeSpan)
{
    timeSpan->seconds = timeSpan->hours * 3600 + timeSpan->minutes * 60 + timeSpan->seconds;
    timeSpan->minutes = 0;
    timeSpan->hours = 0;
}