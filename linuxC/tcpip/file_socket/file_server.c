#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

#define BUF_SIZE 100
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sd, clnt_sd;
	
	char buf[BUF_SIZE];
	int out, read_cnt;
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	
	if(argc!=3) {
		printf("Usage: %s <port> <save file>\n", argv[0]);
		exit(1);
	}
	
	
	serv_sd=socket(PF_INET, SOCK_STREAM, 0);   
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) < 0) {
        perror("bind() error");
        exit(1);
    }
    
    if(listen(serv_sd, 5) < 0) {
        perror("listen() error");
        exit(1);
    }
    
    clnt_adr_sz = sizeof(clnt_adr);    
    clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    if(clnt_sd < 0) {
        perror("accept() error");
        exit(1);
    }
	
	// clnt_adr_sz=sizeof(clnt_adr);    
	// clnt_sd=accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	
	
    out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out < 0) {
        perror("File open error");
        exit(1);
    }
	
   
    while(1)  {
        read_cnt = read(clnt_sd, buf, sizeof(buf)); 
        
        if(read_cnt > 0) {
            write(out, buf, read_cnt); 
            printf("Received : %d bytes\n", read_cnt);
        }
        else if(read_cnt <= 0) { 
            printf("Receive Done ...\n");
            break;
        }
        else { 
            perror("read error");
            break;
        }
    } 
	
	
	close(out);
	close(clnt_sd); close(serv_sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
