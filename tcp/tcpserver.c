#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    int sockfd, newsock;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char buffer[1024];
    
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);
    
    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    listen(sockfd,5);
    printf("Waiting for Connection...\n");
    
    newsock=accept(sockfd,(struct sockaddr*)&client,&len);
    memset(buffer, 0, sizeof(buffer));
    read(newsock,buffer,sizeof(buffer));
    printf("Message:%s\n",buffer);
    
    send(newsock,"hello from server!",18,0);
    close(newsock);
    close(sockfd);

    return 0;
    
    
}