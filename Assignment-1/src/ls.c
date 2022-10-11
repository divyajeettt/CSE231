#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int ls() {

}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    printf("OH MA G INSIDE %s \n", argv[0]);

    char *cwd = (char *) malloc(256*sizeof(char));
    getcwd(cwd, 256);

    printf("%s \n", cwd);
    return 0;
}