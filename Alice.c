#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// additional imports
#include <unistd.h>
#include <arpa/inet.h>

// key-generation imports
#include "ServerConfig.h"
#include "../PQCrypto-SIDH/src/P434/P434_api.h"

#define SA struct sockaddr

void key_exchange_with_bob(int sockfd)
{
    printf("\n\nAlice starting key exchange ...\n");

    // declare char arrays to hold private, public and shared secret info
    unsigned char alice_private_key[SIDH_SECRETKEYBYTES_A] = {0};
    unsigned char alice_public_key[SIDH_PUBLICKEYBYTES] = {0};
    unsigned char bob_public_key[SIDH_PUBLICKEYBYTES] = {0};
    unsigned char shared_secret[SIDH_BYTES] = {0};

    // generate Alice's private key
    random_mod_order_A_SIDHp434(alice_private_key);
    int pk_gen_flag = EphemeralKeyGeneration_A_SIDHp434(alice_private_key, alice_public_key);

    // send Alice's public key to Bob
    write(sockfd, alice_public_key, SIDH_PUBLICKEYBYTES);

    // read Bob's public key
    read(sockfd, bob_public_key, SIDH_PUBLICKEYBYTES);

    // generate shared secret
    int ss_gen_flag = EphemeralSecretAgreement_A_SIDHp434(alice_private_key, bob_public_key, shared_secret);

    printf("Alice's public key: %s\n", alice_public_key);
    printf("Alice's private key: %s\n", alice_private_key);
    printf("Bob's public key: %s\n", bob_public_key);
    printf("\n\nShared secret generated: %s\n\n", shared_secret);
    printf("Key exchange complete\n\n");
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    printf("Hello from Alice\n");

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
    key_exchange_with_bob(sockfd);

    // close the socket
    close(sockfd);
}
