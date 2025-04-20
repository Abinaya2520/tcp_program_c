/*
 * File: tcp_server.c
 * Description: TCP Server using POSIX socket API.
 *              - Listens on port 8080
 *              - Receives a greeting from the client
 *              - Sends a response
 *              - Receives a struct
 *              - Sends a response struct
 * Author: Abinaya
 * Platform: Linux (POSIX compliant)
 */

 #include "stdio.h"
 #include "stdlib.h"
 #include "string.h"
 #include "unistd.h"
 #include "arpa/inet.h"
 
 #define PORT 8080
 
 // Struct for exchanging structured data
 struct Data 
 {
     char name[50];
     int id;
     float value;
 };
 
 int main() 
 {
     int server_fd, new_socket;
     struct sockaddr_in address;
     int addrlen = sizeof(address);
     char buffer[1024] = {0};
     struct Data recv_data, send_data;
 
     // Create socket
     server_fd = socket(AF_INET, SOCK_STREAM, 0);
     if (server_fd == -1)
     {
         perror("Socket creation failed");
         exit(0);
     }
 
     // Configure address
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = inet_addr("172.31.170.25");  // Ip address
     address.sin_port = htons(PORT);
 
     // Bind socket
     if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) 
     { 
         perror("Bind failed");
         close(server_fd);
         exit(0);
     }
 
     // Listen for connections
     if (listen(server_fd, 3) < 0) 
     {
         perror("Listen failed");
         close(server_fd);
         exit(0);
     }
 
     printf("Server listening on port %d\n",PORT);
 
     // Accept client connection
     new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
     if (new_socket < 0) 
     {
         perror("Accept failed");
         close(server_fd);
         exit(EXIT_FAILURE);
     }
 
     // Receive
     read(new_socket, buffer, sizeof(buffer));
     printf("Client: %s\n", buffer);
 
     // Send
     char *response = "Hello from server";
     send(new_socket, response, strlen(response), 0);
 
     //  Receive struct
     recv(new_socket, &recv_data, sizeof(recv_data), 0);
     printf("Struct received - Name: %s, ID: %d, Value: %.2f\n", recv_data.name, recv_data.id, recv_data.value);
 
     // Step 4: send struct response
     strcpy(send_data.name, "Server");
     send_data.id = recv_data.id + 1;
     send_data.value = recv_data.value + 10.0;
     send(new_socket, &send_data, sizeof(send_data), 0);
 
     printf("Struct sent - Name: %s, ID: %d, Value: %.2f\n", send_data.name, send_data.id, send_data.value);
 
     // close
     close(new_socket);
     close(server_fd);
 
     return 0;
 }
 
