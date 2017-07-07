//#define DEBUG_TOM

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "AsciiMassenger.h"

AsciiMassenger::AsciiMassenger() {
    flushRx();
  }



int8_t AsciiMassenger::nextByte(bool* error) {
  int8_t v;
  _nextBlockRx(true, (uint8_t*)&v, sizeof(int8_t), error);

  return v;
}

int16_t AsciiMassenger::nextInt(bool* error)
{
  int16_t v;
  _nextBlockRx(true, (uint8_t*)&v, sizeof(int16_t), error);

  return v;
}

int32_t AsciiMassenger::nextLong(bool* error)
{
  int32_t v;
  _nextBlockRx(true, (uint8_t*)&v, sizeof(int32_t), error);

  return v;
}

float AsciiMassenger::nextFloat(bool* error)
{
  double v;
  _nextBlockRx(false, (uint8_t*)&v, sizeof(double), error);

  return (float)v;
}

void AsciiMassenger::beginPacket(const char* address)
{
  flushTx();
  print(address);
}

void AsciiMassenger::addByte(uint8_t value)
{
  addLong(value);
}

void AsciiMassenger::addInt(int16_t value)
{
  addLong(value);
}

void AsciiMassenger::addLong(int32_t value)
{
  write(' ');
  print(value);

 //_stream->write(' ');
 // _stream->print(value);
}

void AsciiMassenger::addFloat(float value)
{
  write(' ');
  print(value);
  //_stream->write(' ');
 // _stream->print(value);
}

void AsciiMassenger::endPacket()
{
  write('\n');
  write(0);
 // _stream->write('\n');
}

bool AsciiMassenger::_decode(int streamByte)
{
  // Check if we've reached the end of the buffer.
  if (_messageSizeRx >= (MASSENGER_BUFFERSIZE -1))
  {
    _messageSizeRx = MASSENGER_BUFFERSIZE -1;
    _storeRx(0);
    flushRx();
    return false;
  }

  // Process byte.
  switch (streamByte)
  {
    case '\n': // LF
    case '\r': // CR
      if (_messageSizeRx > 0) // only process this if we are *not* at beginning
      {
        if (rxBuffer[_messageSizeRx-1] != 0)
          _storeRx(0);

        // Position _nextIndex after command address string.
        _nextIndexRx = 0;
        _updateNextIndexRx();

        return true;
      }
        
      flushRx();
      break;
    case 0 :
    case ' ':
      // Put null character instead of space to easily use atoi()/atof() functions.
      if (_messageSizeRx > 0 && rxBuffer[_messageSizeRx-1] != 0)
      {
        _storeRx(0);
      }
      break;
    default: // caught a non-reserved character
      _storeRx(streamByte);
  }

  return false;
}

bool AsciiMassenger::_updateNextIndexRx()
{
  while (rxBuffer[_nextIndexRx] != 0) _nextIndexRx++;
  _nextIndexRx++;
  return (_nextIndexRx < _messageSizeRx);
}

bool AsciiMassenger::_hasNextRx() const {
  return (_nextIndexRx < _messageSizeRx);
}

void AsciiMassenger::_nextBlockRx(bool isInteger, uint8_t* value, size_t n, bool* error)
{
  // Check for errors.
  bool err = !_hasNextRx();
  if (err)
    memset(value, 0, n); // set to zero (default)

  if (error)
    *error = err;

  // Process data.
  if (!err)
  {
    // Switch integer vs real.
    if (isInteger)
    {
      long val = strtol(&rxBuffer[_nextIndexRx], 0, 10);
      memcpy(value, &val, n);
    }
    else
    {
      double  val = strtod(&rxBuffer[_nextIndexRx], 0);
      memcpy(value, &val, n);
    }

    _updateNextIndexRx();
  }

}


  size_t AsciiMassenger::write(uint8_t data) {
        _storeTx(data);
        return 0;
    }

