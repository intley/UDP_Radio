#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define BUFFSIZE 8 

/*
 * Arg1: IP address
 * Arg2: Port #
 * Arg3: file
 * Arg4: buffer/packet size
 * Arg5: transmission delay
 *
 */


int main(int argc, char* argv[]){

	int res;
	
	// Set up socket
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if (fd < 0){
		printf("Error setting up socket\n");
		return 1;
	}

	// Set up address info
	struct sockaddr_in vlcaddr;
	memset(&vlcaddr,0,sizeof(vlcaddr));
	vlcaddr.sin_family=AF_INET;
	vlcaddr.sin_addr.s_addr = inet_addr(argv[1]);
	vlcaddr.sin_port=htons(atoi(argv[2]));

	// Read from file
	// Send data over socket
	unsigned char buff[atoi(argv[4])];
	int f = open(argv[3],O_RDONLY);
	
	while (read(f,buff,sizeof(buff))  > 0){
		
		res = sendto(fd,buff,sizeof(buff),0,(struct sockaddr *) &vlcaddr,sizeof(vlcaddr));
		printf("%d\n",res);
		
		// simulate transmission delay
		usleep(atoi(argv[5]));
	}

	return 0;
}
