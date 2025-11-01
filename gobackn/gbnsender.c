#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TIMEOUT 2
#define WINDOW_SIZE 3
#define TOTAL_FRAMES 7

int main() {
    int sockfd, base = 1, nextseq = 1;  // start from Frame 1
    struct sockaddr_in rec;
    char *frames[] = {"Frame 1", "Frame 2", "Frame 3", "Frame 4", "Frame 5", "Frame 6", "Frame 7"};
    char ack[10];
    socklen_t len = sizeof(rec);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    rec.sin_family = AF_INET;
    rec.sin_port = htons(8080);
    rec.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct timeval tv = {TIMEOUT, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    printf("Go-Back-N Sender started...\n");

    while (base <= TOTAL_FRAMES) {
        // Send frames within window
        while (nextseq < base + WINDOW_SIZE && nextseq <= TOTAL_FRAMES) {
            sendto(sockfd, frames[nextseq - 1], strlen(frames[nextseq - 1]) + 1, 0, (struct sockaddr*)&rec, len);
            printf("Sent: %s\n", frames[nextseq - 1]);
            nextseq++;
        }

        int n = recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr*)&rec, &len);
        if (n > 0 && strstr(ack, "ACK")) {
            int ackno = atoi(ack + 3); // parse ACKx (no space)
            printf("Received %s (ACK for Frame %d)\n\n", ack, ackno);

            // Slide window
            if (ackno >= base)
                base = ackno + 1;
        } else {
            printf("Timeout! Resending from Frame %d\n\n", base);
            nextseq = base; // resend all unacknowledged frames
        }
    }

    printf("All frames sent successfully.\n");
    close(sockfd);
    return 0;
}
