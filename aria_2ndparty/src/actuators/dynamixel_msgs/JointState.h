/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /Users/ssb/workspace/src/dynamixel_motor/dynamixel_msgs/msg/JointState.msg
 *
 */


#ifndef DYNAMIXEL_MSGS_MESSAGE_JOINTSTATE_H
#define DYNAMIXEL_MSGS_MESSAGE_JOINTSTATE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace dynamixel_msgs
{
template <class ContainerAllocator>
struct JointState_
{
  typedef JointState_<ContainerAllocator> Type;

  JointState_()
    : header()
    , name()
    , motor_ids()
    , motor_temps()
    , goal_pos(0.0)
    , current_pos(0.0)
    , error(0.0)
    , velocity(0.0)
    , load(0.0)
    , current(0.0)
    , is_moving(false)  {
    }
  JointState_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , name(_alloc)
    , motor_ids(_alloc)
    , motor_temps(_alloc)
    , goal_pos(0.0)
    , current_pos(0.0)
    , error(0.0)
    , velocity(0.0)
    , load(0.0)
    , current(0.0)
    , is_moving(false)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _name_type;
  _name_type name;

   typedef std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  _motor_ids_type;
  _motor_ids_type motor_ids;

   typedef std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  _motor_temps_type;
  _motor_temps_type motor_temps;

   typedef double _goal_pos_type;
  _goal_pos_type goal_pos;

   typedef double _current_pos_type;
  _current_pos_type current_pos;

   typedef double _error_type;
  _error_type error;

   typedef double _velocity_type;
  _velocity_type velocity;

   typedef double _load_type;
  _load_type load;

   typedef double _current_type;
  _current_type current;

   typedef uint8_t _is_moving_type;
  _is_moving_type is_moving;




  typedef boost::shared_ptr< ::dynamixel_msgs::JointState_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dynamixel_msgs::JointState_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct JointState_

typedef ::dynamixel_msgs::JointState_<std::allocator<void> > JointState;

typedef boost::shared_ptr< ::dynamixel_msgs::JointState > JointStatePtr;
typedef boost::shared_ptr< ::dynamixel_msgs::JointState const> JointStateConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dynamixel_msgs::JointState_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dynamixel_msgs::JointState_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace dynamixel_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'dynamixel_msgs': ['/Users/ssb/workspace/src/dynamixel_motor/dynamixel_msgs/msg'], 'std_msgs': ['/Users/ssb/ros_catkin_ws/install_isolated/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::dynamixel_msgs::JointState_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dynamixel_msgs::JointState_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamixel_msgs::JointState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamixel_msgs::JointState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamixel_msgs::JointState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamixel_msgs::JointState_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dynamixel_msgs::JointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6c2e77a51e2e5181e6677df1c3c0817e";
  }

  static const char* value(const ::dynamixel_msgs::JointState_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6c2e77a51e2e5181ULL;
  static const uint64_t static_value2 = 0xe6677df1c3c0817eULL;
};

template<class ContainerAllocator>
struct DataType< ::dynamixel_msgs::JointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dynamixel_msgs/JointState";
  }

  static const char* value(const ::dynamixel_msgs::JointState_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dynamixel_msgs::JointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
string name         # joint name\n\
int32[] motor_ids   # motor ids controlling this joint\n\
int32[] motor_temps # motor temperatures, same order as motor_ids\n\
\n\
float64 goal_pos    # commanded position (in radians)\n\
float64 current_pos # current joint position (in radians)\n\
float64 error       # error between commanded and current positions (in radians)\n\
float64 velocity    # current joint speed (in radians per second)\n\
float64 load        # current load\n\
float64 current     # measured current (amps)\n\
bool is_moving      # is joint currently in motion\n\
\n\
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
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
";
  }

  static const char* value(const ::dynamixel_msgs::JointState_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dynamixel_msgs::JointState_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.name);
      stream.next(m.motor_ids);
      stream.next(m.motor_temps);
      stream.next(m.goal_pos);
      stream.next(m.current_pos);
      stream.next(m.error);
      stream.next(m.velocity);
      stream.next(m.load);
      stream.next(m.current);
      stream.next(m.is_moving);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct JointState_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dynamixel_msgs::JointState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dynamixel_msgs::JointState_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name);
    s << indent << "motor_ids[]" << std::endl;
    for (size_t i = 0; i < v.motor_ids.size(); ++i)
    {
      s << indent << "  motor_ids[" << i << "]: ";
      Printer<int32_t>::stream(s, indent + "  ", v.motor_ids[i]);
    }
    s << indent << "motor_temps[]" << std::endl;
    for (size_t i = 0; i < v.motor_temps.size(); ++i)
    {
      s << indent << "  motor_temps[" << i << "]: ";
      Printer<int32_t>::stream(s, indent + "  ", v.motor_temps[i]);
    }
    s << indent << "goal_pos: ";
    Printer<double>::stream(s, indent + "  ", v.goal_pos);
    s << indent << "current_pos: ";
    Printer<double>::stream(s, indent + "  ", v.current_pos);
    s << indent << "error: ";
    Printer<double>::stream(s, indent + "  ", v.error);
    s << indent << "velocity: ";
    Printer<double>::stream(s, indent + "  ", v.velocity);
    s << indent << "load: ";
    Printer<double>::stream(s, indent + "  ", v.load);
    s << indent << "current: ";
    Printer<double>::stream(s, indent + "  ", v.current);
    s << indent << "is_moving: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.is_moving);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DYNAMIXEL_MSGS_MESSAGE_JOINTSTATE_H
