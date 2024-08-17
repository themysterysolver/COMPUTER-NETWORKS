#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 8080
#define MAX 100

void func(int sockfd){
    char buff[MAX];
    struct sockaddr_in cliaddr;
    socklen_t len=sizeof(cliaddr);
    while(1){
        bzero(buff,MAX);
        int bytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,&len);
        if(bytes<=0){
            printf("Error occured while reciving the message!\n");
            break;
        }
        printf("FROM CLIENT:%s",buff);
        sendto(sockfd,buff,strlen(buff),0,(const struct sockaddr*)&cliaddr,len);
        if(!strncmp(buff,"exit",4)){
            printf("server exited the chat!!");
            break;
        }
    }
}

int main(){
    int sockfd;
    struct sockaddr_in serveraddr;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1){
        printf("socket connection failed!!!\n");
        exit(0);
    }
    else{
        printf("socket connected sucessfully!!\n");
    }
    bzero(&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htons(PORT);

    if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))!=-1){
        printf("Server is binded successfully!!\n");
    }
    else{
        printf("Server is not binded!!");
        exit(0);
    }

    func(sockfd);
    close(sockfd);
    return 0;
}