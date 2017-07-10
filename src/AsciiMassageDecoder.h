#ifndef AsciiMassageDecoder_h
#define AsciiMassageDecoder_h


#include "Massage/MassageDecoder.h"


/// Main AsciiMassageDecoder class.
class AsciiMassageDecoder : public MassageDecoder
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
