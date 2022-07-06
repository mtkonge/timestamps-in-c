#ifndef TIME_STAMP_H
#define TIME_STAMP_H

typedef struct Timespan {
    int seconds;
    int minutes;
    int hours;
} TimeSpan;

void timespan_print(TimeSpan timeSpan);

void timespan_encoder(TimeSpan* timeSpan);

void timespan_decoder(TimeSpan* timeSpan);

#endif