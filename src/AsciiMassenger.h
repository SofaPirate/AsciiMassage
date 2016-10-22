#ifndef AsciiMassenger_h
#define AsciiMassenger_h

#include "Massenger/Massenger.h"

/// Main AsciiMassenger class.
class AsciiMassenger : public Massenger
{
public:
  /// Constructor.
  AsciiMassenger(Stream* stream=&Serial);

  /// Flushes current message in buffer (if any).
  virtual void flush();

  /// Reads next byte.
  virtual int8_t nextByte(bool* error=0);

  /// Reads next int.
  virtual int16_t nextInt(bool* error=0);

  /// Reads next long.
  virtual int32_t nextLong(bool* error=0);

  /// Reads next float.
  virtual float nextFloat(bool* error=0);

  /// Begins the sending of a message.
  virtual void sendBegin(const char* address);

  /// Sends a byte.
  virtual void sendByte(uint8_t value);

  /// Sends an int.
  virtual void sendInt(int16_t value);

  /// Sends a long.
  virtual void sendLong(int32_t value);

  /// Sends a float.
  virtual void sendFloat(float value);

  /// Ends the sending of a message.
  virtual void sendEnd();

  /// Returns true if new message has arrived.
  virtual bool receive();

  /// If current message matches "address", calls function "callback" and returns true.
  virtual bool dispatch(const char* address, callbackFunction callback);

protected:
  /// Processes a single value read from the serial stream.
  virtual bool _process(int serialByte);

    // Current size of message in buffer.
  uint8_t _messageSize;

  // Index in the buffer of next argument to read.
  //uint8_t _nextIndex;

  // Buffer that holds the data for current message.
  char _buffer[MASSENGER_BUFFERSIZE];
  
  // Flag to indicate the need to flush
  bool _needToFlush;

private:
  // Moves nextIndex to the next token.
  bool _updateNextIndex();

  // Returns true iff it is still possible to call next*().
  bool _hasNext() const;

  bool _write(uint8_t value);

  // Helper function to read next value.
  void _nextBlock(bool isInteger, uint8_t* value, size_t n, bool* error);

  // Index in the buffer of next argument to read.
  uint8_t _nextIndex;
};




#endif
