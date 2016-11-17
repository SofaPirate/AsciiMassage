#ifndef BufferedMassenger_h
#define BufferedMassenger_h

#include "Massenger.h"

class BufferedMassenger : public Massenger
{
public:
  /// Constructor.
  BufferedMassenger(Stream* stream=&Serial)
    : Massenger(stream),
    _messageSize(0),
    _needsToFlush(false) {}

  // Virtual destructor.
  virtual ~BufferedMassenger() {}

  /**
   * Flushes previous message and reads serial port. Returns true if new
   * message has arrived.
   */
  virtual bool receive()
  {
    // Flush (if needed).
    if ( _needsToFlush)
      flush();

    // Read stream.
    while (_stream->available())
    {
      // Process single byte.
      // NOTE: If _process() returns true it means that a new message is available.
      if (_process(_stream->read()))
      {
        _needsToFlush = true;
        return true;
      }
    }

    return false;
  }

  /// Flushes current message in buffer (if any).
  virtual void flush() {
  	_needsToFlush = false;
    _messageSize = 0;
  }

  /// If current message matches "address", calls function "callback" and returns true.
  virtual bool dispatch(const char* address, callbackFunction callback)
  {
    // Verity if address matches beginning of buffer.
    bool matches = (strcmp(_buffer, address) == 0);
    if (matches) callback();
    return matches;
  }

protected:
  /**
   * Processes a single value read from the serial stream. Returns true iff a new message
   * is available.
   */
  virtual bool _process(int serialByte) = 0;

  // Writes single byte to buffer (returns false if buffer is full and cannot be written to).
  bool _write(uint8_t value)
  {
    if (_messageSize >= MASSENGER_BUFFERSIZE)
      return false;
    _buffer[_messageSize++] = value;
    return true;
  }

protected:
  // Current size of message in buffer.
  uint8_t _messageSize;

  // Index in the buffer of next argument to read.
  //uint8_t _nextIndex;

  // Buffer that holds the data for current message.
  char _buffer[MASSENGER_BUFFERSIZE];

  // Keeps track of whether we need to flush on the next call to receive().
  bool _needsToFlush;
};

#endif
