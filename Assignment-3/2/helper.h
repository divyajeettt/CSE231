#define N 50
#define CHUNK 5
#define LENGTH 10
#define BATCH_SIZE (LENGTH+2)*CHUNK*sizeof(char)

#define FIFO_S2C "./crimge-s2c.fifo"
#define FIFO_C2S "./crimge-c2s.fifo"
#define SOCKET "./crimge.socket"
#define SHM "./crimge-shm"


char **generateStrings()
{
    char **strings = (char **) malloc(N*sizeof(char *));
    for (int i = 0; i < N; i++)
    {
        strings[i] = (char *) malloc(LENGTH*sizeof(char));
        for (int j = 0; j < LENGTH; j++) strings[i][j] = 'a' + (rand() % 26);
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
    char *buffer = (char *) malloc(2*sizeof(char));
    memset(buffer, '0', 2*sizeof(char));

    if (num < 10) buffer[1] = '0' + num;
    else
    {
        buffer[0] = '0' + num / 10;
        buffer[1] = '0' + num % 10;
    }

    return buffer;
}


char *addIndex(char *string, int index)
{
    char *indexed = (char *) malloc((LENGTH+2)*sizeof(char));
    strcpy(indexed, toString(index));
    strcat(indexed, string);
    return indexed;
}


char **splitIndex(char *string)
{
    char **strings = (char **) malloc(2*sizeof(char *));
    strings[0] = (char *) malloc(2*sizeof(char));
    strings[1] = (char *) malloc(LENGTH*sizeof(char));

    for (int i=0; i < 2; i++) strings[0][i] = string[i];
    for (int i=0; i < LENGTH; i++) strings[1][i] = string[i+2];

    return strings;
}


char *makeBatch(char **strings, int index)
{
    char *batch = (char *) malloc(BATCH_SIZE);
    memset(batch, '\0', BATCH_SIZE);
    for (int i=0; i < CHUNK; i++)
    {
        char *indexedString = addIndex(strings[index+i], index+i);
        strcat(batch, indexedString);
    }
    return batch;
}


char **splitBatch(char *batch)
{
    char **strings = (char **) malloc(CHUNK*sizeof(char *));
    int index = 0;
    for (int i=0; i < CHUNK; i++)
    {
        strings[i] = (char *) malloc((LENGTH+2)*sizeof(char));
        for (int j=0; j < LENGTH+2; j++) strings[i][j] = batch[index++];
    }
    return strings;
}