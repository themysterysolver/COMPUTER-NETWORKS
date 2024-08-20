#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define PORT 8080
#define MAX 100
void func(int sockfd){
    char buff[MAX];
    int n=0;
    while(1){
        bzero(buff,MAX);
        printf("TO SERVER:");
        n=0;
        while((buff[n++]=getchar())!='\n');
        send(sockfd,buff,MAX,0);
        bzero(buff,MAX);
        int byte=recv(sockfd,buff,MAX,0);
        if(byte<=0){
            printf("error occured while recieving the message!\n");
            break;
        }
        printf("FROM SERVER:%s\n",buff);
        if(!strncmp(buff,"exit",4)){
            printf("server exited the chat!!\n");
            break;
        }
    }
}
int main(){
    int sockfd;
    struct sockaddr_in serveraddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("Unable to CREATE a socket!\n");
        exit(0);
    }
    else{
        printf("socket creation is sucessful!!\n");
    }
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port=htons(PORT);
    if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))){
        printf("unable to connect to servfrom from client!!\n");
        exit(0);
    }
    else{
        printf("connected to client sucessfully!!\n");
    }
    func(sockfd);
    close(sockfd);
}