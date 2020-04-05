// Auto-generated. Do not edit!

// (in-package lwr_controllers.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class MultiPriorityTask {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.links = null;
      this.tasks = null;
    }
    else {
      if (initObj.hasOwnProperty('links')) {
        this.links = initObj.links
      }
      else {
        this.links = [];
      }
      if (initObj.hasOwnProperty('tasks')) {
        this.tasks = initObj.tasks
      }
      else {
        this.tasks = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MultiPriorityTask
    // Serialize message field [links]
    bufferOffset = _arraySerializer.int32(obj.links, buffer, bufferOffset, null);
    // Serialize message field [tasks]
    bufferOffset = _arraySerializer.float64(obj.tasks, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MultiPriorityTask
    let len;
    let data = new MultiPriorityTask(null);
    // Deserialize message field [links]
    data.links = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [tasks]
    data.tasks = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.links.length;
    length += 8 * object.tasks.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'lwr_controllers/MultiPriorityTask';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '42e011fbf13e33d6ed6e65ac7a0bdf63';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32[] links
    float64[] tasks
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MultiPriorityTask(null);
    if (msg.links !== undefined) {
      resolved.links = msg.links;
    }
    else {
      resolved.links = []
    }

    if (msg.tasks !== undefined) {
      resolved.tasks = msg.tasks;
    }
    else {
      resolved.tasks = []
    }

    return resolved;
    }
};

module.exports = MultiPriorityTask;
