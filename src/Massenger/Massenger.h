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
  virtual bool receive() = 0;

  /// Flushes current message in buffer (if any).
  virtual void flush() = 0;

  /// If current message matches "address", calls function "callback" and returns true.
  virtual bool dispatch(const char* address, callbackFunction callback) = 0;

  /// Reads next byte.
  virtual int8_t nextByte(bool* error=0) = 0;

  /// Reads next int.
  virtual int16_t nextInt(bool* error=0) = 0;

  /// Reads next long.
  virtual int32_t nextLong(bool* error=0) = 0;

  /// Reads next float.
  virtual float nextFloat(bool* error=0) = 0;

  /// Begins the sending of a message.
  virtual void sendBegin(const char* address) = 0;

  /// Sends a byte.
  virtual void sendByte(uint8_t value) = 0;

  /// Sends an int.
  virtual void sendInt(int16_t value) = 0;

  /// Sends a long.
  virtual void sendLong(int32_t value) = 0;

  /// Sends a float.
  virtual void sendFloat(float value) = 0;

  /// Ends the sending of a message.
  virtual void sendEnd() = 0;

  /// Sends message with no arguments.
  virtual void sendMessage(const char *address)
  {
    sendBegin(address);
    sendEnd();
  }

  /// Sends message with single byte value.
  virtual void sendMessageByte(const char *address, uint8_t value)
  {
    sendBegin(address);
    sendByte(value);
    sendEnd();
  }

  /// Sends message with single int value.
  virtual void sendMessageInt(const char *address, int16_t value)
  {
    sendBegin(address);
    sendInt(value);
    sendEnd();
  }

  /// Sends message with single long value.
  virtual void sendMessageLong(const char *address, int32_t value)
  {
    sendBegin(address);
    sendLong(value);
    sendEnd();
  }

  /// Sends message with single float value.
  virtual void sendMessageFloat(const char *address, float value)
  {
    sendBegin(address);
    sendFloat(value);
    sendEnd();
  }

protected:
  // Pointer to the stream read by this object.
  Stream* _stream;
};




#endif
