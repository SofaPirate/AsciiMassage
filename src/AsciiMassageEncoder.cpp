//#define DEBUG_TOM

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "AsciiMassageEncoder.h"

AsciiMassageEncoder::AsciiMassageEncoder() {
    flush();
  }


void AsciiMassageEncoder::beginPacket(const char* address)
{
  flush();
  print(address);
}

void AsciiMassageEncoder::addByte(uint8_t value)
{
  addLong(value);
}

void AsciiMassageEncoder::addInt(int16_t value)
{
  addLong(value);
}

void AsciiMassageEncoder::addLong(int32_t value)
{
  write(' ');
  print(value);

 //_stream->write(' ');
 // _stream->print(value);
}

void AsciiMassageEncoder::addFloat(float value)
{
  write(' ');
  print(value);
  //_stream->write(' ');
 // _stream->print(value);
}

void AsciiMassageEncoder::endPacket()
{
  write('\n');
  write(0);
 // _stream->write('\n');
}

  size_t AsciiMassageEncoder::write(uint8_t data) {
        _store(data);
        return 0;
    }

