#include <stdio.h>      //standard I/O
#include <sys/socket.h> //definition of socket operation!
#include <netinet/in.h> //constants  and structure for internet!
#include <unistd.h>     //conatins close( ) to close a fd
#include <stdlib.h>     //used for exit( )
#include <string.h>     //used for strlen()
#define PORT 8080
#define MAX 100
void func(int clifd){
    char buff[MAX];
    int n;
    while(1){
        bzero(buff,MAX);
        int bytes=recv(clifd,buff,sizeof(buff),0);
        if(bytes<=0){
            printf("error occured while recieveing!!");
            break;
        }
        printf("From client:%s",buff);
        send(clifd,buff,sizeof(buff),0);
        if(!strncmp("exit",buff,4)){
            printf("Server exit");
            break;
        }
    }
}
int main(){
    int sockfd,clifd,len;
    struct sockaddr_in serveraddr,cliaddr;

    //socket creation!
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("socket creation failed!\n");
        exit(0);
    }
    else{
        printf("Socket created sucessfully!\n");
    }
    bzero(&serveraddr,sizeof(serveraddr));
    
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htonl(PORT);

    if((bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))==0){
        printf("Socket is binded sucessfullt to the address!!");
    }
    else{
        printf("Binding of socket failed!!");
        exit(0);
    }

    if(listen(sockfd,3)!=-1){
        printf("Server is now listening!!");
    }
    else{
        printf("Listening failed!!");
        exit(0);
    }
    len=sizeof(cliaddr);
    clifd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
    if(clifd!=-1){
        printf("aceptig the clinet is sucessful!!");
    }
    else{
        printf("aceept() failed!!");
    }
    func(clifd);
    close(sockfd);
}

