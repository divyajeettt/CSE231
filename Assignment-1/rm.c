#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// int main() {
//     char *buf = (char *) malloc(100*sizeof(char));
//     buf = getlogin();
//     printf("%s \n", buf);
// }

// #include<stdio.h>
// #include<stdlib.h>

main() {
char *buf;
buf=(char *)malloc(10*sizeof(char));
cuserid(buf);
printf("\n %s \n",buf);
}