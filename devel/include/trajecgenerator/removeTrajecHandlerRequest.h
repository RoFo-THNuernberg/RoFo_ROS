// Generated by gencpp from file trajecgenerator/removeTrajecHandlerRequest.msg
// DO NOT EDIT!


#ifndef TRAJECGENERATOR_MESSAGE_REMOVETRAJECHANDLERREQUEST_H
#define TRAJECGENERATOR_MESSAGE_REMOVETRAJECHANDLERREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace trajecgenerator
{
template <class ContainerAllocator>
struct removeTrajecHandlerRequest_
{
  typedef removeTrajecHandlerRequest_<ContainerAllocator> Type;

  removeTrajecHandlerRequest_()
    : name()  {
    }
  removeTrajecHandlerRequest_(const ContainerAllocator& _alloc)
    : name(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _name_type;
  _name_type name;





  typedef boost::shared_ptr< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> const> ConstPtr;

}; // struct removeTrajecHandlerRequest_

typedef ::trajecgenerator::removeTrajecHandlerRequest_<std::allocator<void> > removeTrajecHandlerRequest;

typedef boost::shared_ptr< ::trajecgenerator::removeTrajecHandlerRequest > removeTrajecHandlerRequestPtr;
typedef boost::shared_ptr< ::trajecgenerator::removeTrajecHandlerRequest const> removeTrajecHandlerRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator1> & lhs, const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator2> & rhs)
{
  return lhs.name == rhs.name;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator1> & lhs, const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace trajecgenerator

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c1f3d28f1b044c871e6eff2e9fc3c667";
  }

  static const char* value(const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc1f3d28f1b044c87ULL;
  static const uint64_t static_value2 = 0x1e6eff2e9fc3c667ULL;
};

template<class ContainerAllocator>
struct DataType< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "trajecgenerator/removeTrajecHandlerRequest";
  }

  static const char* value(const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string name\n"
;
  }

  static const char* value(const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.name);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct removeTrajecHandlerRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::trajecgenerator::removeTrajecHandlerRequest_<ContainerAllocator>& v)
  {
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.name);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TRAJECGENERATOR_MESSAGE_REMOVETRAJECHANDLERREQUEST_H
