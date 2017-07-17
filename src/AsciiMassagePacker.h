#ifndef AsciiMassagePacker_h
#define AsciiMassagePacker_h


#include "Massage/MassagePacker.h"
#include "Print.h"

/// Main AsciiMassagePacker class.
// Maybe Print should be private !!!
// Print should be instantiated and not extended
class AsciiMassagePacker : public MassagePacker, private Print
{
public:
  /// Constructor.
  AsciiMassagePacker();

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

  // REQUIRED BY PRINT, BUT SHOULD NEVER BE USED EXTERNALLY !!!
  virtual size_t write(uint8_t) ;
  

};




#endif
