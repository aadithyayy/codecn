#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TIMEOUT 2

int main()
{
    int sockfd, seq = 0;
    struct sockaddr_in rec;
    char *frames[] = {"Frame 1", "Frame 2", "Frame 3", "Frame 4", "Frame 5"};
    char ack[10];
    socklen_t len = sizeof(rec);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    rec.sin_family = AF_INET;
    rec.sin_port = htons(8080);
    rec.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct timeval tv = {TIMEOUT, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    while (seq < 5)
    {
        sendto(sockfd, frames[seq], strlen(frames[seq]) + 1, 0,
               (struct sockaddr *)&rec, len);
        printf("Sent: %s\n", frames[seq]);

        int n = recvfrom(sockfd, ack, sizeof(ack), 0,
                         (struct sockaddr *)&rec, &len);
        if (n > 0 && strstr(ack, "ACK"))
        {
            printf("ACK received for %s\n\n", frames[seq]);
            seq++;
        }
        else
        {
            printf("Timeout! Resending %s\n\n", frames[seq]);
        }
    }

    printf("All frames sent successfully.\n");
    close(sockfd);
    return 0;
}
