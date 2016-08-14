#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
#define PORT 13 // port of daytime server

char rBuffer[BUFLEN];

int main(int argc, char *argv[])
{
  // define your variables here
	int sock,sockLen;
	struct sockaddr_in client,server;
	struct hostent *rHost;

  // check that there are enough parameters
	if(argc !=2)
	{
		printf("*******	INVALID Number of ARGUMENTS ******\n");
		exit(0);
	}
  // Write your code (actual functionality) here
	rHost = gethostbyname(argv[1]);
	if (rHost == NULL)
	{
		printf("invalid HOST_NAME\n");
		exit(0);
    	}
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	
	memcpy(&server.sin_addr , rHost->h_addr, rHost->h_length);
	
	sockLen = sizeof(struct sockaddr_in);	
	
	sock = socket(AF_INET,SOCK_STREAM,0);
	
	
	if(connect(sock,(struct sockaddr*)&server,sockLen)<0)
		printf("\n*****connect_function_failed*****\n");
	
	if(recv(sock,rBuffer,BUFLEN,0)<0)
		printf("------FAILED_RECIEVING-----\n");

// Print to standard output	
	printf("\t DATE\t TIME  %s \n",rBuffer);
	
	

 close(sock);
  
  return 0;
}
