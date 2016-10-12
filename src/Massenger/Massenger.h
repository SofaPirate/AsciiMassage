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
  Massenger(Stream* stream=&Serial);

  // Virtual destructor.
  virtual ~Massenger() {}

  /**
   * Flushes previous message and reads serial port. Returns true if new
   * message has arrived.
   */
  virtual bool receive();

  /// Flushes current message in buffer (if any).
  virtual void flush();

  /// If current message matches "address", calls function "callback" and returns true.
  virtual bool dispatch(const char* address, callbackFunction callback);

  /// Reads next byte.
  virtual int8_t nextByte(bool* error=0) = 0;

  /// Reads next int.
  virtual int16_t nextInt(bool* error=0) = 0;

  /// Reads next long.
  virtual int32_t nextLong(bool* error=0) = 0;

  /// Reads next float.
  virtual float nextFloat(bool* error=0) = 0;

  /// Reads next double.
  virtual double nextDouble(bool* error=0) = 0;

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

  /// Sends a double.
  virtual void sendDouble(double value) = 0;

  /// Ends the sending of a message.
  virtual void sendEnd() = 0;

  /// Sends message with no arguments.
  virtual void send(const char *address);

  /// Sends message with single byte value.
  virtual void sendByte(const char *address, uint8_t value);

  /// Sends message with single int value.
  virtual void sendInt(const char *address, int16_t value);

  /// Sends message with single long value.
  virtual void sendLong(const char *address, int32_t value);

  /// Sends message with single float value.
  virtual void sendFloat(const char *address, float value);

  /// Sends message with single double value.
  virtual void sendDouble(const char *address, double value);

protected:
  /// Processes a single value read from the serial stream.
  virtual bool _process(int serialByte) = 0;

  // Writes single byte to buffer (returns false if buffer is full and cannot be written to).
  bool _write(uint8_t value);

  // Pointer to the stream read by this object.
  Stream* _stream;

  // Current size of message in buffer.
  uint8_t _messageSize;

  // Index in the buffer of next argument to read.
  //uint8_t _nextIndex;

  // Buffer that holds the data for current message.
  char _buffer[MASSENGER_BUFFERSIZE];
};




#endif
