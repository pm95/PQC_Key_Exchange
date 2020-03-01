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

void chat_with_server(int sockfd, int public_key)
{
    // character buffer for message string
    char buff[MAX];
    int N;

    while (1)
    {
        // zero out the buffer
        memset(buff, '\0', sizeof(buff));
        printf("Enter the string : ");
        N = 0;
        while ((buff[N++] = getchar()) != '\n')
            ;

        // send message to server
        write(sockfd, buff, sizeof(buff));

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
    alice.public_key = 1523;

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
    chat_with_server(sockfd, alice.public_key);

    // close the socket
    close(sockfd);
}
