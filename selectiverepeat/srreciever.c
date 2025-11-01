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
    int dropped_once = 0; // track if frame 3 was dropped

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    printf("Selective Repeat ARQ Simulation (Receiver)\n");

    while (1)
    {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&snd, &len);
        int no = buffer[6] - '1'; // Extract frame number from "Frame X"
        printf("Received: %s\n", buffer);

        // Drop Frame 3 only once
        if (no == 2 && !dropped_once)
        {
            printf("Dropping Frame %d intentionally (once)\n", no + 1);
            dropped_once = 1;
            continue;
        }

        if (!received[no])
        {
            received[no] = 1;
            sprintf(ack, "%d", no);
            sendto(sockfd, ack, strlen(ack) + 1, 0, (struct sockaddr *)&snd, len);
            printf("Sent ACK for Frame %d\n", no + 1);
        }

        // Check if all frames received
        int all_received = 1;
        for (int i = 0; i < TOTAL_FRAMES; i++)
        {
            if (!received[i])
            {
                all_received = 0;
                break;
            }
        }
        if (all_received)
            break;
    }

    printf("\nAll frames received successfully!\n");
    close(sockfd);
    return 0;
}
