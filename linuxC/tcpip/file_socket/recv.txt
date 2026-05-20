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
	int sd;
	
	char buf[BUF_SIZE];
	int in, read_cnt;
	struct sockaddr_in serv_adr;

	if(argc < 4) {
		printf("Usage: %s <IP> <port> <send filename>\n", argv[0]);
		exit(1);
	}
	
	sd=socket(PF_INET, SOCK_STREAM, 0);   

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	

	if ((in = open(argv[3], O_RDONLY)) < 0) {
        perror("File open error");
        exit(1);
    }
    
	
	
	while((read_cnt = read(in, buf, sizeof(buf))) >0) {
        ; 
        if(read_cnt > 0) {
            write(sd, buf, read_cnt); 
            printf("Sent : %d bytes\n", read_cnt);
        }
        else if(read_cnt == 0) { 
            printf("Send Done ...\n");
            break;
        }
        else { // read() 오류
            perror("read error");
            break;
        }
    } 
	
	
	// write(sd, "Done ....", 10);
	close(in);
	close(sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}