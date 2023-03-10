// Generated by gencpp from file trajecgenerator/float32RequestResponse.msg
// DO NOT EDIT!


#ifndef TRAJECGENERATOR_MESSAGE_FLOAT32REQUESTRESPONSE_H
#define TRAJECGENERATOR_MESSAGE_FLOAT32REQUESTRESPONSE_H


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
struct float32RequestResponse_
{
  typedef float32RequestResponse_<ContainerAllocator> Type;

  float32RequestResponse_()
    {
    }
  float32RequestResponse_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> const> ConstPtr;

}; // struct float32RequestResponse_

typedef ::trajecgenerator::float32RequestResponse_<std::allocator<void> > float32RequestResponse;

typedef boost::shared_ptr< ::trajecgenerator::float32RequestResponse > float32RequestResponsePtr;
typedef boost::shared_ptr< ::trajecgenerator::float32RequestResponse const> float32RequestResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::trajecgenerator::float32RequestResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace trajecgenerator

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::trajecgenerator::float32RequestResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "trajecgenerator/float32RequestResponse";
  }

  static const char* value(const ::trajecgenerator::float32RequestResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::trajecgenerator::float32RequestResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct float32RequestResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::trajecgenerator::float32RequestResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::trajecgenerator::float32RequestResponse_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // TRAJECGENERATOR_MESSAGE_FLOAT32REQUESTRESPONSE_H
