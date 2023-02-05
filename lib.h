#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "./string.h"
#include "./file.h"
#include <dirent.h>
#include <string.h>

void displayReceive(int clientSocket, char* message, int display)
{
    char server_reply[1024];
    int a;
    while ((a = recv(clientSocket, server_reply, 1024, 0)) > 0)
    {
        server_reply[a] = '\0';
        if(display)
        {
            printf("%s", server_reply);
            printf("\n");
        }
        strcopy(message, server_reply);
        if(strstr(server_reply, "\n"))
        {
            printf("\n");
            break;
        } 
        message[strsize(message)] = 0;
    }
}

int askFile(struct _file* file)
{
    file->filename = malloc(1);
    int j = 0;
    printf("Quel fichier voulez-vous copier ? ");
    while((file->filename[j] = getchar()) != '\n')
    {
            j++;
            file->filename = realloc(file->filename, j + 1);
    }
    file->filename[j] = 0;
    return 0;
}

int initConnect(int* clientSocket, int port)
{
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    *clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    for(int i = 0; i < 8; i++) serverAddr.sin_zero[i] = 0;
    addr_size = sizeof serverAddr;

    if(connect(*clientSocket, (struct sockaddr*)&serverAddr, addr_size) != 0)
    {
        return -1;
    }
    return 1;
}

int sendFilesList(char* path, int clientSocket) 
{
    DIR* _d = opendir(path);
    struct dirent* d;
    int i = 0;

    while((d = readdir(_d)) != NULL)
    {   
        if(d->d_type == DT_REG) 
        {   
            printf("%s\n", d->d_name);
            send(clientSocket, d->d_name, strsize(d->d_name), 0);
            send(clientSocket, "\n", 1, 0);
        }
    }
    closedir(_d);
    return 0;
}

int checkFiles(char* path, char* filename)
{
    DIR* _d = opendir(path);
    struct dirent* d;
    int i = 0;

    while((d = readdir(_d)) != NULL)
    {   
        if(d->d_type == DT_REG) 
        {   
            if(strcompare(d->d_name, filename)) return 1;
        }
    }
    closedir(_d);
    return 0;
}


