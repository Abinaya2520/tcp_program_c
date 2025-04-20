/*
 * File: tcp_client.c
 * Description: TCP Client using POSIX socket API.
 *              - Connects to server on port 8080
 *              - Sends greeting
 *              - Receives server response
 *              - Sends a struct
 *              - Receives response struct
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
 struct Data {
     char name[50];
     int id;
     float value;
 };
 
 int main() {
     int sock;
     struct sockaddr_in serv_addr;
     char buffer[1024] = {0};
     struct Data send_data, recv_data;
 
     // Create socket
     sock = socket(AF_INET, SOCK_STREAM, 0);
     if (sock < 0) 
     {
         perror("Socket creation failed");
         exit(0);
     }
 
     // Configure server address
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr("172.31.170.25");  // IP address
     serv_addr.sin_port = htons(PORT);
 
     // Connect to server
     if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
     {
         perror("Connection failed");
         close(sock);
         exit(0);
     }
 
     // Send 
     char *message = "Hello from client";
     send(sock, message, strlen(message), 0);
     printf("Sent to server: %s\n", message);
 
     // Receive 
     read(sock, buffer, sizeof(buffer));
     printf("Server: %s\n", buffer);
 
     // Step 3: Send struct
     strcpy(send_data.name, "Client1");
     send_data.id = 1;                    // dummy value
     send_data.value = 55.5;
     send(sock, &send_data, sizeof(send_data), 0);
     printf("Struct sent - Name: %s, ID: %d, Value: %.2f\n", send_data.name, send_data.id, send_data.value);
 
     // Step 4: Receive struct
     recv(sock, &recv_data, sizeof(recv_data), 0);
     printf("Struct received - Name: %s, ID: %d, Value: %.2f\n", recv_data.name, recv_data.id, recv_data.value);
 
     // close
     close(sock);
 
     return 0;
 }
 