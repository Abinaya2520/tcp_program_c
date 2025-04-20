TCP Client-Server Program in C (Linux)

Author: Abinaya  
Date: April 2025  
Platform: Linux (Tested on Ubuntu 22.04)

Description:

This project demonstrates a basic TCP client-server communication using C and POSIX sockets.

Features:

- Server listens on port 8080
- Client connects to the server, sends a greeting
- Server responds to greeting
- Client sends a struct (name, id, value)
- Server receives struct and sends back modified data

Files:

- tcp_server.c
- tcp_client.c

Build Instructions:

Open a terminal and compile both files using gcc

Run Instructions:

1. First, run the server

2. Then, in a separate terminal, run the client
