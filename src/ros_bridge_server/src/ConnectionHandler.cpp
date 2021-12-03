#include "ConnectionHandler.h"

enum MSG_ID {
    INIT_ID = 0x01,
    ADVERTISE_ID,
    PUBLISH_ID
};

ConnectionHandler::ConnectionHandler() : _sock() {}

ConnectionHandler::~ConnectionHandler()  
{   
    _unadvertise();

    if(_node_handle != nullptr)
        delete _node_handle;
}

int ConnectionHandler::wait_for_accept()
{   
    int status = -1;

    if(_sock.accept_connection() != SOCKET_FAIL)
    {
        ROS_INFO("Accepted connection!");

        std::thread client_handler(handler_function, this);
        client_handler.detach();
        
        status = 1;
    }

    return status;
}

void ConnectionHandler::handler_function(ConnectionHandler *conn_handle)
{   
    ros::Rate loop_rate(10);

    while(1)
    {
        if(conn_handle->_receive_new_msg() == SOCKET_FAIL)
            break;

    
        loop_rate.sleep();
    }

    ROS_INFO("Error closing connection...");

    conn_handle->_sock.close_connection();

    delete conn_handle;
}

int ConnectionHandler::_receive_new_msg()
{   
    uint8_t rx_buffer[RX_BUFFER_LEN];

    uint8_t* rx_buffer_ptr = rx_buffer;

    int len = _sock.socket_receive(rx_buffer, RX_BUFFER_LEN);

    printf("Error: %d\n", errno);

    if(len == SOCKET_FAIL && errno != EWOULDBLOCK)
        return SOCKET_FAIL;
    else if(len == SOCKET_FAIL)
        return SOCKET_OK;

    printf("Received: ");
    for(int i = 0; i < len; i++)
        printf("%2x", rx_buffer[i]);
    printf("\n");
    printf("Received: ");
    for(int i = 0; i < len; i++)
        printf("%c", rx_buffer[i]);
    printf("\n");

    while(rx_buffer_ptr < (len + rx_buffer))
    {
        switch(rx_buffer_ptr[0])
        {
            case INIT_ID:
                rx_buffer_ptr++;

                ROS_INFO("Received Initialize message!");

                _namespace = (char*)rx_buffer_ptr;
                rx_buffer_ptr += _namespace.size() + 1;

                _node_handle = new ros::NodeHandle(_namespace);

                break;

            
            case ADVERTISE_ID:
            {
                rx_buffer_ptr++;

                std::string topic = (char*)rx_buffer_ptr;
                rx_buffer_ptr += topic.size() + 1;

                std::string message_type = (char*)rx_buffer_ptr;
                rx_buffer_ptr += message_type.size() + 1;

                ROS_INFO("Advertising Topic: %s, MsgType: %s", topic.c_str(), message_type.c_str());

                _advertise(topic, message_type);
                break;
            }
            
            case PUBLISH_ID:
            {   
                rx_buffer_ptr++;

                std::string topic = (char*)(rx_buffer_ptr);
                rx_buffer_ptr += topic.size() + 1;

                ROS_INFO("Received topic: %s", topic.c_str());

                ros::Publisher* pub = _getPublisher(topic);

                if(pub != nullptr && _node_handle != nullptr)
                {
                    if(topic == "pose2D") 
                    {
                        ros_msgs::Pose2D pose;
                        rx_buffer_ptr = pose.deserialize(rx_buffer_ptr);
                        pub->publish((geometry_msgs::Pose2D)pose);
                    }
                }
                break;
            }
        }
    }

    return SOCKET_OK;
}

ros::Publisher* ConnectionHandler::_getPublisher(std::string const& topic)
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

void ConnectionHandler::_advertise(std::string const& topic, std::string const& message_type)
{   
    ros::Publisher * new_pub;

    if(message_type == "Pose2D")
        new_pub = new ros::Publisher(_node_handle->advertise<geometry_msgs::Pose2D>(topic, 10, false));


    _publisher.push_back(new_pub);
}

void ConnectionHandler::_unadvertise() {
    for(auto i : _publisher)
        delete i;
}




