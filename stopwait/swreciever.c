#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, frame_no = 0;
    struct sockaddr_in serv, snd;
    char buffer[1024], ack[10];
    socklen_t len = sizeof(snd);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    printf("Receiver ready...\n");

    while (1)
    {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&snd, &len);
        frame_no++;
        printf("Received: %s\n", buffer);

        // Intentionally drop ACK for specific frames (2 and 4)
        if (frame_no == 2 || frame_no == 4)
        {
            printf("!! Intentionally dropping ACK for %s\n\n", buffer);
            continue;
        }

        strcpy(ack, "ACK");
        sendto(sockfd, ack, strlen(ack) + 1, 0, (struct sockaddr *)&snd, len);
        printf("Sent ACK for %s\n\n", buffer);
    }

    close(sockfd);
    return 0;
}
