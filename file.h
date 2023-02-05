#include <stdio.h>
#include <stdlib.h>

struct _file {
    char* filename;
    char* buffer;
    int size;
};

int filecat(char* filename)
{
    FILE* fd;
    fd = fopen(filename, "rb");
    if(fd == NULL) return -1;

    int ch;
    while((ch = fgetc(fd)) != EOF) printf("%c", ch);

    printf("\n");
    fclose(fd);
    return 0;
}

int filecopy(char* filename, char* filedst)
{
    FILE* fd;
    FILE* fd2;
    fd = fopen(filename, "rb");
    if(fd == NULL) return -1;

    fd2 = fopen(filedst, "w");
    if(fd2 == NULL) return -1;

    int ch;
    while((ch = fgetc(fd)) != EOF) fputc(ch, fd2);
    fclose(fd);
    fclose(fd2);

    return 0;
}

int filemove(char* filesrc, char* filedst)
{
    if(filecopy(filesrc, filedst) == 0) remove(filesrc);
    else return -1;
    
    return 0;
}

char* fileread(char* filename, int* retsize)
{
    int fsize = 1;
    int ch;
    char* buffer;
    FILE* fd;

    fd = fopen(filename, "r");
    if(fd == 0)
    {
        buffer = malloc(1);
        buffer[0] = 0;
        return buffer;
    }

    buffer = malloc(fsize);

    while((ch = fgetc(fd)) != EOF) 
    {
        buffer[fsize - 1] = ch;
        fsize++;
        buffer = realloc(buffer, fsize);
    }

    fclose(fd);

    *retsize = fsize - 1;
    return buffer;
}

int filewrite(char* filename, char* buffer, int buffer_size)
{
    FILE* fd;
    fd = fopen(filename, "w");
    if(fd == NULL) return -1;
    for (int i = 0; i < buffer_size; i++) fputc(buffer[i], fd);
    fclose(fd);
    return 0;
}

int filerevert(char* filename)
{
    return 0;
}

int filecrypt(char* filename, char* key)
{
    return 0;
}
