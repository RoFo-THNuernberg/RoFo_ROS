#pragma once

#include "ros/ros.h"

#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>

enum {
    SOCKET_FAIL = -1,
    SOCKET_OK = 1
} SOCKET_STATUS;

/** 
 * \class Socket
 * 
 * \brief Abstraction layer for tcp socket communication.
 * It is safe to create multiple Socket objects. 
 * Note: Only the first instance calls create_socket() \n 
 * 
 * Workflow: instantiate new Socket object -> Call accept connection -> Send/receive data and periodically check sendFailed()
 */
class Socket
{
    public:
        Socket();
        ~Socket();

        /**
         * \brief Accept new connections.
         *
         * \return
         *  - connection file describtor (is also stored in variable _connection_fd); returns SOCKET_FAIL if accept failed
         */
        int accept_connection();
        
        /**
         * \brief Send operation 
         * Sets _send_failed to false if communication fails.
         * 
         * \param buffer 
         * \param buffer_len
         * 
         * \return 
         * - amount of bytes send; SOCKET_FAIL if the communication failed
         */
        int socket_send(uint8_t const* buffer, int buffer_len);

        /**
         * \brief Receive new data from connection with client. 
         * If communication with client failed, _send_failed gets set to false
         * 
         * \param rx_buffer Buffer for storing received data
         * \param recv_bytes Maximum amount of bytes to be received in the buffer
         * 
         * \return 
         * - amount of bytes received; SOCKET_FAIL if the communication failed
         */
        int socket_receive(uint8_t* rx_buffer, int recv_bytes);

        int socket_receive_nonblock(uint8_t* rx_buffer, int recv_bytes);

        int socket_receive_string(std::string& new_string, int max_bytes);

        void close_connection();

    private:

        /**
         * \brief Creates a server socket, which is ready for accepting connections from clients.
         * This function is only called at the construction of the first socket object.
         */
        void _create_socket();

        void _enable_keep_alive();

        int _connection_fd;

        int const _socket_port;
        int const _socket_max_conn;
        static int _socket_fd;
        struct sockaddr_in _socket_addr;
};