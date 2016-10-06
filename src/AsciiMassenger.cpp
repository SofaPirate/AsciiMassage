//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "AsciiMassenger.h"

AsciiMassenger::AsciiMassenger(Stream* stream)
  : Massenger(stream) {}

void AsciiMassenger::flush()
{
  Massenger::flush();
  _nextIndex = 0;
}

int8_t AsciiMassenger::nextByte(bool* error) {
  int8_t v;
  _nextBlock(true, (uint8_t*)&v, sizeof(int8_t), error);
  Serial.println(v);
  return v;
}

int16_t AsciiMassenger::nextInt(bool* error)
{
  int16_t v;
  _nextBlock(true, (uint8_t*)&v, sizeof(int16_t), error);
  Serial.println(v);
  return v;
}

int32_t AsciiMassenger::nextLong(bool* error)
{
  int32_t v;
  _nextBlock(true, (uint8_t*)&v, sizeof(int32_t), error);
  Serial.println(v);
  return v;
}

float AsciiMassenger::nextFloat(bool* error)
{
  float v;
  _nextBlock(false, (uint8_t*)&v, sizeof(float), error);
  Serial.println(v);
  return v;
}

double AsciiMassenger::nextDouble(bool* error)
{
  double v;
  _nextBlock(false, (uint8_t*)&v, sizeof(double), error);
  Serial.println(v);
  return v;
}

void AsciiMassenger::sendBegin(const char* address)
{
  _stream->print(address);
}

void AsciiMassenger::sendByte(uint8_t value)
{
  sendLong(value);
}

void AsciiMassenger::sendInt(int16_t value)
{
  sendLong(value);
}

void AsciiMassenger::sendLong(int32_t value)
{
  _stream->write(' ');
  _stream->print(value);
}

void AsciiMassenger::sendFloat(float value)
{
  sendDouble(value);
}

void AsciiMassenger::sendDouble(double value)
{
  _stream->write(' ');
  _stream->print(value);
}


void AsciiMassenger::sendEnd()
{
  _stream->write('\n');
}

bool AsciiMassenger::_process(int streamByte)
{
  // Check if we've reached the end of the buffer.
  if (_messageSize >= (MASSENGER_BUFFERSIZE-1))
  {
    _messageSize = MASSENGER_BUFFERSIZE-1;
    _write(0);
    return true;
  }

  // Process byte.
  switch (streamByte)
  {
    case '\n': // LF
    case '\r': // CR
      if (_messageSize > 0) // only process this if we are *not* at beginning
      {
        if (_buffer[_messageSize-1] != 0)
          _write(0);

        // Position _nextIndex after command address string.
        _nextIndex = 0;
        _updateNextIndex();

        return true;
      }
      break;
    case ' ':
      // Put null character instead of space to easily use atoi()/atof() functions.
      if (_messageSize > 0 && _buffer[_messageSize-1] != 0)
      {
        _write(0);
      }
      break;
    default: // caught a non-reserved character
      _write(streamByte);
  }

  return false;
}

bool AsciiMassenger::_updateNextIndex()
{
  while (_buffer[_nextIndex] != 0)
    _nextIndex++;
  _nextIndex++;
  return (_nextIndex < _messageSize);
}

bool AsciiMassenger::_hasNext() const {
  return (_nextIndex < _messageSize);
}

void AsciiMassenger::_nextBlock(bool isInteger, uint8_t* value, size_t n, bool* error)
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
      long val = strtol(&_buffer[_nextIndex], 0, 10);
      memcpy(value, &val, n);
    }
    else
    {
      double val = strtod(&_buffer[_nextIndex], 0);
      memcpy(value, &val, n);
    }

    _updateNextIndex();
  }
}
