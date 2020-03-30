// Auto-generated. Do not edit!

// (in-package lwr_controllers.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let CartesianImpedancePoint = require('../msg/CartesianImpedancePoint.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetCartesianImpedanceCommandRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.command = null;
    }
    else {
      if (initObj.hasOwnProperty('command')) {
        this.command = initObj.command
      }
      else {
        this.command = new CartesianImpedancePoint();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetCartesianImpedanceCommandRequest
    // Serialize message field [command]
    bufferOffset = CartesianImpedancePoint.serialize(obj.command, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetCartesianImpedanceCommandRequest
    let len;
    let data = new SetCartesianImpedanceCommandRequest(null);
    // Deserialize message field [command]
    data.command = CartesianImpedancePoint.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += CartesianImpedancePoint.getMessageSize(object.command);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'lwr_controllers/SetCartesianImpedanceCommandRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cc36264319f44d204c2ace0744aa21ee';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    lwr_controllers/CartesianImpedancePoint command
    
    ================================================================================
    MSG: lwr_controllers/CartesianImpedancePoint
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
    const resolved = new SetCartesianImpedanceCommandRequest(null);
    if (msg.command !== undefined) {
      resolved.command = CartesianImpedancePoint.Resolve(msg.command)
    }
    else {
      resolved.command = new CartesianImpedancePoint()
    }

    return resolved;
    }
};

class SetCartesianImpedanceCommandResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetCartesianImpedanceCommandResponse
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetCartesianImpedanceCommandResponse
    let len;
    let data = new SetCartesianImpedanceCommandResponse(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'lwr_controllers/SetCartesianImpedanceCommandResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetCartesianImpedanceCommandResponse(null);
    return resolved;
    }
};

module.exports = {
  Request: SetCartesianImpedanceCommandRequest,
  Response: SetCartesianImpedanceCommandResponse,
  md5sum() { return 'cc36264319f44d204c2ace0744aa21ee'; },
  datatype() { return 'lwr_controllers/SetCartesianImpedanceCommand'; }
};
