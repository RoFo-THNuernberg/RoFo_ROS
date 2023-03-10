// Generated by gencpp from file trajecgenerator/boolRequest.msg
// DO NOT EDIT!


#ifndef TRAJECGENERATOR_MESSAGE_BOOLREQUEST_H
#define TRAJECGENERATOR_MESSAGE_BOOLREQUEST_H

#include <ros/service_traits.h>


#include <trajecgenerator/boolRequestRequest.h>
#include <trajecgenerator/boolRequestResponse.h>


namespace trajecgenerator
{

struct boolRequest
{

typedef boolRequestRequest Request;
typedef boolRequestResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct boolRequest
} // namespace trajecgenerator


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::trajecgenerator::boolRequest > {
  static const char* value()
  {
    return "88c93a4e354c9b18b18fde29f72f94c2";
  }

  static const char* value(const ::trajecgenerator::boolRequest&) { return value(); }
};

template<>
struct DataType< ::trajecgenerator::boolRequest > {
  static const char* value()
  {
    return "trajecgenerator/boolRequest";
  }

  static const char* value(const ::trajecgenerator::boolRequest&) { return value(); }
};


// service_traits::MD5Sum< ::trajecgenerator::boolRequestRequest> should match
// service_traits::MD5Sum< ::trajecgenerator::boolRequest >
template<>
struct MD5Sum< ::trajecgenerator::boolRequestRequest>
{
  static const char* value()
  {
    return MD5Sum< ::trajecgenerator::boolRequest >::value();
  }
  static const char* value(const ::trajecgenerator::boolRequestRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::trajecgenerator::boolRequestRequest> should match
// service_traits::DataType< ::trajecgenerator::boolRequest >
template<>
struct DataType< ::trajecgenerator::boolRequestRequest>
{
  static const char* value()
  {
    return DataType< ::trajecgenerator::boolRequest >::value();
  }
  static const char* value(const ::trajecgenerator::boolRequestRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::trajecgenerator::boolRequestResponse> should match
// service_traits::MD5Sum< ::trajecgenerator::boolRequest >
template<>
struct MD5Sum< ::trajecgenerator::boolRequestResponse>
{
  static const char* value()
  {
    return MD5Sum< ::trajecgenerator::boolRequest >::value();
  }
  static const char* value(const ::trajecgenerator::boolRequestResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::trajecgenerator::boolRequestResponse> should match
// service_traits::DataType< ::trajecgenerator::boolRequest >
template<>
struct DataType< ::trajecgenerator::boolRequestResponse>
{
  static const char* value()
  {
    return DataType< ::trajecgenerator::boolRequest >::value();
  }
  static const char* value(const ::trajecgenerator::boolRequestResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // TRAJECGENERATOR_MESSAGE_BOOLREQUEST_H
