#include <stdio.h>      //standard I/O
#include <sys/socket.h> //definition of socket operation!
#include <netinet/in.h> //constants  and structure for internet!
#include <unistd.h>     //conatins close( ) to close a fd
#include <stdlib.h>     //used for exit( )
#include <string.h>     //used for strlen()
#define PORT 8080
int main(){
    int sockfd,connfd,len;
    struct sockaddr_in serveraddr,cli;

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
    serveraddr.sin_
}

