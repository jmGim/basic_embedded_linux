

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock;

    struct sockaddr_in serv_addr;
	int str_len;
    //char message[30]={'a','b', '\0'};
	//char message[30]="ab";
    char message[50] = {'\0'};
	if (argc != 3 ){
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket () error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

	//s_addr 에 4byte 숫자만 저장 되어야 함. 
	// -> 숫자를 반대로 저장 ex) 251.16.10.10
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);  // server : htonl()
    serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)   
		error_handling("connect() error");

	do {
		fputs("문자열을 입력하세요 ! (quit - 종료)", stdout);
		fgets(message, sizeof(message), stdin); // blocking 함수 - enter 까지
		message[strlen(message)-1] = '\0';
		if(!strcmp(message, "quit")) 
			break;
		write(sock, message, strlen(message));
	//	strcat(message, "(sent from Client)");

		// read() : blocking function : 들어올 때까지 대기(잠자는 상태)
		// 대기 상태(sleep) 
		str_len=read(sock, message, sizeof(message)-1);
		
		
		if(str_len < 0)
		   error_handling("accept() error");

			//write(sock, message, str_len);
		message[str_len] = '\0';
		
		printf("Message from server : %s, size : %d\n", message, str_len);	

	} while(1);
	close(sock);
    return 0;
}

void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n', stderr);

    exit(1);
}
