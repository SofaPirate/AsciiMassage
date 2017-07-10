#ifndef MassageEncoder_h
#define MassageEncoder_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef MASSAGE_ENCODER_BUFFERSIZE
/**
 * Max. size of message buffer. Can be predefined before including MassageEncoder.h
 * to increase/decrease size.
 */
#define MASSAGE_ENCODER_BUFFERSIZE 256
#endif


/// Main MassageEncoder abstract class.
class MassageEncoder
{
public:
  typedef void (*callbackFunction)(void);

  /// Constructor.
  MassageEncoder() {
    flush();
  }

    /// Flushes current message in buffer (if any).
  void flush() {
    _needToFlush = false;
    _messageSize = 0;
    _nextIndex = 0;
  }

  // Virtual destructor.
  virtual ~MassageEncoder() {}

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
  virtual void sendEmpty(const char *address)
  {
    beginPacket(address);
    endPacket();
  }

  /// Sends message with single byte value.
  virtual void sendOneByte(const char *address, uint8_t value)
  {
    beginPacket(address);
    addByte(value);
    endPacket();
  }

  /// Sends message with single int value.
  virtual void sendOneInt(const char *address, int16_t value)
  {
    beginPacket(address);
    addInt(value);
    endPacket();
  }

  /// Sends message with single long value.
  virtual void sendOneLong(const char *address, int32_t value)
  {
    beginPacket(address);
    addLong(value);
    endPacket();
  }

  /// Sends message with single float value.
  virtual void sendOneFloat(const char *address, float value)
  {
    beginPacket(address);
    addFloat(value);
    endPacket();
  }

  size_t size() {
    return _messageSize;
  }

char* buffer  () { 
  return _buffer; 
}

  protected:
     // Writes single byte to buffer (returns false if buffer is full and cannot be written to).
    bool _store(uint8_t value)
    {
      
     if (_messageSize >= MASSAGE_ENCODER_BUFFERSIZE)
        return false;
      _buffer[_messageSize++] = value;
      
      return true;
    }

      // Current size of message in buffer.
    uint8_t _messageSize;

    // Index in the buffer of next argument to read.
    uint8_t _nextIndex;

    bool _needToFlush;


  // Buffer that holds the data for current message to be sent.
  char _buffer[MASSAGE_ENCODER_BUFFERSIZE];


};




#endif
