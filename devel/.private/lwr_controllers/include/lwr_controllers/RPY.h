// Generated by gencpp from file lwr_controllers/RPY.msg
// DO NOT EDIT!


#ifndef LWR_CONTROLLERS_MESSAGE_RPY_H
#define LWR_CONTROLLERS_MESSAGE_RPY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace lwr_controllers
{
template <class ContainerAllocator>
struct RPY_
{
  typedef RPY_<ContainerAllocator> Type;

  RPY_()
    : roll(0.0)
    , pitch(0.0)
    , yaw(0.0)  {
    }
  RPY_(const ContainerAllocator& _alloc)
    : roll(0.0)
    , pitch(0.0)
    , yaw(0.0)  {
  (void)_alloc;
    }



   typedef double _roll_type;
  _roll_type roll;

   typedef double _pitch_type;
  _pitch_type pitch;

   typedef double _yaw_type;
  _yaw_type yaw;





  typedef boost::shared_ptr< ::lwr_controllers::RPY_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::lwr_controllers::RPY_<ContainerAllocator> const> ConstPtr;

}; // struct RPY_

typedef ::lwr_controllers::RPY_<std::allocator<void> > RPY;

typedef boost::shared_ptr< ::lwr_controllers::RPY > RPYPtr;
typedef boost::shared_ptr< ::lwr_controllers::RPY const> RPYConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::lwr_controllers::RPY_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::lwr_controllers::RPY_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace lwr_controllers

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'lwr_controllers': ['/home/shimin/ROS_Prgm_Prj/src/kuka-lwr/lwr_controllers/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::lwr_controllers::RPY_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::lwr_controllers::RPY_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lwr_controllers::RPY_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lwr_controllers::RPY_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lwr_controllers::RPY_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lwr_controllers::RPY_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::lwr_controllers::RPY_<ContainerAllocator> >
{
  static const char* value()
  {
    return "eeec8b25a660789a89540dedcb2b06d6";
  }

  static const char* value(const ::lwr_controllers::RPY_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeeec8b25a660789aULL;
  static const uint64_t static_value2 = 0x89540dedcb2b06d6ULL;
};

template<class ContainerAllocator>
struct DataType< ::lwr_controllers::RPY_<ContainerAllocator> >
{
  static const char* value()
  {
    return "lwr_controllers/RPY";
  }

  static const char* value(const ::lwr_controllers::RPY_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::lwr_controllers::RPY_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 roll\n\
float64 pitch\n\
float64 yaw\n\
";
  }

  static const char* value(const ::lwr_controllers::RPY_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::lwr_controllers::RPY_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.roll);
      stream.next(m.pitch);
      stream.next(m.yaw);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RPY_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::lwr_controllers::RPY_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::lwr_controllers::RPY_<ContainerAllocator>& v)
  {
    s << indent << "roll: ";
    Printer<double>::stream(s, indent + "  ", v.roll);
    s << indent << "pitch: ";
    Printer<double>::stream(s, indent + "  ", v.pitch);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LWR_CONTROLLERS_MESSAGE_RPY_H
