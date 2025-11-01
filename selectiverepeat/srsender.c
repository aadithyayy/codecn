#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define WINDOW_SIZE 3
#define TOTAL_FRAMES 5

int main()
{
    int sockfd;
    struct sockaddr_in rec;
    socklen_t len = sizeof(rec);
    char *frames[] = {"Frame 1", "Frame 2", "Frame 3", "Frame 4", "Frame 5"};
    char ack[10];
    int sent[TOTAL_FRAMES] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    rec.sin_family = AF_INET;
    rec.sin_port = htons(PORT);
    rec.sin_addr.s_addr = INADDR_ANY;

    printf("Selective Repeat ARQ Simulation (Sender)\n");

    int base = 0;
    while (base < TOTAL_FRAMES)
    {
        // Send up to window size frames
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
        {
            if (!sent[i])
            {
                sendto(sockfd, frames[i], strlen(frames[i]) + 1, 0,
                       (struct sockaddr *)&rec, len);
                printf("Sent: %s\n", frames[i]);
            }
        }

        // Wait for ACK
        recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr *)&rec, &len);
        int ack_no = atoi(ack);

        printf("ACK received for Frame %d\n", ack_no + 1);
        sent[ack_no] = 1;

        // Slide window if base frame is acknowledged
        while (base < TOTAL_FRAMES && sent[base])
            base++;
    }

    printf("\nAll frames sent and acknowledged!\n");
    close(sockfd);
}
