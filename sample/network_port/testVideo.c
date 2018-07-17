#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <stdio.h>  

#define READ_SIZE 20480000
#define MAX_SEND_PACK 8192

//port and ip
#define PORT 23003  
#define SERVER_IP "192.168.5.10" 
#define FILE_NAME "test.h264"

char I_Head[5] = {0x00, 0x00, 0x00, 0x01, 0x67};
char P_Head[5] = {0x00, 0x00, 0x00, 0x01, 0x61};

char F_Head[6] = {0x00, 0x00, 0x00, 0x01, 0x09, 0x10};
char buffer[READ_SIZE];

//00 00 00 01 67 - I
//00 00 00 01 61 - P
//I 29P // 33ms 

int main(int argc, char** argv)  
{  
    FILE *pF;
    int i,j;

    bzero(buffer,sizeof(buffer));
  
    pF = fopen(FILE_NAME, "rb+");
    if (pF == NULL) {
       printf("No File!\r\n");
    }

    int s,len;  
    struct sockaddr_in addr;  
    int addr_len =sizeof(struct sockaddr_in);  

    if((s = socket(AF_INET,SOCK_DGRAM,0))<0){  
        perror("socket");  
        exit(1);  
    }  

    bzero(&addr,sizeof(addr));  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(PORT);  
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  
    len = fread(buffer,1,READ_SIZE,pF);  
        
    if (len < 0) {
       printf("read length error!\r\n");
    } else {
       printf("file len = %d B\r\n", len);
    }

    i = 0;
    j = 0;

    while(1){
        while (memcmp(buffer+i,I_Head,5)!=0 && memcmp(buffer+i,P_Head,5)!=0) {
           i++;
           if (i > len) {
              printf("Send finish\r\n");
	      fclose(pF);

              printf("Resend\r\n");
              pF = fopen(FILE_NAME, "rb+");
              
              i = 0;
              j = 0;
              
              continue;
           }
        }
   
        j = i + 5;
        while (memcmp(buffer+j,I_Head,5)!=0 && memcmp(buffer+j,P_Head,5)!=0) {
           j++;
           if (j > len) {
              printf("send finish\r\n");
	      fclose(pF);

              printf("Resend\r\n");
              pF = fopen(FILE_NAME, "rb+");
              
              i = 0;
              j = 0;
              
              continue;
           }
        }

	if (memcmp(buffer+i,P_Head,5) == 0) {
          printf("send p frame, len = %d\r\n", j - i);

          while (j - i > MAX_SEND_PACK) {
             sendto(s, buffer+i, MAX_SEND_PACK,0,(struct sockaddr *)&addr,addr_len); 
             usleep(700);
             i += MAX_SEND_PACK;
          }

          sendto(s, buffer+i, j - i,0,(struct sockaddr *)&addr,addr_len); 
          usleep(33000);
        } else if(memcmp(buffer+i, I_Head,5) == 0) {
          printf("send i frame, len = %d\r\n", j - i);

          while (j - i > MAX_SEND_PACK) {
             sendto(s,buffer+i,MAX_SEND_PACK,0,(struct sockaddr *)&addr,addr_len); 
             i += MAX_SEND_PACK;
          }

          sendto(s,buffer+i,j - i,0,(struct sockaddr *)&addr,addr_len); 
          usleep(33000);
        }
       
        i = j;
    }  
}
