#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];
    FILE *fp; // Added for file handling

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Waiting for connection...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    printf("Client connected.\n");

    memset(buffer, 0, sizeof(buffer));
    read(newsock, buffer, sizeof(buffer));
    printf("Client requested file: %s\n", buffer); // Added: show requested filename

    // Added: open requested file
    fp = fopen(buffer, "rb");
    if (fp == NULL)
    {
        // Added: send error if file not found
        strcpy(buffer, "FILE_NOT_FOUND");
        send(newsock, buffer, strlen(buffer), 0);
        printf("File not found.\n");
    }
    else
    {
        // Added: send file contents in chunks
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            send(newsock, buffer, strlen(buffer), 0);
            memset(buffer, 0, sizeof(buffer));
        }
        printf("File sent successfully.\n");
        fclose(fp); // Added: close file after sending
    }

    close(newsock);
    close(sockfd);
    return 0;
}
