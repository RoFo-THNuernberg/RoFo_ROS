// Generated by gencpp from file trajecgenerator/boolRequestResponse.msg
// DO NOT EDIT!


#ifndef TRAJECGENERATOR_MESSAGE_BOOLREQUESTRESPONSE_H
#define TRAJECGENERATOR_MESSAGE_BOOLREQUESTRESPONSE_H


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
struct boolRequestResponse_
{
  typedef boolRequestResponse_<ContainerAllocator> Type;

  boolRequestResponse_()
    {
    }
  boolRequestResponse_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> const> ConstPtr;

}; // struct boolRequestResponse_

typedef ::trajecgenerator::boolRequestResponse_<std::allocator<void> > boolRequestResponse;

typedef boost::shared_ptr< ::trajecgenerator::boolRequestResponse > boolRequestResponsePtr;
typedef boost::shared_ptr< ::trajecgenerator::boolRequestResponse const> boolRequestResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::trajecgenerator::boolRequestResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace trajecgenerator

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::trajecgenerator::boolRequestResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "trajecgenerator/boolRequestResponse";
  }

  static const char* value(const ::trajecgenerator::boolRequestResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::trajecgenerator::boolRequestResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct boolRequestResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::trajecgenerator::boolRequestResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::trajecgenerator::boolRequestResponse_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // TRAJECGENERATOR_MESSAGE_BOOLREQUESTRESPONSE_H
