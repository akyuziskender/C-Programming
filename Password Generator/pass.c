#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    size_t i;
    FILE *fPtr;
    srand(time(NULL));
    int rand_number, amount_written;
    time_t now = time(NULL);  // getting the time since the Epoch (00:00:00 UTC, January 1, 1970), measured in seconds
    struct tm *t = localtime(&now);  // getting the local time
    char curr_time[26];  // a char array to hold the current time
    strftime(curr_time, sizeof(curr_time), "%d.%m.%Y %H:%M", t );
    char text[100];
    char pass[9];
    for(i = 0; i < 8; i++) {
        rand_number = rand() % 75;
        rand_number += 48;
        if(((rand_number>57) && (rand_number<65)) || ((rand_number>90) && (rand_number<97))) {
            i--;
        }
        else {
            pass[i] = rand_number;
        }
    }
    pass[8] = '\0';
    sprintf(text, "Password: %s --- Time: %s", pass, curr_time);
    printf("%s\n", text);
    fPtr = fopen("password.txt", "a");
    amount_written = fprintf(fPtr, "%s\n", text);
    if(amount_written < 0) puts("Error occured.");
    return 0;
}
