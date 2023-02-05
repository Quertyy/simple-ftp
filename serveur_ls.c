#include <stdio.h>
#include "./lib.h"

int main()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    struct _file file;
    char* message;

    char** files;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
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

        sendFilesList("data", newSocket);
        send(newSocket, "1", 1, 0);
    }

    return 0;
}