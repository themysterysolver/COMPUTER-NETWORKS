#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 8080
#define MAX 100
void func(int clifd){
    char buff[MAX];
    int n;
    while(1){
        bzero(buff,MAX);
        int bytes=recv(clifd,struct serveradd(cliaddr),0)
    }
}

int main(){
    int sockfd,clifd,len;
    struct sockaddr_in serveraddr,cliaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("Socket connection failed!!!\n");
        exit(0);
    } 
    else{
        printf("socket conenction sucessful!!\n");
    }
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveradd.sin_port=htonl(PORT);
    if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))){
        printf("Socket is binded sucessfully!!\n");
    }
    else{
        printf("Unable to bind socket\n");
        exit(0);
    }
    if(listen(sockfd,3)==-1){
        printf("unable to listen!!\n");
        exit(0);
    }
    else{
        printf("Server is listening!!\n");
    }
    len=sizeof(cliaddr);
    clifd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
    if(clifd!=-1){
        printf("Server accepted the incmoing request form client!\n");
    }
    else{
        printf("unable to accept!accept() failed\n");
    }
    funct(clifd);
    clsoe(sockfd);
}