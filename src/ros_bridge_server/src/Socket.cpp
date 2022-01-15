#include "Socket.h"

#define SOCKET_PORT 2888
#define MAX_CONNECTION 10
#define KEEP_ALIVE_TIMEOUT 4
#define KEEP_ALIVE_PERIOD 1

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

                    int flags = fcntl(_socket_fd, F_GETFL);
                    fcntl(_socket_fd, F_SETFL, flags | O_NONBLOCK);

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

void Socket::_enable_keep_alive()
{
    int op_value = 1;
    setsockopt(_connection_fd, SOL_SOCKET, SO_KEEPALIVE, &op_value, sizeof(int));
    op_value = KEEP_ALIVE_PERIOD,
    setsockopt(_connection_fd, IPPROTO_TCP, TCP_KEEPIDLE, &op_value, sizeof(int));
    op_value = KEEP_ALIVE_TIMEOUT;
    setsockopt(_connection_fd, IPPROTO_TCP, TCP_KEEPINTVL, &op_value, sizeof(int));
    op_value = 5;
    setsockopt(_connection_fd, IPPROTO_TCP, TCP_KEEPCNT, &op_value, sizeof(int));
}


int Socket::accept_connection()
{   
    return _connection_fd = accept4(_socket_fd, NULL, NULL, SOCK_NONBLOCK);
}

/*
int Socket::accept_connection()
{   
    return _connection_fd = accept(_socket_fd, NULL, NULL);
}
*/

bool Socket::is_connected()
{
    return _is_connected;
}

/*
int Socket::socket_receive(uint8_t* rx_buffer, int recv_bytes)
{
    int len = recv(_connection_fd, rx_buffer, recv_bytes, 0);

    if(len == SOCKET_FAIL && errno == EWOULDBLOCK)
        len = 0;
    else if(len == SOCKET_FAIL)
        _is_connected = false;

    return len;
}
*/

int Socket::socket_receive(uint8_t* rx_buffer, int recv_bytes)
{
    int bytes_read = 0;

    do
    {   
        bytes_read = recv(_connection_fd, rx_buffer, recv_bytes, 0);

        if(bytes_read == SOCKET_FAIL && errno == EWOULDBLOCK)
            bytes_read = 0;

        recv_bytes -= bytes_read;
    } 
    while (recv_bytes > 0 && bytes_read != SOCKET_FAIL);


    return bytes_read;
}

int Socket::socket_receive_string(std::string& new_string, int max_bytes)
{
    int bytes_read = 0;
    char rx_buffer[max_bytes];

    for(int i = 0; i < max_bytes; i++)
    {
        do
        {
            bytes_read = recv(_connection_fd, rx_buffer + i, 1, 0);
        } 
        while(bytes_read == SOCKET_FAIL && errno == EWOULDBLOCK);

        if(bytes_read == SOCKET_FAIL || rx_buffer[i] == '\0')
            break;
    }

    if(bytes_read != SOCKET_FAIL    )
        new_string.assign(rx_buffer);
    
    return bytes_read;
}

int Socket::socket_receive_nonblock(uint8_t* rx_buffer, int recv_bytes)
{
    int len = recv(_connection_fd, rx_buffer, recv_bytes, 0);

    if(len == SOCKET_FAIL && errno == EWOULDBLOCK)
        len = 0;

    return len;
}

int Socket::socket_send(uint8_t const* buffer, int buffer_len)
{
    int err = send(_connection_fd, buffer, buffer_len, 0);

    if(err == SOCKET_FAIL && errno == EWOULDBLOCK)
        err = 0;
    else if (err == SOCKET_FAIL)
        _is_connected = false;

    return err;
}

void Socket::close_connection()
{
    _is_connected = false;
    shutdown(_connection_fd, SHUT_RDWR);
    close(_connection_fd);
}