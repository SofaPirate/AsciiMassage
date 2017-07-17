#ifndef MassageParser_h
#define MassageParser_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef MASSAGE_PARSER_BUFFERSIZE
/**
 * Max. size of message buffer. Can be predefined before including MassageParser.h
 * to increase/decrease size.
 */
#define MASSAGE_PARSER_BUFFERSIZE 256
#endif


/// Main MassageParser abstract class.
class MassageParser
{
public:
  typedef void (*callbackFunction)(void);

  /// Constructor.
  MassageParser( ) {  
    flush(); 
  }

  // Virtual destructor.
  virtual ~MassageParser() {}

  /**
   * Flushes previous message and reads serial port. Returns true if new
   * message has arrived.
   */
   void parse(int data, callbackFunction callback)
  {

    if ( _needToFlush) {
      
      flush();
    }
    // Read stream.
    

    if ( _decode(data) ) {
        _needToFlush = true;
        
        callback();
        
    }
    
  }

  void parseStream(Stream* stream, callbackFunction callback)
  {
  	  while ( stream->available() ) {
    // PARSE INPUT AND EXECUTRE massageReceived IF A COMPLETE MASSAGE IS RECEIVED 
    		parse( stream->read() , callback );
  	  }
  }

    /// Flushes current message in buffer (if any).
  void flush() {
    _needToFlush = false;
    _messageSize = 0;
    _nextIndex = 0;
  }


  /// If current message matches "address", calls function "callback" and returns true.
  //virtual bool dispatch(const char* address, callbackFunction callback) = 0;

   /// Return true if current message matches "address"
  bool fullMatch(const char* address)
  {
    // Verity if address matches beginning of buffer.
    bool matches = (strcmp(_buffer, address) == 0);
    return matches;
  }

  /// Reads next byte.
  virtual int8_t nextByte(bool* error=0) = 0;

  /// Reads next int.
  virtual int16_t nextInt(bool* error=0) = 0;

  /// Reads next long.
  virtual int32_t nextLong(bool* error=0) = 0;

  /// Reads next float.
  virtual float nextFloat(bool* error=0) = 0;

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
      
     if (_messageSize >= MASSAGE_PARSER_BUFFERSIZE) return false;

      _buffer[_messageSize++] = value;
      
      return true;
    }

      // Current size of message in buffer.
  size_t _messageSize;

  // Index in the buffer of next argument to read.
  uint8_t _nextIndex;

  bool _needToFlush;

  // Buffer that holds the data for current message to be sent.
  char _buffer[MASSAGE_PARSER_BUFFERSIZE];

};






#endif
