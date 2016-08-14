#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> 

char message[] = "SUCCESS";
char buffer[5];
int len = sizeof(char)*5;
int PORT = 12345;
int bufSize = 256;
int main()
{
	int sb,marks,server,check,fromlen,messageSize;
	struct sockaddr_in  my_addr,to;
	char* ch;
	sb = 0;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	
	server = socket(AF_INET,SOCK_DGRAM,0);
	if(server<0)
		printf("*********socket_formation_failed********\n");
	
	if (bind(server, (struct sockaddr *)&my_addr, sizeof(my_addr))<0) 
    		printf("bind failed\n");
	
	fromlen = sizeof(struct sockaddr_in);
	messageSize = strlen(message);

	printf("\n ROLL No.	NAME		IP Address	Port no.	Marks	Attendance\n");

	while(1)
{
	sb = recvfrom(server,buffer,bufSize,0,(struct sockaddr *)&to,&fromlen);	
	if(sb<0)
		{printf("------------not recieved---------\n");}
	else{
	//printf("********** %s *********\n",buffer);
	ch = strtok(buffer,"|");
	printf("%s\t",ch);
	ch = strtok(NULL,"");
	printf("%s\t",ch);
	
	printf("%s\t",inet_ntoa(to.sin_addr));
	printf("%d\t\t",to.sin_port);
	marks = rand()%30;
	printf("%d\t",marks);
	printf("p\n");
	}
	check = sendto(server,message, messageSize , 0, (struct sockaddr *)&to,fromlen);
	if(check<0)
		printf("___________sending_failed______________\n");
}

}
