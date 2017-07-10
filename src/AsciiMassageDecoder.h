#ifndef AsciiMassageDecoder_h
#define AsciiMassageDecoder_h


#include "Massage/BufferedMassageDecoder.h"
//#include "Print.h"

/// Main AsciiMassageDecoder class.
// Maybe Print should be private !!!
// Print should be instantiated and not extended
class AsciiMassageDecoder : public BufferedMassageDecoder
{
public:
  /// Constructor.
  AsciiMassageDecoder();

  /// Reads next byte.
  virtual int8_t nextByte(bool* error=0);

  /// Reads next int.
  virtual int16_t nextInt(bool* error=0); 

  /// Reads next long.
  virtual int32_t nextLong(bool* error=0);

  /// Reads next float.
  virtual float nextFloat(bool* error=0);
/*
   /// Begins the sending of a message.
  virtual void beginPacket(const char* address);

  /// Adds a byte.
  virtual void addByte(uint8_t value);

  /// Adds an int.
  virtual void addInt(int16_t value);

  /// Adds a long.
  virtual void addLong(int32_t value);

  /// Adds a float.
  virtual void addFloat(float value);

  /// Ends the sending of a message.
  virtual void endPacket();

  // REQUIRED BY PRINT, BUT SHOULD NEVER BE USED !!!
  virtual size_t write(uint8_t) ;
  */

protected:
  /// Decode a single value read from the serial stream.
  /// Returns true if a massage is terminated
  virtual bool _decode(int serialByte) ;
  /// Processes a single value read from the serial stream.
  // virtual bool _processTx(int serialByte) ;

private:
  // Moves nextIndex to the next token.
  bool _updateNextIndex();

  // Returns true iff it is still possible to call next*().
  bool _hasNext() const;

  // Helper function to read next value.
  void _nextBlock(bool isInteger, uint8_t* value, size_t n, bool* error);


};




#endif
