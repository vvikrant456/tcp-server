#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include<iostream>

int main() {
    // Step 1: Create the socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Step 2: Bind the socket to an IP and port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(8080);
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    
    // Step 3: Listen for incoming connections
    listen(server_fd, 3);
    
    printf("Server is running and listening on port 8080...\n");
    
    while (1) {  // Infinite loop to keep accepting new connections
        // Step 4: Accept an incoming connection (Three-way handshake happens here)
        int addrlen = sizeof(address);
        int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        
        if (new_socket < 0) {
            perror("Failed to accept connection");
            continue;
        }
        
        printf("Connection accepted.\n");

        // Step 5: Handle data transfer
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);   // Read data from client
        printf("Client message: %s\n", buffer);  // Print client's message
        
        // Respond to the client
        char *response = "Hello from server!";
        write(new_socket, response, strlen(response));
        
        // Step 6: Close the client connection (Four-way handshake)
        close(new_socket);   // Close the socket for this client
        printf("Connection closed.\n");
    }
    
    // Close the listening socket (this part will never be reached in the current loop)
    close(server_fd);
    
    return 0;
}
