#pragma once

#include "ros/ros.h"

#include <sys/socket.h>
#include <netinet/in.h>

enum {
    SOCKET_FAIL = -1,
    SOCKET_OK = 1
} SOCKET_STATUS;

class Socket
{
    public:
        Socket();
        ~Socket();

        int accept_connection();
        int socket_receive(uint8_t* rx_buffer, int recv_bytes);
        void close_connection();

    private:

        void _create_socket();

        int _connection_fd;

        int const _socket_port;
        int const _socket_max_conn;
        static int _socket_fd;
        struct sockaddr_in _socket_addr;
};