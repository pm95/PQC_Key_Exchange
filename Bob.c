#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

// additional imports
#include <unistd.h>
#include <arpa/inet.h>

// key-generation imports
#include "Public.h"
#include "../PQCrypto-SIDH/src/P434/P434_api.h"

#define SA struct sockaddr

// Function designed for chat between client and server.
void key_exchange_with_alice(int sockfd)
{
    printf("\n\nBob continuing key exchange ...\n");

    // declare char arrays to hold private, public and shared secret info
    unsigned char bob_private_key[SIDH_SECRETKEYBYTES_A] = {0};
    unsigned char bob_public_key[SIDH_PUBLICKEYBYTES] = {0};
    unsigned char alice_public_key[SIDH_PUBLICKEYBYTES] = {0};
    unsigned char shared_secret[SIDH_BYTES] = {0};

    // generate Bob's private key
    random_mod_order_A_SIDHp434(bob_private_key);
    int pk_gen_flag = EphemeralKeyGeneration_A_SIDHp434(bob_private_key, bob_public_key);

    // read Alice's public key
    read(sockfd, alice_public_key, SIDH_PUBLICKEYBYTES);

    // send Bob's public key to Alice
    write(sockfd, bob_public_key, SIDH_PUBLICKEYBYTES);

    // generate shared secret
    int ss_gen_flag = EphemeralSecretAgreement_B_SIDHp434(bob_private_key, bob_public_key, shared_secret);

    printf("Bob's public key: %s\n", bob_public_key);
    printf("Bob's private key: %s\n", bob_private_key);
    printf("Alice's public key: %s\n", alice_public_key);
    printf("\n\nShared secret generated: %s\n\n", shared_secret);
    printf("Key exchange complete\n\n");
}

// Driver function
int main()
{
    // define bob's member variables
    printf("Hello from Bob\n");

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    key_exchange_with_alice(connfd);

    // After chatting close the socket
    close(sockfd);
}
