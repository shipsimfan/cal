#include <los/console.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

const char* months[] = {
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December",
};

const int month_lengths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

extern int is_leap_year(long year);
extern long day_of_week(long month, long day, long year);

int get_month_length(int month, int year) {
    if (month == 1 && is_leap_year(year))
        return 29;

    return month_lengths[month];
}

int main() {
    time_t current_time_epoch = time(NULL);
    struct tm* date = gmtime(&current_time_epoch);

    int num_spaces = (20 - (strlen(months[date->tm_mon]) + 5)) / 2;

    for (int i = 0; i < num_spaces; i++)
        printf(" ");

    printf("%s %i\n", months[date->tm_mon], date->tm_year + 1900);
    printf("Su Mo Tu We Th Fr Sa\n");

    int starting_weekday = day_of_week(date->tm_mon + 1, 1, date->tm_year + 1900);
    for (int i = 0; i < starting_weekday; i++)
        printf("   ");

    int current_weekday = starting_weekday;
    int month_length = get_month_length(date->tm_mon, date->tm_year + 1900);
    for (int day = 1; day <= month_length; day++) {
        if (day == date->tm_mday) {
            console_set_foreground_rgb(0x00, 0x00, 0x00);
            console_set_background_rgb(0xFF, 0xFF, 0xFF);
        }

        printf("%2i", day);

        if (day == date->tm_mday) {
            console_set_foreground_rgb(0xFF, 0xFF, 0xFF);
            console_set_background_rgb(0x00, 0x00, 0x00);
        }

        printf(" ");

        current_weekday++;
        if (current_weekday == 7) {
            printf("\n");
            current_weekday = 0;
        }
    }

    if (current_weekday != 0)
        printf("\n");

    return 0;
}
