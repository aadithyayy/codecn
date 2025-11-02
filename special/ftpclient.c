#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];
    FILE *fp;                     // Added for writing received data
    char filename[] = "data.txt"; // Added: fixed filename to request automatically

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Connected to server.\n");

    // Changed: send filename instead of “Hello server!”
    send(sockfd, filename, strlen(filename), 0);
    printf("Requested file: %s\n", filename);

    // Added: open file to save data from server
    fp = fopen("received.txt", "w");
    if (fp == NULL)
    {
        perror("Error creating file");
        close(sockfd);
        exit(1);
    }

    // Changed: receive file data and write to file
    while (1)
    {
        int n = read(sockfd, buffer, sizeof(buffer));
        if (n <= 0)
            break;
        if (strcmp(buffer, "FILE_NOT_FOUND") == 0)
        {
            printf("File not found on server.\n");
            remove("received.txt");
            break;
        }
        fprintf(fp, "%s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    printf("File received and saved as 'received.txt'.\n");

    fclose(fp); // Added: close file
    close(sockfd);
    return 0;
}
