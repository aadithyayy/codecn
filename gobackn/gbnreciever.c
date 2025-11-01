#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, expected = 1;
    struct sockaddr_in serv, snd;
    char buffer[1024], ack[10];
    socklen_t len = sizeof(snd);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    printf("Go-Back-N Receiver ready...\n");

    int drop_done = 0; // to drop ACK for Frame 3 once

    while (1) {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&snd, &len);
        printf("Received: %s\n", buffer);

        int fno;
        sscanf(buffer, "Frame %d", &fno);

        if (fno == expected) {
            printf("Accepted Frame %d\n", fno);

            // Drop ACK for Frame 3 only once
            if (fno == 3 && !drop_done) {
                printf("!! ACK lost for Frame %d\n\n", fno);
                drop_done = 1;
                // Do NOT increment expected yet, sender never got ACK
                // Still wait for retransmission of Frame 3
                continue;
            }

            expected++; // only move forward after valid ACK sent
        } 
        else {
            printf("Out of order Frame %d discarded\n", fno);
        }

        // Always send ACK for last in-order frame received
        sprintf(ack, "ACK%d", expected - 1);
        sendto(sockfd, ack, strlen(ack) + 1, 0, (struct sockaddr*)&snd, len);
        printf("Sent %s\n\n", ack);
    }

    close(sockfd);
    return 0;
}
