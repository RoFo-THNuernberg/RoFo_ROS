#pragma once

#include "Socket.h" 
#include "RosMsgs.h"
#include "SubscriberCallback.h"
#include "Publisher.h"
#include "msg_id.h"
#include "SmartBufferPtr.h"

#include <thread>
#include <string>
#include <vector>

#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"

/**
 * \class CommuniatonHandler
 * 
 * \brief Handles connection and communication with client. Creates a thread for receiving and interpreting received data.
 * Registers ros subscriber => Socket send operations are triggered by ros subscriber callback.
 * 
 * Workflow: Create Socket object -> wait for Socket object to accept new connection -> create CommunicationHandler object
 * => pass Socket object in constructor
 */
class CommunicationHandler
{
    public:
        CommunicationHandler(Socket& sock);
        ~CommunicationHandler();

    private:
        /**
         * \brief Handles connection and communication with client
         * 
         * \param conn_handle Connection Handler object
         * 
         * \return Returns only if communication fails. Deletes dynamically allocated CommunicationHandler object
         */
        static void _communication_handler(CommunicationHandler *conn_handle);

        static void _check_keep_alive(CommunicationHandler *conn_handle);

        /**
         * \brief Receive and interpret incoming data from client
         * 
         * \return SOCKET_OK if receive and interpret successful; else SOCKET_FAIL
         */
        int _interpret_receive();


        int _send_keep_alive();


        PublisherInterface* _getPublisher(const std::string& topic);

        void _unadvertise();
        void _advertise(std::string const& topic, std::string const& message_type);
        void _subscribe(std::string const& topic, std::string const& message_type);
        void _unsubscribe();

        Socket& _sock;
        ros::NodeHandle *_node_handle = nullptr;
        std::string _namespace;

        uint64_t _robot_time_difference_us;
        uint64_t _keep_alive_time_us;
        uint64_t _last_send_keep_alive_us;

        bool _communication_initialized = false;

        std::thread _communication_handler_thread;
        std::thread _check_keep_alive_thread;

        std::vector<PublisherInterface*> _publisher;
        std::vector<SubscriberCallback*> _subscriber;
};
