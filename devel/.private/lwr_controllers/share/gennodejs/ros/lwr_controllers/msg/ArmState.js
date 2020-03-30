// Auto-generated. Do not edit!

// (in-package lwr_controllers.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class ArmState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.joint_name = null;
      this.est_ext_torques = null;
      this.est_ee_wrench = null;
      this.est_ee_wrench_base = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('joint_name')) {
        this.joint_name = initObj.joint_name
      }
      else {
        this.joint_name = [];
      }
      if (initObj.hasOwnProperty('est_ext_torques')) {
        this.est_ext_torques = initObj.est_ext_torques
      }
      else {
        this.est_ext_torques = [];
      }
      if (initObj.hasOwnProperty('est_ee_wrench')) {
        this.est_ee_wrench = initObj.est_ee_wrench
      }
      else {
        this.est_ee_wrench = new geometry_msgs.msg.Wrench();
      }
      if (initObj.hasOwnProperty('est_ee_wrench_base')) {
        this.est_ee_wrench_base = initObj.est_ee_wrench_base
      }
      else {
        this.est_ee_wrench_base = new geometry_msgs.msg.Wrench();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ArmState
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [joint_name]
    bufferOffset = _arraySerializer.string(obj.joint_name, buffer, bufferOffset, null);
    // Serialize message field [est_ext_torques]
    bufferOffset = _arraySerializer.float32(obj.est_ext_torques, buffer, bufferOffset, null);
    // Serialize message field [est_ee_wrench]
    bufferOffset = geometry_msgs.msg.Wrench.serialize(obj.est_ee_wrench, buffer, bufferOffset);
    // Serialize message field [est_ee_wrench_base]
    bufferOffset = geometry_msgs.msg.Wrench.serialize(obj.est_ee_wrench_base, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ArmState
    let len;
    let data = new ArmState(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [joint_name]
    data.joint_name = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [est_ext_torques]
    data.est_ext_torques = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [est_ee_wrench]
    data.est_ee_wrench = geometry_msgs.msg.Wrench.deserialize(buffer, bufferOffset);
    // Deserialize message field [est_ee_wrench_base]
    data.est_ee_wrench_base = geometry_msgs.msg.Wrench.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.joint_name.forEach((val) => {
      length += 4 + val.length;
    });
    length += 4 * object.est_ext_torques.length;
    return length + 104;
  }

  static datatype() {
    // Returns string type for a message object
    return 'lwr_controllers/ArmState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1ec4005eded14deb32698c63aa479d03';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    string[] joint_name
    float32[] est_ext_torques
    geometry_msgs/Wrench est_ee_wrench
    geometry_msgs/Wrench est_ee_wrench_base
    
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
    const resolved = new ArmState(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.joint_name !== undefined) {
      resolved.joint_name = msg.joint_name;
    }
    else {
      resolved.joint_name = []
    }

    if (msg.est_ext_torques !== undefined) {
      resolved.est_ext_torques = msg.est_ext_torques;
    }
    else {
      resolved.est_ext_torques = []
    }

    if (msg.est_ee_wrench !== undefined) {
      resolved.est_ee_wrench = geometry_msgs.msg.Wrench.Resolve(msg.est_ee_wrench)
    }
    else {
      resolved.est_ee_wrench = new geometry_msgs.msg.Wrench()
    }

    if (msg.est_ee_wrench_base !== undefined) {
      resolved.est_ee_wrench_base = geometry_msgs.msg.Wrench.Resolve(msg.est_ee_wrench_base)
    }
    else {
      resolved.est_ee_wrench_base = new geometry_msgs.msg.Wrench()
    }

    return resolved;
    }
};

module.exports = ArmState;
