#ifndef BufferedMassenger_h
#define BufferedMassenger_h

#include "Massenger.h"

class BufferedMassenger : public Massenger
{
public:
  /// Constructor.
  BufferedMassenger()  {
    flushRx();
  }

  // Virtual destructor.
  virtual ~BufferedMassenger() {}

  /**
   * Flushes previous message and reads serial port. Returns true if new
   * message has arrived.
   */
  virtual void parse(int data, callbackFunction callback)
  {

    if ( _needToFlushRx) {
      
      flushRx();
    }
    // Read stream.
    

    if ( _decode(data) ) {
        _needToFlushRx = true;
        callback();
        //return true;
    }
    
    //return false;
  }

  /// Flushes current message in buffer (if any).
  void flushRx() {
    _needToFlushRx = false;
    _messageSizeRx = 0;
    _nextIndexRx = 0;
  }

    /// Flushes current message in buffer (if any).
  void flushTx() {

    size = _messageSizeTx = 0;


  }


  virtual bool dispatch(const char* address, callbackFunction callback)
  {
    // Verity if address matches beginning of buffer.
    bool matches = (strcmp(rxBuffer, address) == 0);
    if (matches) callback();
    return matches;
  }

    virtual bool fullMatch(const char* address)
  {
    // Verity if address matches beginning of buffer.
    bool matches = (strcmp(rxBuffer, address) == 0);
    return matches;
  }

protected:
  /// Decode a single value read from the serial stream.
  // True if an end is found.
  virtual bool _decode(int serialByte) = 0;

  // Writes single byte to buffer (returns false if buffer is full and cannot be written to).
  bool _storeRx(uint8_t value)
  {
    if (_messageSizeRx >= MASSENGER_BUFFERSIZE)
      return false;
    rxBuffer[_messageSizeRx++] = value;
    return true;
  }
/*
    /// Processes a single value read from the serial stream.
  virtual bool _processTx(int serialByte) = 0;
  */
  // Writes single byte to buffer (returns false if buffer is full and cannot be written to).
  bool _storeTx(uint8_t value)
  {
    
   if (_messageSizeTx >= MASSENGER_BUFFERSIZE)
      return false;
    buffer[_messageSizeTx++] = value;
    size = _messageSizeTx;
    return true;
  }


protected:
  // Current size of message in buffer.
  uint8_t _messageSizeRx;

  // Index in the buffer of next argument to read.
  uint8_t _nextIndexRx;

  bool _needToFlushRx;

    // Current size of message in buffer.
  uint8_t _messageSizeTx;

        // Buffer that holds the data for current message.
  char rxBuffer[MASSENGER_BUFFERSIZE];

public:
  
  size_t size;

  // Buffer that holds the data for current message to be sent.
  char buffer[MASSENGER_BUFFERSIZE];
};

#endif
