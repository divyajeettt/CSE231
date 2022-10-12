#include <time.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

void getDate() {
    time_t now;
    time(&now);
    printf("%s", ctime(&now));

    char *buffer = (char *) malloc(256*sizeof(char));

    struct tm *ts = localtime(&now);
    // strftime(buffer, 256, "%a %Y-%m-%d %H:%M:%S %Z", ts);
    strftime(buffer, 256, "%a %b %d %H:%M:%S %p %Z %Y", ts);
    printf("%s\n", buffer);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    getDate();
    return 0;
}