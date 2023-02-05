# SIMPLE FTP IMPLEMENTATION

This is a simple FTP implementation in C. It is a client-server application.

I never practiced much the C language, so I wanted to practice by rewriting simple libraries such as string and file and use them by writing a simple implementation of the FTP protocol.

### How it works
The client first sends a request to the first server and the latter sends back the list of files contained in the data directory. The client can then copy one of the files into its current directory by sending the name of the chosen file to server 2.

### How to run
First, compile the servers and the client by running the following commands:
```bash
gcc -o server_ls server1.c
gcc -o server_read server2.c
gcc -o client client.c
```
Then, run the servers and the client in different terminals:
```bash
./server_ls
./server_read
./client
```
The client will ask you to enter the name of the file you want to copy. Enter the name of one of the files listed by the first server and the client will copy it into its current directory. If the file does not exist, the client will print an error message and ask you again to enter the name of the file you want to copy.