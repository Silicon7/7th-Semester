#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>
#include <string.h>

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want

int main(int argc, char **argv)
{ 
   // Define your variables here
	char *host_name;
	char *alias;
	struct hostent *rHost;
	struct in_addr addr;
	int i=0,j=0;
	// Check that there are enough parameters
	if(argc !=2)
	{
		printf("*******	INVALID Number of ARGUMENTS ******\n");
		exit(0);
	}

	host_name = argv[1];

	// Address resolution stage by using gethostbyname()
	rHost = gethostbyname(host_name);

	// Check if a bogus hostname is	 provided
	if (rHost == NULL)
	{
		printf("invalid HOST_NAME\n");
		exit(0);
    	}

	// Print to standard output
	printf("Canonical name is : %s\n",rHost->h_name);
	
	while(rHost->h_aliases[j] != 0)
	{
		alias = rHost->h_aliases[j++];
		printf("ALIAS name #%d: %s\n",j,alias);
	}
	while (rHost->h_addr_list[i] != 0) 
	{
		addr.s_addr = *rHost->h_addr_list[i++];
                printf("\tIP Address #%d: %s\n", i, inet_ntoa(addr));
        }

   	return 0;
}

