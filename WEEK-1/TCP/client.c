#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAX 100
#define PORT 8080
void func(int sockfd){
    char buff[MAX];
    int n;
    while(1){
        bzero(buff,sizeof(buff));
        printf("Enter the string:");
        n=0;
        while((buff[n++]=getchar())!='\n');
        send(sockfd,buff,strlen(buff),0);
        bzero(buff,sizeof(buff));
        recv(sockfd,buff,sizeof(buff),0);
        printf("\nEchoed Message from Server:%s",buff);
        if(!strncmp("exit",buff,4)){
            printf("exit");
            break;
        }

    }
}
int main(){
    int sockfd;
    struct sockaddr_in serveraddr;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd!=-1){
        printf("Socket creation for client is sucessful!!\n");
    }
    else{
        printf("socket creation in client failed!!\n");
        exit(0);
    }
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port=htons(PORT);

    if(!connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))){
        printf("client is connected to the server\n");
    }
    else{
        printf("unable to connect to server\n");
        exit(0);
    }
    func(sockfd);
    close(sockfd);

}