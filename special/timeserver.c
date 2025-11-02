#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int main()
{
    int sockfd, newsock;
    struct sockaddr_in server, client;
    char buffer[1024];
    socklen_t len = sizeof(client);
    time_t t;

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Setup server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }

    // Listen for client
    listen(sockfd, 5);
    printf("Server waiting for client...\n");

    // Accept client connection
    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    if (newsock < 0)
    {
        perror("Accept failed");
        exit(1);
    }

    printf("Client connected!\n");

    // Get current time
    t = time(NULL);
    snprintf(buffer, sizeof(buffer), "Current Time: %s", ctime(&t));

    // Send time to client
    send(newsock, buffer, strlen(buffer), 0);
    printf("Time sent to client.\n");

    // Close sockets
    close(newsock);
    close(sockfd);

    return 0;
}
