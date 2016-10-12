//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "Massenger.h"

Massenger::Massenger(Stream* stream)
  : _stream(stream) {}

bool Massenger::receive()
{
  // Flush.
  flush();

  // Read stream.
  while (_stream->available())
  {
    if (_process(_stream->read()))
      return true;
  }

  return false;
}

void Massenger::flush()
{
  _messageSize = 0;
}

bool Massenger::dispatch(const char* address, callbackFunction callback)
{
  // Verity if address matches beginning of buffer.
  bool matches = (strcmp(_buffer, address) == 0);
  if (matches) callback();
  return matches;
}

void Massenger::send(const char *address)
{
  sendBegin(address);
  sendEnd();
}

void Massenger::sendByte(const char *address, uint8_t value)
{
  sendBegin(address);
  sendByte(value);
  sendEnd();
}

void Massenger::sendInt(const char *address, int16_t value)
{
  sendBegin(address);
  sendInt(value);
  sendEnd();
}

void Massenger::sendLong(const char *address, int32_t value)
{
  sendBegin(address);
  sendLong(value);
  sendEnd();
}

void Massenger::sendFloat(const char *address, float value)
{
  sendBegin(address);
  sendFloat(value);
  sendEnd();
}

void Massenger::sendDouble(const char *address, double value)
{
  sendBegin(address);
  sendDouble(value);
  sendEnd();
}

bool Massenger::_write(uint8_t value)
{
  if (_messageSize >= MASSENGER_BUFFERSIZE)
    return false;
  _buffer[_messageSize++] = value;
}
