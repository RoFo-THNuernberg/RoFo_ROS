// Generated by gencpp from file trajecgenerator/plotTrajecXoY.msg
// DO NOT EDIT!


#ifndef TRAJECGENERATOR_MESSAGE_PLOTTRAJECXOY_H
#define TRAJECGENERATOR_MESSAGE_PLOTTRAJECXOY_H

#include <ros/service_traits.h>


#include <trajecgenerator/plotTrajecXoYRequest.h>
#include <trajecgenerator/plotTrajecXoYResponse.h>


namespace trajecgenerator
{

struct plotTrajecXoY
{

typedef plotTrajecXoYRequest Request;
typedef plotTrajecXoYResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct plotTrajecXoY
} // namespace trajecgenerator


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::trajecgenerator::plotTrajecXoY > {
  static const char* value()
  {
    return "af80c98d097b90c478c238e3c9f71a07";
  }

  static const char* value(const ::trajecgenerator::plotTrajecXoY&) { return value(); }
};

template<>
struct DataType< ::trajecgenerator::plotTrajecXoY > {
  static const char* value()
  {
    return "trajecgenerator/plotTrajecXoY";
  }

  static const char* value(const ::trajecgenerator::plotTrajecXoY&) { return value(); }
};


// service_traits::MD5Sum< ::trajecgenerator::plotTrajecXoYRequest> should match
// service_traits::MD5Sum< ::trajecgenerator::plotTrajecXoY >
template<>
struct MD5Sum< ::trajecgenerator::plotTrajecXoYRequest>
{
  static const char* value()
  {
    return MD5Sum< ::trajecgenerator::plotTrajecXoY >::value();
  }
  static const char* value(const ::trajecgenerator::plotTrajecXoYRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::trajecgenerator::plotTrajecXoYRequest> should match
// service_traits::DataType< ::trajecgenerator::plotTrajecXoY >
template<>
struct DataType< ::trajecgenerator::plotTrajecXoYRequest>
{
  static const char* value()
  {
    return DataType< ::trajecgenerator::plotTrajecXoY >::value();
  }
  static const char* value(const ::trajecgenerator::plotTrajecXoYRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::trajecgenerator::plotTrajecXoYResponse> should match
// service_traits::MD5Sum< ::trajecgenerator::plotTrajecXoY >
template<>
struct MD5Sum< ::trajecgenerator::plotTrajecXoYResponse>
{
  static const char* value()
  {
    return MD5Sum< ::trajecgenerator::plotTrajecXoY >::value();
  }
  static const char* value(const ::trajecgenerator::plotTrajecXoYResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::trajecgenerator::plotTrajecXoYResponse> should match
// service_traits::DataType< ::trajecgenerator::plotTrajecXoY >
template<>
struct DataType< ::trajecgenerator::plotTrajecXoYResponse>
{
  static const char* value()
  {
    return DataType< ::trajecgenerator::plotTrajecXoY >::value();
  }
  static const char* value(const ::trajecgenerator::plotTrajecXoYResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // TRAJECGENERATOR_MESSAGE_PLOTTRAJECXOY_H
