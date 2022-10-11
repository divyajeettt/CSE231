#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    if (remove("a.exe") == 0) {
        printf("Deleted");
    } else {
        printf("Not deleted");
    }
    return 0;
}