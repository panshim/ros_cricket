// Generated by gencpp from file lwr_controllers/ArmState.msg
// DO NOT EDIT!


#ifndef LWR_CONTROLLERS_MESSAGE_ARMSTATE_H
#define LWR_CONTROLLERS_MESSAGE_ARMSTATE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Wrench.h>
#include <geometry_msgs/Wrench.h>

namespace lwr_controllers
{
template <class ContainerAllocator>
struct ArmState_
{
  typedef ArmState_<ContainerAllocator> Type;

  ArmState_()
    : header()
    , joint_name()
    , est_ext_torques()
    , est_ee_wrench()
    , est_ee_wrench_base()  {
    }
  ArmState_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , joint_name(_alloc)
    , est_ext_torques(_alloc)
    , est_ee_wrench(_alloc)
    , est_ee_wrench_base(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _joint_name_type;
  _joint_name_type joint_name;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _est_ext_torques_type;
  _est_ext_torques_type est_ext_torques;

   typedef  ::geometry_msgs::Wrench_<ContainerAllocator>  _est_ee_wrench_type;
  _est_ee_wrench_type est_ee_wrench;

   typedef  ::geometry_msgs::Wrench_<ContainerAllocator>  _est_ee_wrench_base_type;
  _est_ee_wrench_base_type est_ee_wrench_base;





  typedef boost::shared_ptr< ::lwr_controllers::ArmState_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::lwr_controllers::ArmState_<ContainerAllocator> const> ConstPtr;

}; // struct ArmState_

typedef ::lwr_controllers::ArmState_<std::allocator<void> > ArmState;

typedef boost::shared_ptr< ::lwr_controllers::ArmState > ArmStatePtr;
typedef boost::shared_ptr< ::lwr_controllers::ArmState const> ArmStateConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::lwr_controllers::ArmState_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::lwr_controllers::ArmState_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace lwr_controllers

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'lwr_controllers': ['/home/shimin/ROS_Prgm_Prj/src/kuka-lwr/lwr_controllers/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::lwr_controllers::ArmState_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::lwr_controllers::ArmState_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lwr_controllers::ArmState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lwr_controllers::ArmState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lwr_controllers::ArmState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lwr_controllers::ArmState_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::lwr_controllers::ArmState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1ec4005eded14deb32698c63aa479d03";
  }

  static const char* value(const ::lwr_controllers::ArmState_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1ec4005eded14debULL;
  static const uint64_t static_value2 = 0x32698c63aa479d03ULL;
};

template<class ContainerAllocator>
struct DataType< ::lwr_controllers::ArmState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "lwr_controllers/ArmState";
  }

  static const char* value(const ::lwr_controllers::ArmState_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::lwr_controllers::ArmState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
string[] joint_name\n\
float32[] est_ext_torques\n\
geometry_msgs/Wrench est_ee_wrench\n\
geometry_msgs/Wrench est_ee_wrench_base\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Wrench\n\
# This represents force in free space, separated into\n\
# its linear and angular parts.\n\
Vector3  force\n\
Vector3  torque\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
# It is only meant to represent a direction. Therefore, it does not\n\
# make sense to apply a translation to it (e.g., when applying a \n\
# generic rigid transformation to a Vector3, tf2 will only apply the\n\
# rotation). If you want your data to be translatable too, use the\n\
# geometry_msgs/Point message instead.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::lwr_controllers::ArmState_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::lwr_controllers::ArmState_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.joint_name);
      stream.next(m.est_ext_torques);
      stream.next(m.est_ee_wrench);
      stream.next(m.est_ee_wrench_base);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ArmState_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::lwr_controllers::ArmState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::lwr_controllers::ArmState_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "joint_name[]" << std::endl;
    for (size_t i = 0; i < v.joint_name.size(); ++i)
    {
      s << indent << "  joint_name[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.joint_name[i]);
    }
    s << indent << "est_ext_torques[]" << std::endl;
    for (size_t i = 0; i < v.est_ext_torques.size(); ++i)
    {
      s << indent << "  est_ext_torques[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.est_ext_torques[i]);
    }
    s << indent << "est_ee_wrench: ";
    s << std::endl;
    Printer< ::geometry_msgs::Wrench_<ContainerAllocator> >::stream(s, indent + "  ", v.est_ee_wrench);
    s << indent << "est_ee_wrench_base: ";
    s << std::endl;
    Printer< ::geometry_msgs::Wrench_<ContainerAllocator> >::stream(s, indent + "  ", v.est_ee_wrench_base);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LWR_CONTROLLERS_MESSAGE_ARMSTATE_H
