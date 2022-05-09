/*
	Project submitted by :
	Shivam Dwivedi				110071950			dwivedi2@uwindsor.ca
	Varinder Pal Babool			110057836			babool@uwindsor.ca
*/

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd)
{
	char pattern[MAX], serverFilePath[MAX];
	int n;
	// infinite loop for chat

	bzero(pattern, MAX);
	bzero(serverFilePath, MAX);
	read(connfd, serverFilePath, sizeof(serverFilePath));
	printf("From client: %s\t File \n", serverFilePath);
	read(connfd, pattern, sizeof(pattern));
	printf("From client: %s\t Pattern \n", pattern);

	int fd[2];
	int k=pipe(fd);//create a pipe
	if(k == -1)
		exit(1); 
	if(fork() == 0){
		close(fd[0]);

		dup2(fd[1], 1);
		execlp("grep", "grep", "--color=always", "-w", pattern, serverFilePath, NULL);
		// printf("Child");
		
	}
	else {
		char output[MAX];
		close(fd[1]);//since parent does not use fd[1]
		dup2(fd[0], 0);
		// printf("Child has sent the message:\n");
		read(fd[0], &output, MAX);
		// printf("\n%s\nHere it is", output);
		write(connfd, output, sizeof(output));
	}

}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	Refunction:;
	printf("\nWaiting for Client to send something\n");
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);
	goto Refunction;

	// After chatting close the socket
	close(sockfd);
}

