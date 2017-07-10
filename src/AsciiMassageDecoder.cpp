//#define DEBUG_TOM

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "AsciiMassageDecoder.h"

AsciiMassageDecoder::AsciiMassageDecoder() {
    flush();
  }



int8_t AsciiMassageDecoder::nextByte(bool* error) {
  int8_t v;
  _nextBlock(true, (uint8_t*)&v, sizeof(int8_t), error);

  return v;
}

int16_t AsciiMassageDecoder::nextInt(bool* error)
{
  int16_t v;
  _nextBlock(true, (uint8_t*)&v, sizeof(int16_t), error);

  return v;
}

int32_t AsciiMassageDecoder::nextLong(bool* error)
{
  int32_t v;
  _nextBlock(true, (uint8_t*)&v, sizeof(int32_t), error);

  return v;
}

float AsciiMassageDecoder::nextFloat(bool* error)
{
  double v;
  _nextBlock(false, (uint8_t*)&v, sizeof(double), error);

  return (float)v;
}
/*
void AsciiMassageDecoder::beginPacket(const char* address)
{
  flush();
  print(address);
}

void AsciiMassageDecoder::addByte(uint8_t value)
{
  addLong(value);
}

void AsciiMassageDecoder::addInt(int16_t value)
{
  addLong(value);
}

void AsciiMassageDecoder::addLong(int32_t value)
{
  write(' ');
  print(value);

 //_stream->write(' ');
 // _stream->print(value);
}

void AsciiMassageDecoder::addFloat(float value)
{
  write(' ');
  print(value);
  //_stream->write(' ');
 // _stream->print(value);
}

void AsciiMassageDecoder::endPacket()
{
  write('\n');
  write(0);
 // _stream->write('\n');
}
*/
bool AsciiMassageDecoder::_decode(int streamByte)
{
  // Check if we've reached the end of the buffer.
  if (_messageSize >= (MASSAGE_DECODER_BUFFERSIZE -1))
  {
    _messageSize = MASSAGE_DECODER_BUFFERSIZE -1;
    _store(0);
    flush();
    return false;
  }

  // Process byte.
  switch (streamByte)
  {
    case '\n': // LF
    case '\r': // CR
      if (_messageSize > 0) // only process this if we are *not* at beginning
      {
        if (buffer[_messageSize-1] != 0)
          _store(0);

        // Position _nextIndex after command address string.
        _nextIndex = 0;
        _updateNextIndex();

        return true;
      }
        
      flush();
      break;
    case 0 :
    case ' ':
      // Put null character instead of space to easily use atoi()/atof() functions.
      if (_messageSize > 0 && buffer[_messageSize-1] != 0)
      {
        _store(0);
      }
      break;
    default: // caught a non-reserved character
      _store(streamByte);
  }

  return false;
}

bool AsciiMassageDecoder::_updateNextIndex()
{
  while (buffer[_nextIndex] != 0) _nextIndex++;
  _nextIndex++;
  return (_nextIndex < _messageSize);
}

bool AsciiMassageDecoder::_hasNext() const {
  return (_nextIndex < _messageSize);
}

void AsciiMassageDecoder::_nextBlock(bool isInteger, uint8_t* value, size_t n, bool* error)
{
  // Check for errors.
  bool err = !_hasNext();
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
      long val = strtol(&buffer[_nextIndex], 0, 10);
      memcpy(value, &val, n);
    }
    else
    {
      double  val = strtod(&buffer[_nextIndex], 0);
      memcpy(value, &val, n);
    }

    _updateNextIndex();
  }

}

/*
  size_t AsciiMassageDecoder::write(uint8_t data) {
        _store(data);
        return 0;
    }

*/