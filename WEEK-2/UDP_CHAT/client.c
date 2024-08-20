#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 100
#define PORT 8080
void func(int sockfd,struct sockaddr_in serveraddr){
    char buff[MAX];
    socklen_t len=sizeof(serveraddr);
    int n=0;
    while(1){
        printf("FROM CLIENT:");
        n=0;
        while((buff[n++]=getchar())!='\n');
        sendto(sockfd,buff,MAX,0,(const struct sockaddr*)&serveraddr,len);
        if(!strncmp("exit",buff,4)){
            printf("Client has exited the chat!!\n");
            break;
        }
        bzero(buff,sizeof(buff));
        int bytes=recvfrom(sockfd,buff,MAX,0,(struct sockaddr*)&serveraddr,&len);
        if(bytes<=0){
            printf("Error occured while recieving!!\n");
            break;
        }
        printf("FROM SERVER:%s",buff);
        
        if (!strncmp("exit", buff, 4)) {
            printf("Server has exited the chat.\n");
            break;
        }
   
   
   
    }
}
int main(){
    int sockfd;
    struct sockaddr_in serveraddr;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<=-1){
        printf("socket connection failed!!\n");
        exit(0);
    }
    else{
        printf("Socket connection is sucessful!!\n");
    }
    bzero(&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port=htons(PORT);

    func(sockfd,serveraddr);
    close(sockfd);
}