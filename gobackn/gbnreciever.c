#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, expected = 1;
    struct sockaddr_in serv, snd;
    char buffer[1024], ack[10];
    socklen_t len = sizeof(snd);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    printf("Go-Back-N Receiver ready...\n");

    while (1)
    {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&snd, &len);
        printf("Received: %s\n", buffer);

        int fno;
        sscanf(buffer, "Frame %d", &fno);

        // Intentionally drop ACK for Frame 3
        if (fno == 3)
        {
            printf("!! ACK lost for Frame %d\n\n", fno);
            continue;
        }

        if (fno == expected)
        {
            printf("Accepted Frame %d\n", fno);
            expected++;
        }
        else
        {
            printf("Out of order Frame %d discarded\n", fno);
        }

        sprintf(ack, "ACK%d", expected - 1);
        sendto(sockfd, ack, strlen(ack) + 1, 0, (struct sockaddr *)&snd, len);
        printf("Sent %s\n\n", ack);
    }

    close(sockfd);
    return 0;
}
