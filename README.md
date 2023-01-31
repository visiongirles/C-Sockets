# Server using Sockets in C

Here is a project to reproduce **LiveServer** extension for Visual Studio Code -> creating a customized localhost server using Sockets in C language on UNIX-system.

## Files

- server.c - a main file
- client.c - an _optional_ file, use if you need to see preconfigured connection in terminal

## To configure

    clang server.c -o build/server

Optional:

    clang client.c -o build/client

## To run

1.  Run the server first:

    build/server

2.  Run the client using either of the options:

**First option:** for prepared client's request run at the different terminal from where you server is running:

    build/client

**Second option:** type as url a-in any browser:

    https://localhost:8080

## Features

- Has a client.c to test prepared client's response
- Can be run at browser at https://localhost:8080
- Can be run on any port -> change #define SERVER_PORT
- Server.c prints supporting info on client's address & port
