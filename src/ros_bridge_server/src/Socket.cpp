#include "Socket.h"

#define SOCKET_PORT 2888
#define MAX_CONNECTION 10

int Socket::_socket_fd = -1;

Socket::Socket() : _socket_port{SOCKET_PORT}, _socket_max_conn{MAX_CONNECTION} 
{
    if(_socket_fd == -1)
    {
        _socket_addr.sin_family = AF_INET;
        _socket_addr.sin_port = htons(_socket_port);
        _socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        _create_socket();
    }
}

Socket::~Socket() {}


void Socket::_create_socket()
{
    int cnt = 0;

    while(1)
    {
        _socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (_socket_fd >= 0)
        {
            if(bind(_socket_fd, (struct sockaddr *)&_socket_addr, sizeof(_socket_addr)) >= 0)
            {
                if(listen(_socket_fd, _socket_max_conn) >= 0)
                {
                    ROS_INFO("Successful! Start accepting connections.");
                    break;
                }
                else 
                    ROS_INFO("Listen for connections failed!");
            }
            else 
                ROS_INFO("Failed to bind socket!");

            close(_socket_fd);
        } 
        else
            ROS_INFO("Failed to create socket!");

        if(cnt < 4)
            ROS_INFO("Retrying... Attempt: %d", ++cnt);
        else
            exit(EXIT_FAILURE);
    }
}

int Socket::accept_connection()
{
    return _connection_fd = accept4(_socket_fd, NULL, NULL, SOCK_NONBLOCK);
}

int Socket::socket_receive(uint8_t* rx_buffer, int recv_bytes)
{
    int len = recv(_connection_fd, rx_buffer, recv_bytes, 0);

    return len;
}

void Socket::close_connection()
{
    shutdown(_connection_fd, SHUT_RDWR);
    close(_connection_fd);
}