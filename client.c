#include <stdio.h>
#include "./lib.h"

int main()
{
    filewrite("rarad.txt", "test", 4);
    struct _file file;
    int clientSocket;
    int a;
    char server_reply[1024];

    if(initConnect(&clientSocket, 12345))
    {
        send(clientSocket, "ok", 2, 0);
        printf("Liste des fichiers :\n");
        displayReceive(clientSocket, server_reply, 1);
    }
    close(clientSocket);
    int copy = 0;
    
    while (!copy)
    {
        if(initConnect(&clientSocket, 54321))
        {
            askFile(&file);
            send(clientSocket, file.filename, strsize(file.filename), 0);
            send(clientSocket, "\n", 1, 0);
            displayReceive(clientSocket, server_reply, 0);
            if(strcompare(server_reply, "ERROR\n")) {
                printf("Le fichier n'existe pas\n");
                for(int i = 0; i < 1024; i++) server_reply[i] = 0;
            } else {
                file.buffer = server_reply;
                file.size = strsize(file.buffer);
                filewrite(file.filename, file.buffer, file.size);
                printf("Le fichier a ete copie\n");
                copy = 1;
            }
        }
    }
    close(clientSocket);
    return 0;
}