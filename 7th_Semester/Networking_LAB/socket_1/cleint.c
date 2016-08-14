#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> 

char message[5] = {'H','E','L','L','O'};
char buffer[] = "2012-EE-99|a_rasheed";
char mess[7];
int len = sizeof(char)*5;
int PORT = 12345;
int bufSize = 256;
int main(int argc, char** argv)
{
	int sb,flag,sock,check,i=0,length,messageSize;
	sb = 0;
	struct sockaddr_in  my_addr,to;

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");

	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1)
		printf("***** SOCKET NOT CREATED ****\n");
	
	length = sizeof(struct sockaddr_in);
	messageSize = strlen(buffer);
	sb = sendto(sock,argv[1], messageSize ,0, (struct sockaddr *)&my_addr,length);
	if(sb<0)
		printf("______sending failed________\n");
	else
		printf("\tsuccessfully sent\n");
	
	while(i<1)
{
	check = recvfrom(sock,mess,bufSize,0,(struct sockaddr *)&my_addr,&length);
	if(check<0)
		printf("\tnot recieved\n");
	else
	//printf("\trecieved\n");
	printf("\t***%s*** \n",mess);
	i++;

}
}
