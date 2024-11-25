#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

#define PROGRAM "format"
#define PORT    9090
#define BUFFER_SIZE 256

int socket_bind(int port);
int server_accept(int listen_fd, struct sockaddr_in *client);
char **generate_random_env(int length);

void main()
{
    int listen_fd;
    struct sockaddr_in client;

    // Generate a random number
    srand(time(NULL));
    int random_n = rand() % 2000;

    // handle signal from child processes
    signal(SIGCHLD, SIG_IGN);

    listen_fd = socket_bind(PORT);
    while (1) {
        int socket_fd = server_accept(listen_fd, &client);

        if (socket_fd < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        if (pid == 0) {
            // Child process
            close(listen_fd);

            // Buffer to store client input
            char buffer[BUFFER_SIZE];
            memset(buffer, 0, BUFFER_SIZE);

            while (1) {
                // Read data from the client
                int bytes_read = recv(socket_fd, buffer, BUFFER_SIZE - 1, 0);
                if (bytes_read <= 0) {
                    if (bytes_read < 0) {
                        perror("recv failed");
                    }
                    close(socket_fd);
                    exit(EXIT_FAILURE);
                }

                buffer[bytes_read] = '\0';

                printf("Received from client: %s\n", buffer);

                // Check for buffer overflow
                if (bytes_read >= BUFFER_SIZE - 1) {
                    const char *overflow_msg = "Buffer overflow detected\n";
                    send(socket_fd, overflow_msg, strlen(overflow_msg), 0);
                } else {
                    const char *no_overflow_msg = "No buffer overflow\n";
                    send(socket_fd, no_overflow_msg, strlen(no_overflow_msg), 0);
                }

                // Redirect STDIN to this connection, so it can take input from user
                dup2(socket_fd, STDIN_FILENO);

                // Invoke the program
                fprintf(stderr, "Starting %s\n", PROGRAM);
                execle(PROGRAM, PROGRAM, (char *)NULL, generate_random_env(random_n));

                // If execle fails
                perror("execle failed");
                close(socket_fd);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            close(socket_fd);
        }
    }

    close(listen_fd);
}

int socket_bind(int port)
{
    int listen_fd;
    int opt = 1;
    struct sockaddr_in server;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    memset((char *) &server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if (bind(listen_fd, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_fd, 3) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    return listen_fd;
}

int server_accept(int listen_fd, struct sockaddr_in *client)
{
    int c = sizeof(struct sockaddr_in);

    int socket_fd = accept(listen_fd, (struct sockaddr *)client, (socklen_t *)&c);
    char *ipAddr = inet_ntoa(client->sin_addr);
    printf("Got a connection from %s\n", ipAddr);
    return socket_fd;
}

// Generate environment variables. The length of the environment affects 
// the stack location. This is used to add some randomness to the lab.
char **generate_random_env(int length)
{
    char **env = malloc(2 * sizeof(char *));
    env[0] = malloc(length);
    memset(env[0], 'A', length - 1);
    env[0][length - 1] = '\0';
    env[1] = NULL;
    return env;
}