//#define DEBUG_TOM

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "AsciiMassagePacker.h"

AsciiMassagePacker::AsciiMassagePacker() {
    flush();
  }


void AsciiMassagePacker::beginPacket(const char* address)
{
  flush();
  print(address);
}

void AsciiMassagePacker::addByte(uint8_t value)
{
  addLong(value);
}

void AsciiMassagePacker::addInt(int16_t value)
{
  addLong(value);
}

void AsciiMassagePacker::addLong(int32_t value)
{
  write(' ');
  print(value);


}

void AsciiMassagePacker::addFloat(float value)
{
  write(' ');
  print(value);

}

void AsciiMassagePacker::endPacket()
{
  write('\n');
  //write(0);
  //_messageSize--;

}

  size_t AsciiMassagePacker::write(uint8_t data) {
        _store(data);
        return 0;
    }

