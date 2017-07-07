#ifndef Massage_h
#define Massage_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef MASSAGE_BUFFERSIZE
/**
 * Max. size of message buffer. Can be predefined before including Massage.h
 * to increase/decrease size.
 */
#define MASSAGE_BUFFERSIZE 256
#endif


/// Main Massage abstract class.
class Massage
{
public:
  typedef void (*callbackFunction)(void);

  /// Constructor.
  Massage() {}

  // Virtual destructor.
  virtual ~Massage() {}

  /**
   * Flushes previous message and reads serial port. Returns true if new
   * message has arrived.
   */
  virtual void parse(int data,callbackFunction callback) = 0;


  /// If current message matches "address", calls function "callback" and returns true.
  //virtual bool dispatch(const char* address, callbackFunction callback) = 0;

   /// Return true if current message matches "address"
  virtual bool fullMatch(const char* address) = 0;


  /// Reads next byte.
  virtual int8_t nextByte(bool* error=0) = 0;

  /// Reads next int.
  virtual int16_t nextInt(bool* error=0) = 0;

  /// Reads next long.
  virtual int32_t nextLong(bool* error=0) = 0;

  /// Reads next float.
  virtual float nextFloat(bool* error=0) = 0;

  /// Begins the sending of a message.
  virtual void beginPacket(const char* address) = 0;

  /// Adds a byte.
  virtual void addByte(uint8_t value) = 0;

  /// Adds an int.
  virtual void addInt(int16_t value) = 0;

  /// Adds a long.
  virtual void addLong(int32_t value) = 0;

  /// Adds a float.
  virtual void addFloat(float value) = 0;

  /// Ends the sending of a message.
  virtual void endPacket() = 0;

  /// Sends message with no arguments.
  virtual void sendMassage(const char *address)
  {
    beginPacket(address);
    endPacket();
  }

  /// Sends message with single byte value.
  virtual void sendMassageByte(const char *address, uint8_t value)
  {
    beginPacket(address);
    addByte(value);
    endPacket();
  }

  /// Sends message with single int value.
  virtual void sendMassageInt(const char *address, int16_t value)
  {
    beginPacket(address);
    addInt(value);
    endPacket();
  }

  /// Sends message with single long value.
  virtual void sendMassageLong(const char *address, int32_t value)
  {
    beginPacket(address);
    addLong(value);
    endPacket();
  }

  /// Sends message with single float value.
  virtual void sendMassageFloat(const char *address, float value)
  {
    beginPacket(address);
    addFloat(value);
    endPacket();
  }

};




#endif
