#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define WINDOW_SIZE 3
#define TOTAL_FRAMES 5
#define TIMEOUT_SEC 2

int main() {
    int sockfd;
    struct sockaddr_in rec;
    socklen_t len = sizeof(rec);
    char *frames[] = {"Frame 1", "Frame 2", "Frame 3", "Frame 4", "Frame 5"};
    char ackbuf[32];

    int acked[TOTAL_FRAMES] = {0};      // 1 if frame i was ACKed
    int sent_once[TOTAL_FRAMES] = {0};  // 1 if frame i has been sent at least once in current attempt
    int base = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); return 1; }

    rec.sin_family = AF_INET;
    rec.sin_port = htons(PORT);
    rec.sin_addr.s_addr = inet_addr("127.0.0.1");

    // set receive timeout
    struct timeval tv;
    tv.tv_sec = TIMEOUT_SEC;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("setsockopt");
        close(sockfd);
        return 1;
    }

    printf("Selective Repeat ARQ Simulation (Sender) - fixed\n");

    while (base < TOTAL_FRAMES) {
        // send frames in window that are not yet ACKed and haven't been sent in this attempt
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i) {
            if (!acked[i] && !sent_once[i]) {
                ssize_t s = sendto(sockfd, frames[i], strlen(frames[i]) + 1, 0,
                                   (struct sockaddr *)&rec, len);
                if (s < 0) { perror("sendto"); }
                else {
                    printf("Sent: %s\n", frames[i]);
                    sent_once[i] = 1;
                }
            }
        }

        // collect ACKs until timeout occurs
        while (1) {
            ssize_t n = recvfrom(sockfd, ackbuf, sizeof(ackbuf), 0,
                                 (struct sockaddr *)&rec, &len);
            if (n < 0) {
                if (errno == EWOULDBLOCK || errno == EAGAIN) {
                    // timeout - break to resend unacked frames in window
                    printf("Timeout waiting for ACKs. Will resend unacked frames in window.\n");
                    // reset sent_once[] for frames in window so they'll be resent
                    for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i) {
                        sent_once[i] = 0;
                    }
                    break;
                } else {
                    perror("recvfrom");
                    close(sockfd);
                    return 1;
                }
            } else {
                ackbuf[n] = '\0';
                int ack_no = atoi(ackbuf); // receiver sends "0","1",...
                if (ack_no >= 0 && ack_no < TOTAL_FRAMES && !acked[ack_no]) {
                    acked[ack_no] = 1;
                    printf("ACK received for Frame %d\n", ack_no + 1);
                } else {
                    printf("Received duplicate/invalid ACK: %s\n", ackbuf);
                }

                // slide base while consecutive frames from base are ACKed
                while (base < TOTAL_FRAMES && acked[base]) {
                    base++;
                }

                // if window moved forward, we want to allow sending new frames in new window:
                // mark sent_once for new frames as 0 (they haven't been sent yet)
                for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i) {
                    if (!acked[i]) sent_once[i] = sent_once[i]; // keep previous state
                }

                // if all frames acked, break
                if (base >= TOTAL_FRAMES) break;

                // continue receiving more ACKs until timeout
            }
        }

        // loop repeats: will send any new frames in window (sent_once reset for them)
    }

    printf("\nAll frames sent and acknowledged!\n");
    close(sockfd);
    return 0;
}
