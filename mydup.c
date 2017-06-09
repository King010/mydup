
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd=open("./file",O_CREAT | O_RDWR,0666);
	if(fd<0){
		perror("open");
		return 0;
	}

	close(1);
	int new_fd=dup2(fd,1);

	char buf[1024];
	while(1){
		memset(buf,'\0',sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		if(strncmp("quit",buf,4)==0)
			break;
		printf("%s",buf);
		fflush(stdout);
	}
	close(new_fd);
}
