#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 64  // small buffer for dmeo

void vulnerable_function(char *input) {
    char buffer[BUFFER_SIZE];
    printf("You said: ");
    gets(buffer); 
    printf("%s\n", buffer);
}


// We have to create a server that will be run on the docker container to attack.
//
// Somehow we have to be able to connect to the server in order to attack it!
// We could have the server take arbitrary inputs and if it hits the vulnerable_function we could give the user root access? haha
int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Vulnerable server running on port %d\n", PORT);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }



    char input[BUFFER_SIZE];
    read(new_socket, input, sizeof(input) - 1);
    input[sizeof(input) - 1] = '\0'; 
    printf("You're input is not correct!");
    vulnerable_function(input);

    close(new_socket);
    close(server_fd);
    return 0;
}
