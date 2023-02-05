#include <stdio.h>
#include "./lib.h"
#include <string.h>

int main()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    struct _file file;
    char client_reply[1024];


    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54321);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    for(int i = 0 ; i < sizeof(serverAddr.sin_zero); i++) serverAddr.sin_zero[i] = 0;
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));


    while(1)
    {
        if(listen(serverSocket, 5) == 0)
        {
            printf("Le serveur est en ecoute...\n");
        }
        else
        {
            printf("Echec de l'ouverture du port...\n");
            return 1;
        }
        addr_size = sizeof(serverStorage);
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        
        
        file.filename = malloc(1);
        int i = 0;
        int ch;
        while((ch = recv(newSocket, file.filename + i, 1, 0)) != 0)
        {
            if (file.filename[i] == '\n') break;
            i++;
            file.filename = realloc(file.filename, i + 1);
            
        }
        file.filename[i] = 0;
        char path[] = "data/";
        char* result = strconcat(path, file.filename);
        char* response;
        if(checkFiles("data", file.filename) == 0){
            response = "ERROR";
        } else {
            file.buffer = fileread(result, &file.size);
            response = file.buffer;
        }
        send(newSocket, response, strsize(response), 0);
        send(newSocket, "\n", 1, 0);
    }
    
    return 0;
}