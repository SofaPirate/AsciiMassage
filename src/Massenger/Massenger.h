#ifndef Massenger_h
#define Massenger_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef MASSENGER_BUFFERSIZE
/**
 * Max. size of message buffer. Can be predefined before including Massenger.h
 * to increase/decrease size.
 */
#define MASSENGER_BUFFERSIZE 128
#endif


/// Main Massenger abstract class.
class Massenger
{
public:
  typedef void (*callbackFunction)(void);

  /// Constructor.
  Massenger(Stream* stream) : _stream(stream) {}

  // Virtual destructor.
  virtual ~Massenger() {}

  /**
   * Flushes previous message and reads serial port. Returns true if new
   * message has arrived.
   */
  virtual bool parsePacket() = 0;


  /// If current message matches "address", calls function "callback" and returns true.
  virtual bool dispatch(const char* address, callbackFunction callback) = 0;

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
  virtual void sendMessage(const char *address)
  {
    beginPacket(address);
    endPacket();
  }

  /// Sends message with single byte value.
  virtual void sendMessageByte(const char *address, uint8_t value)
  {
    beginPacket(address);
    addByte(value);
    endPacket();
  }

  /// Sends message with single int value.
  virtual void sendMessageInt(const char *address, int16_t value)
  {
    beginPacket(address);
    addInt(value);
    endPacket();
  }

  /// Sends message with single long value.
  virtual void sendMessageLong(const char *address, int32_t value)
  {
    beginPacket(address);
    addLong(value);
    endPacket();
  }

  /// Sends message with single float value.
  virtual void sendMessageFloat(const char *address, float value)
  {
    beginPacket(address);
    addFloat(value);
    endPacket();
  }

protected:
  // Pointer to the stream read by this object.
  Stream* _stream;
};




#endif
