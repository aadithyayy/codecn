#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define TOTAL_FRAMES 5

int main()
{
    int sockfd;
    struct sockaddr_in serv, snd;
    socklen_t len = sizeof(snd);
    char buffer[1024], ack[10];
    int received[TOTAL_FRAMES] = {0};
    int frame_no = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    printf("Selective Repeat ARQ Simulation (Receiver)\n");

    while (frame_no < TOTAL_FRAMES)
    {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&snd, &len);
        printf("Received: %s\n", buffer);

        // Extract frame number
        int no = buffer[6] - '1'; // "Frame X" → extract X-1
        if (no == 2)
        {
            printf("Dropping Frame %d intentionally\n", no + 1);
            continue;
        }

        received[no] = 1;
        sprintf(ack, "%d", no);
        sendto(sockfd, ack, strlen(ack) + 1, 0, (struct sockaddr *)&snd, len);
        printf("Sent ACK for Frame %d\n", no + 1);
        frame_no++;
    }

    printf("\nAll frames received!\n");
    close(sockfd);
}
