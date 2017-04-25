#ifndef AsciiMassenger_h
#define AsciiMassenger_h


#include "Massenger/BufferedMassenger.h"

/// Main AsciiMassenger class.
class AsciiMassenger : public BufferedMassenger
{
public:
  /// Constructor.
  AsciiMassenger(Stream* stream=&Serial);

  /// Reads next byte.
  virtual int8_t nextByte(bool* error=0);

  /// Reads next int.
  virtual int16_t nextInt(bool* error=0);

  /// Reads next long.
  virtual int32_t nextLong(bool* error=0);

  /// Reads next float.
  virtual float nextFloat(bool* error=0);

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

protected:
  /// Processes a single value read from the serial stream.
  virtual bool _process(int serialByte);

private:
  // Moves nextIndex to the next token.
  bool _updateNextIndex();

  // Returns true iff it is still possible to call next*().
  bool _hasNext() const;

  // Helper function to read next value.
  void _nextBlock(bool isInteger, uint8_t* value, size_t n, bool* error);

};




#endif
