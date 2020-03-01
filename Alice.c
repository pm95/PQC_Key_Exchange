#include "Public.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// additional imports
#include <unistd.h>
#include <arpa/inet.h>

#define SA struct sockaddr

struct Person alice;

void chat_with_server(int sockfd, int private_key)
{
    // character buffer for message string
    char buff[MAX];
    int N;

    int public_key = mod_exp(g, private_key, n);

    while (1)
    {
        // zero out the buffer
        memset(buff, '\0', sizeof(buff));
        N = 0;

        printf("Sending Alice's public key ... %d\n", public_key);
        sprintf(buff, "%d", public_key);

        // send message to server
        write(sockfd, buff, sizeof(buff));
        printf("Sent Alice's public key ... %d\n", public_key);

        // zero out the buffer
        memset(buff, '\0', sizeof(buff));

        // read message from server
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);

        if ((strncmp(buff, "exit", 4)) == 0)
        {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    printf("Hello from Alice");
    struct Person alice;
    alice.private_key = 1523;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    chat_with_server(sockfd, alice.private_key);

    // close the socket
    close(sockfd);
}
