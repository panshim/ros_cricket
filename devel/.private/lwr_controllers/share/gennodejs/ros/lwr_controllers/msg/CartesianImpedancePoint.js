// Auto-generated. Do not edit!

// (in-package lwr_controllers.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Stiffness = require('./Stiffness.js');
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class CartesianImpedancePoint {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.x_FRI = null;
      this.k_FRI = null;
      this.d_FRI = null;
      this.f_FRI = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('x_FRI')) {
        this.x_FRI = initObj.x_FRI
      }
      else {
        this.x_FRI = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('k_FRI')) {
        this.k_FRI = initObj.k_FRI
      }
      else {
        this.k_FRI = new Stiffness();
      }
      if (initObj.hasOwnProperty('d_FRI')) {
        this.d_FRI = initObj.d_FRI
      }
      else {
        this.d_FRI = new Stiffness();
      }
      if (initObj.hasOwnProperty('f_FRI')) {
        this.f_FRI = initObj.f_FRI
      }
      else {
        this.f_FRI = new geometry_msgs.msg.Wrench();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CartesianImpedancePoint
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [x_FRI]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.x_FRI, buffer, bufferOffset);
    // Serialize message field [k_FRI]
    bufferOffset = Stiffness.serialize(obj.k_FRI, buffer, bufferOffset);
    // Serialize message field [d_FRI]
    bufferOffset = Stiffness.serialize(obj.d_FRI, buffer, bufferOffset);
    // Serialize message field [f_FRI]
    bufferOffset = geometry_msgs.msg.Wrench.serialize(obj.f_FRI, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CartesianImpedancePoint
    let len;
    let data = new CartesianImpedancePoint(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [x_FRI]
    data.x_FRI = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [k_FRI]
    data.k_FRI = Stiffness.deserialize(buffer, bufferOffset);
    // Deserialize message field [d_FRI]
    data.d_FRI = Stiffness.deserialize(buffer, bufferOffset);
    // Deserialize message field [f_FRI]
    data.f_FRI = geometry_msgs.msg.Wrench.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 200;
  }

  static datatype() {
    // Returns string type for a message object
    return 'lwr_controllers/CartesianImpedancePoint';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '71b8c728a99ddb73ba603776d4733a5f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    # 1. If frame_id in header is NOT EMPTY, then x_FRI is considered to be the pose w.r.t. that frame, so the increment w.r.t. the current tip pose will be computed internally (in the teach pendant is equivalent to select the Cartesian increments to be in the WORLD frame) 
    # 2. If frame_id in header is EMPTY, then x_FRI is considered to be the pose w.r.t. to the current tip pose (in the teach pendant is equivalent to select the Cartesian increments to be in the TOOL frame)
    # The increment (or offset) is x_FRI
    geometry_msgs/Pose x_FRI
    # The stiffness, damping and wrench are expressed in the current tip frame readed in the HWiface
    lwr_controllers/Stiffness k_FRI
    lwr_controllers/Stiffness d_FRI
    geometry_msgs/Wrench f_FRI
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: geometry_msgs/Pose
    # A representation of pose in free space, composed of position and orientation. 
    Point position
    Quaternion orientation
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: geometry_msgs/Quaternion
    # This represents an orientation in free space in quaternion form.
    
    float64 x
    float64 y
    float64 z
    float64 w
    
    ================================================================================
    MSG: lwr_controllers/Stiffness
    # This represents a diagonal Cartesian stiffness
    # It is motivated by the KDL class: http://people.mech.kuleuven.be/~rsmits/kdl/api/html/classKDL_1_1Stiffness.html
    # The conversion would be straight-forward, however, a generic 6D stiffness matrix would be desirable
    
    float64 x
    float64 y
    float64 z
    float64 rx
    float64 ry
    float64 rz
    ================================================================================
    MSG: geometry_msgs/Wrench
    # This represents force in free space, separated into
    # its linear and angular parts.
    Vector3  force
    Vector3  torque
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CartesianImpedancePoint(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.x_FRI !== undefined) {
      resolved.x_FRI = geometry_msgs.msg.Pose.Resolve(msg.x_FRI)
    }
    else {
      resolved.x_FRI = new geometry_msgs.msg.Pose()
    }

    if (msg.k_FRI !== undefined) {
      resolved.k_FRI = Stiffness.Resolve(msg.k_FRI)
    }
    else {
      resolved.k_FRI = new Stiffness()
    }

    if (msg.d_FRI !== undefined) {
      resolved.d_FRI = Stiffness.Resolve(msg.d_FRI)
    }
    else {
      resolved.d_FRI = new Stiffness()
    }

    if (msg.f_FRI !== undefined) {
      resolved.f_FRI = geometry_msgs.msg.Wrench.Resolve(msg.f_FRI)
    }
    else {
      resolved.f_FRI = new geometry_msgs.msg.Wrench()
    }

    return resolved;
    }
};

module.exports = CartesianImpedancePoint;
