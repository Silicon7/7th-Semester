#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int PORT = 12345;	
char buffer[15];
int bufLen;
char rBuffer[10];
int rBufLen = 256;

int main()
{
	int sock,recvLen,sockLen,clisock;
	struct sockaddr_in server,client;
	
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;

	sockLen = sizeof(struct sockaddr_in);
	recvLen = sizeof(struct sockaddr_in);

	sock = socket(AF_INET,SOCK_STREAM,0);	

	bufLen = strlen(buffer);
	
	if(bind(sock,(struct sockaddr *)&server,sockLen)<0)
		printf("###### BIND FAILED ######\n");
	
	if(listen(sock,100)<0)
		printf("###### LISTEN FAILED ######\n");
	
	clisock = accept(sock,(struct sockaddr*)&client, &recvLen);
	if(clisock<0)
		printf("****** ACCEPT FAILED ******\n");

		

	printf("SERVER : ");	gets(buffer);
	if(send(clisock,buffer,256,0)<0)
		printf("===== SENDING FAILED =====\n");
	
	if(recv(clisock,rBuffer,rBufLen,0)<0)
		printf("------ RECIEVING FAILED -----\n");
	printf("\nCLIENT : %s \n",rBuffer);


	printf("SERVER : ");	gets(buffer);
	if(send(clisock,buffer,256,0)<0)
		printf("===== SENDING FAILED =====\n");
	
	if(recv(clisock,rBuffer,rBufLen,0)<0)
		printf("------ RECIEVING FAILED -----\n");
	printf("CLIENT : %s \n",rBuffer);


close(sock);
close(clisock);

return 0;

}
