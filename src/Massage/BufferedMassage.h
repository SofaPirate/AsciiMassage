#ifndef BufferedMassage_h
#define BufferedMassage_h

#include "Massage.h"

class BufferedMassage : public Massage {
public:
  /// Constructor.
  BufferedMassage()  {
    flush();
  }

  // Virtual destructor.
  virtual ~BufferedMassage() {}

  /**
   * Flushes previous message and reads serial port. Returns true if new
   * message has arrived.
   */
  virtual void parse(int data, callbackFunction callback)
  {

    if ( _needToFlush) {
      
      flush();
    }
    // Read stream.
    

    if ( _decode(data) ) {
        _needToFlush = true;
        callback();
        //return true;
    }
    
    //return false;
  }

  /// Flushes current message in buffer (if any).
  void flush() {
    _needToFlush = false;
    size = _messageSize = 0;
    _nextIndex = 0;
  }




    virtual bool fullMatch(const char* address)
  {
    // Verity if address matches beginning of buffer.
    bool matches = (strcmp(buffer, address) == 0);
    return matches;
  }

protected:
  /// Decode a single value read from the serial stream.
  // True if an end is found.
  virtual bool _decode(int serialByte) = 0;

  
/*
    /// Processes a single value read from the serial stream.
  virtual bool _processTx(int serialByte) = 0;
  */
  // Writes single byte to buffer (returns false if buffer is full and cannot be written to).
  bool _store(uint8_t value)
  {
    
   if (_messageSize >= MASSAGE_BUFFERSIZE)
      return false;
    buffer[_messageSize++] = value;
    size = _messageSize;
    return true;
  }


protected:
  // Current size of message in buffer.
  uint8_t _messageSize;

  // Index in the buffer of next argument to read.
  uint8_t _nextIndex;

  bool _needToFlush;




public:
  
  size_t size;

  // Buffer that holds the data for current message to be sent.
  char buffer[MASSAGE_BUFFERSIZE];
};

#endif
