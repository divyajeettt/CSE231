#define N 50
#define CHUNK 5
#define LENGTH 10
#define SOCKET "./crimge.socket"
#define FIFO "./crimge-fifo"
#define SHM "./crimge-shm"


char **generateStrings()
{
    char **strings = (char **) malloc(N*sizeof(char *));
    for (int i = 0; i < N; i++)
    {
        strings[i] = (char *) malloc(LENGTH*sizeof(char));
        for (int j = 0; j < LENGTH; j++)
        {
            strings[i][j] = 'a' + rand() % 26;
        }
    }
    return strings;
}


int toInt(char *buffer)
{
    int num = 0;
    num += ((int) (buffer[0] - '0')) * 10;
    num += ((int) (buffer[1] - '0'));
    return num;
}


char *toString(int num)
{
    char *buffer = (char *) malloc(LENGTH*sizeof(char));
    memset(buffer, '0', LENGTH*sizeof(char));

    if (num < 10) buffer[1] = '0' + num;
    else
    {
        buffer[0] = '0' + num / 10;
        buffer[1] = '0' + num % 10;
    }

    return buffer;
}