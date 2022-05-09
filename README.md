# ASP_Project
Implementation of distributed processing of grep with client server programming

There are two programs server.c (server) and dgrep.c (client) in C to implement a simple
command to search whole words in two files using distributed processing.
1. The server and the client are required to run on two different machines.
2. The communication between the client and the server will be through sockets
3. The server must start running before the client, and wait for a connection from the
client.
4. The server must run in an infinite loop.

The client’s name is dgrep and must accept the following (three) command line arguments
1. argv[1]=pattern (pattern to be searched in whole words) 
2. argv[2]= file1(Relative or absolute path of the first file)
3. argv[3]= file2 (Relative or absolute path of the second file)
