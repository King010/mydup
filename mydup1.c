
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		perror("socket");
		return 1;
	}

	struct sockaddr_in peer;
	peer.sin_family=AF_INET;
	peer.sin_port=htons(atoi(argv[2]));
	peer.sin_addr.s_addr=inet_addr(argv[1]);

	if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0){
		perror("connect");
		return 2;
	}
	close(1);
	int new_fd=dup2(sock,1);
	char buf[1024];
	close(sock);
	while(1){
		ssize_t s=read(0,buf,sizeof(buf)-1);
		if(s>0)
			buf[s-1]='\0';
		if(strncmp("quit",buf,4)==0)
			break;
		printf("%s",buf);
		fflush(stdout);
	}
	close(new_fd);
}



