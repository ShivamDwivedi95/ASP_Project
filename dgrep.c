// Socket code taken from 
// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/?ref=lbp

/*
	Project submitted by :
	Shivam Dwivedi				110071950			dwivedi2@uwindsor.ca
	Varinder Pal Babool			110057836			babool@uwindsor.ca
*/


#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd, char *argv[])
{
	char buff[MAX];
	int n;
	bzero(buff, sizeof(buff));
	write(sockfd, argv[3], sizeof(buff));
	write(sockfd, argv[1], sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));
	
	int fd[2];
	FILE *fp2;
	int k=pipe(fd);//create a pipe
	char data[1024] = {0};
	if(k == -1)
		exit(1); 
	if(fork() == 0) {

		int file = open("client_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	    if(file == -1){
		    
	    }
        int file2 = dup2(file, 1);
        close(file);
        int err = execlp("egrep","egrep","-i","--color=always",argv[1], argv[2], NULL);
    	if(err == -1){
		    printf("could not find program to execute");
		    
	    } 
	}
	else {
		wait(NULL);
        fp2 = fopen("client_output.txt", "r");
        while(1) {
            if(fgets(data, 1024, fp2) != NULL)
            {
                printf("%s: %s",argv[2],data);
            }
            else{
                break;
            }
        }
        printf("%s: ", argv[3]);
		
        for(int i=0 ; i<sizeof(buff) ; i++) {
            if(buff[i] == '\n') {
				printf("\n%s: ", argv[3]);
				// printf("%s", tempStr);
				if(buff[i]=='\0') 
					break;
			} 
			else if(buff[i]=='\0') {
				break;
			} else
				printf("%c", buff[i]);
        } 

	}

}

int main(int argc, char *argv[])
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	// printf("%d\n\n", argc);
	if(argc !=4) {
		printf("Error: need dgrep pattern file1 file2");
		exit(0);


	}

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
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd, argv);

	// close the socket
	close(sockfd);
}
