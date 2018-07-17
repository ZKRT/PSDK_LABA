#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <stdio.h>  

//port & ip
#define PORT 23002  
#define SERVER_IP "192.168.5.10"  

int main(int argc, char** argv)  
{  
    int s,len;  
    struct sockaddr_in addr;  
    int addr_len =sizeof(struct sockaddr_in);  
    char buffer[512];  
    int testId = 0;

    if((s = socket(AF_INET,SOCK_DGRAM,0))<0){  
        perror("socket");  
        exit(1);  
    }  

    bzero(&addr,sizeof(addr));  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(PORT);  
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  
    while(1){
        if (testId >= 100) {
           testId = 0; 	
        }

        sprintf(buffer, "Network Test Data %d \r\n", testId++); 
        len = sendto(s,buffer,strlen(buffer) + 1,0,(struct sockaddr *)&addr,addr_len); 
	printf("send len = %d \r\n",len);
	usleep(1000000);
    }  
}
