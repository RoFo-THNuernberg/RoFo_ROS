#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler(Socket& sock) : _sock{sock}, _communication_handler_thread(_communication_handler, this),
    _check_keep_alive_thread(_check_keep_alive, this) 
{
        _communication_handler_thread.detach();

        _keep_alive_time_us = ros::Time::now().toNSec() / 1000;
        _last_send_keep_alive_us = ros::Time::now().toNSec() / 1000;
}

CommunicationHandler::~CommunicationHandler()  
{   

    ROS_INFO_NAMED(_namespace.c_str(), "Destruct Connection Handler");
    _unadvertise();
    _unsubscribe();

    if(_node_handle != nullptr)
        delete _node_handle;
    
    delete &_sock;
}

void CommunicationHandler::_communication_handler(CommunicationHandler *conn_handle)
{   
    ros::Rate loop_rate(100);

    while(ros::ok())
    {   
        if(conn_handle->_sock.is_connected() == false)
            break;

        if(conn_handle->_send_keep_alive() != SOCKET_FAIL)
            if(conn_handle->_interpret_receive() == SOCKET_FAIL)
                break;
    
        loop_rate.sleep();
    }

    ROS_INFO_NAMED(conn_handle->_namespace.c_str(), "Shutting down communication_handler_thread");

    conn_handle->_sock.close_connection();
    
    conn_handle->_check_keep_alive_thread.join();

    delete conn_handle;
}

void CommunicationHandler::_check_keep_alive(CommunicationHandler *conn_handle)
{   
    ros::Rate loop_rate(1000.0 / KEEP_ALIVE_CHECK_PERIOD_MS);

    while(ros::ok())
    {
        if(conn_handle->_sock.is_connected() == false)
            break;
        
        if((ros::Time::now().toNSec() / 1000 - conn_handle->_keep_alive_time_us) / 1000 > MAX_KEEP_ALIVE_TIMOUT_MS)
            break;

        loop_rate.sleep();
    }

    ROS_INFO_NAMED(conn_handle->_namespace.c_str(), "Shutting down keep_alive_thread!");

    conn_handle->_sock.close_connection();
}

int CommunicationHandler::_interpret_receive()
{   
    /*
    int status = SOCKET_OK;
    
    uint8_t rx_buffer[RX_BUF_LEN];
    uint8_t* rx_buffer_ptr = rx_buffer;

    int len = _sock.socket_receive(rx_buffer, RX_BUF_LEN);

    if(len == -1)
        status = SOCKET_FAIL;
        */

    int socket_len_err = 0;

    uint8_t* rx_buffer[64];
    int rx_buffer_length = 0;
    int rx_buffer_row = 0;

    do {
        rx_buffer[rx_buffer_row] = new uint8_t[RX_BUF_LEN];

        socket_len_err = _sock.socket_receive(rx_buffer[rx_buffer_row], RX_BUF_LEN);
        rx_buffer_length += socket_len_err;

        rx_buffer_row++;

    } while (socket_len_err == RX_BUF_LEN && rx_buffer_row < 64);

    SmartBufferPtr rx_buffer_ptr(rx_buffer, RX_BUF_LEN, rx_buffer_row);


    //Guarantees that the first message is the initialize packet
    if(_communication_initialized == false && rx_buffer_ptr[0] != INIT_ID && socket_len_err != 0)
        socket_len_err = SOCKET_FAIL;
 

    while(rx_buffer_length > rx_buffer_ptr - SmartBufferPtr(rx_buffer, RX_BUF_LEN, rx_buffer_row) && socket_len_err != SOCKET_FAIL)
    {   
        switch(rx_buffer_ptr[0])
        {   
            case INIT_ID:
            {
                rx_buffer_ptr += 1;

                _namespace << rx_buffer_ptr;
                rx_buffer_ptr += _namespace.size() + 1;

                _communication_initialized = true;

                ROS_INFO_NAMED(_namespace.c_str(), "Received Initialize message! Client name: %s", _namespace.c_str());

                _node_handle = new ros::NodeHandle(_namespace);
                _subscribe("set_pose2D", "geometry_msgs/Pose2D");
                _subscribe("goal_point", "geometry_msgs/Point");
                _advertise("pose2D", "geometry_msgs/Pose2D");

                break;
            }
            case KEEP_ALIVE_ID:
            {
                rx_buffer_ptr += 1;

                uint64_t robot_time;
                robot_time << rx_buffer_ptr;
                rx_buffer_ptr += sizeof(uint64_t);

                _keep_alive_time_us = ros::Time::now().toNSec() / 1000;

                _robot_time_difference_us = _keep_alive_time_us - robot_time;

                ROS_INFO_NAMED(_namespace.c_str(), "Keep Alive! Robot Time: %ld", robot_time);

                break;
            }
            case PUBLISH_ID:
            {
                rx_buffer_ptr += 1;

                std::string topic;
                topic << rx_buffer_ptr;
                rx_buffer_ptr += topic.size() + 1;

                ROS_INFO_NAMED(_namespace.c_str(), "Received topic: %s", topic.c_str());
            
                ros_msgs::Pose2D pose;
                pose.deserialize(rx_buffer_ptr);
                rx_buffer_ptr += pose.getSize();
                
                PublisherInterface* pub = _getPublisher(topic);

                if(pub != nullptr)
                {   
                    pub->getMsgType()->deserialize(rx_buffer_ptr);
                    rx_buffer_ptr += pub->getMsgType()->getSize();

                    pub->publish();
                }
                else
                    socket_len_err = SOCKET_FAIL;

                break;
            }
            default:
                socket_len_err = SOCKET_FAIL;
                break;
        }
    }

    return socket_len_err;
}

int CommunicationHandler::_send_keep_alive()
{   
    uint64_t time_now_us = ros::Time::now().toNSec() / 1000;

    if((time_now_us - _last_send_keep_alive_us) / 1000 > KEEP_ALIVE_SEND_PERIOD_MS)
    {
        uint8_t pkt_buffer[1 + sizeof(uint64_t)];
        int pkt_len = 0;

        pkt_buffer[0] = KEEP_ALIVE_ID;
        pkt_len++;  

        *(uint64_t*)(pkt_buffer + pkt_len) = time_now_us;

        pkt_len += sizeof(uint64_t);

        _sock.socket_send(pkt_buffer, pkt_len);
    }

    return SOCKET_OK;
}

PublisherInterface* CommunicationHandler::_getPublisher(std::string const& topic)
{
    std::string full_topic_name = _node_handle->getNamespace() + "/" + topic; 

    for(auto i : _publisher)
    {
        if(i->getTopic() == full_topic_name)
        {   
            return i;
        }
    }

    return nullptr;
}

void CommunicationHandler::_advertise(std::string const& topic, std::string const& message_type)
{   
    PublisherInterface* new_pub = nullptr;

    if(message_type == "geometry_msgs/Pose2D")
        new_pub = new Publisher<geometry_msgs::Pose2D>(_node_handle, topic, new ros_msgs::Pose2D);
    else if (message_type == "geometry_msgs/Twist")
        new_pub = new Publisher<geometry_msgs::Twist>(_node_handle, topic, new ros_msgs::Twist2D);
    else if (message_type == "geometry_msgs/Point")
        new_pub = new Publisher<geometry_msgs::Point>(_node_handle, topic, new ros_msgs::Point2D);
    else if (message_type == "std_msgs/String")
        new_pub = new Publisher<std_msgs::String>(_node_handle, topic, new ros_msgs::String);

    if(new_pub != nullptr)
        _publisher.push_back(new_pub);
}

void CommunicationHandler::_subscribe(std::string const& topic, std::string const& message_type)
{
    SubscriberCallback *new_sub = new SubscriberCallback(topic, &_sock);

    if(message_type == "geometry_msgs/Pose2D")
        new_sub->create_subscribtion<geometry_msgs::Pose2D, ros_msgs::Pose2D>(topic, _node_handle);
    else if(message_type == "geometry_msgs/Twist")
        new_sub->create_subscribtion<geometry_msgs::Twist, ros_msgs::Twist2D>(topic, _node_handle);
    else if(message_type == "geometry_msgs/Point")
        new_sub->create_subscribtion<geometry_msgs::Point, ros_msgs::Point2D>(topic, _node_handle);
    else if(message_type == "std_msgs/String")
        new_sub->create_subscribtion<std_msgs::String, ros_msgs::String>(topic, _node_handle);
    else
    {
        delete new_sub;
        new_sub = nullptr;
    }

    if(new_sub != nullptr)
        _subscriber.push_back(new_sub);
}

void CommunicationHandler::_unsubscribe()
{
    for(auto i : _subscriber)
        delete i;
}

void CommunicationHandler::_unadvertise() 
{
    for(auto i : _publisher)
        delete i;
}




