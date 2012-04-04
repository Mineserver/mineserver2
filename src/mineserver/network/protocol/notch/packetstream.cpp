/*
  Copyright (c) 2011-2012, The Mineserver Project
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string>
#include <cstring>
#include <errno.h>
#include <vector>

#include <mineserver/byteorder.h>
#include <mineserver/network/protocol/notch/packetstream.h>

void Mineserver::Network_Protocol_Notch_PacketStream::bytesFrom(const uint8_t* src, size_t n)
{
	m_buffer->insert(m_buffer->end(), src, src+n);
}

void Mineserver::Network_Protocol_Notch_PacketStream::bytesFrom(const std::vector<uint8_t> src)
{
  m_buffer->insert(m_buffer->end(), src.begin(), src.end());
}

void Mineserver::Network_Protocol_Notch_PacketStream::bytesTo(uint8_t* dst, size_t n)
{
  memcpy(dst, reinterpret_cast<uint8_t*>(&((*m_buffer)[m_pos])), n);
  m_pos += n;
}

void Mineserver::Network_Protocol_Notch_PacketStream::bytesTo(std::vector<uint8_t> dst)
{
  dst.insert(dst.end(), m_buffer->begin()+m_pos, m_buffer->end());
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(bool val)
{
  m_buffer->push_back(val ? 1 : 0);

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(bool& val)
{
  if (haveData(1))
  {
    val = ((*m_buffer)[m_pos++] != 0);
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(int8_t val)
{
  m_buffer->push_back(val);

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(int8_t& val)
{
  if (haveData(1))
  {
    val = (*m_buffer)[m_pos++];
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(uint8_t val)
{
  m_buffer->push_back(val);

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(uint8_t& val)
{
  if (haveData(1))
  {
    val = (*m_buffer)[m_pos++];
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(int16_t val)
{
  int16_t nval = htobe16(val);

  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(int16_t& val)
{
  if (haveData(2))
  {
    val = betoh16(*(reinterpret_cast<int16_t*>(&((*m_buffer)[m_pos]))));
    m_pos += 2;
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(uint16_t val)
{
  uint16_t nval = htobe16(val);

  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(uint16_t& val)
{
  if (haveData(2))
  {
    val = betoh16(*(reinterpret_cast<uint16_t*>(&((*m_buffer)[m_pos]))));
    m_pos += 2;
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(int32_t val)
{
  int32_t nval = htobe32(val);

  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(int32_t& val)
{
  if (haveData(4))
  {
    val = betoh32(*(reinterpret_cast<int32_t*>(&((*m_buffer)[m_pos]))));
    m_pos += 4;
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(uint32_t val)
{
  uint32_t nval = htobe32(val);

  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(uint32_t& val)
{
  if (haveData(4))
  {
    val = betoh32(*(reinterpret_cast<uint32_t*>(&((*m_buffer)[m_pos]))));
    m_pos += 4;
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(int64_t val)
{
  int64_t nval = htobe64(val);

  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(int64_t& val)
{
  if (haveData(8))
  {
    val = betoh64(*(reinterpret_cast<int64_t*>(&((*m_buffer)[m_pos]))));
    m_pos += 8;
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(uint64_t val)
{
  uint64_t nval = htobe64(val);

  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(uint64_t& val)
{
  if (haveData(8))
  {
    val = betoh64(*(reinterpret_cast<uint64_t*>(&((*m_buffer)[m_pos]))));
    m_pos += 8;
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(float val)
{
  uint32_t nval;

  memcpy(&nval, &val, 4);
  nval = htobe32(nval);
  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(float& val)
{
  if (haveData(4))
  {
    uint32_t res;
    uint8_t* p = reinterpret_cast<uint8_t*>(&res);

    for (size_t i = 0; i < sizeof(res); ++i)
    {
      *p++ = (*m_buffer)[m_pos++];
    }

    uint32_t ival = betoh32(res);
    memcpy(&val, &ival, 4);

    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(double val)
{
  uint64_t nval;

  memcpy(&nval, &val, 8);
  nval = betoh64(nval);
  append(reinterpret_cast<const uint8_t*>(&nval), sizeof(nval));

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(double& val)
{
  if (haveData(8))
  {
    uint64_t res;
    uint8_t* p = reinterpret_cast<uint8_t*>(&res);

    for (size_t i = 0; i < sizeof(res); ++i)
    {
      *p++ = (*m_buffer)[m_pos++];
    }

    uint64_t ival = betoh64(res);
    memcpy(&val, &ival, 8);

    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator<<(const std::string& str)
{
  char *dst, *dst_c;
  size_t src_s, src_l, dst_s, dst_l;

  src_s = src_l = str.size();
  dst_s = dst_l = str.size()*2;

  char* src_c = const_cast<char*>(str.c_str());
  dst = dst_c = new char[dst_s];

  memset(dst, 0, dst_s);

  size_t rc = iconv(m_iconvUtfHandler, &src_c, &src_l, &dst_c, &dst_l);

  // Should be handling these errors
  if (static_cast<int>(rc) == -1) {
    switch (errno) {
    case E2BIG:
      break;
    case EILSEQ:
      break;
    case EINVAL:
      break;
    default:
      break;
    }
  }

  size_t result_b = dst_s-dst_l;
  size_t result_c = result_b/2;

  result_c = htobe16(result_c);

  append(reinterpret_cast<const uint8_t*>(&result_c), 2);
  append(reinterpret_cast<const uint8_t*>(dst), result_b);

  delete[] dst;

  return *this;
}

Mineserver::Network_Protocol_Notch_PacketStream& Mineserver::Network_Protocol_Notch_PacketStream::operator>>(std::string& str)
{
  int16_t len;

  if (haveData(2))
  {
    len = betoh16(*(reinterpret_cast<int16_t*>(&((*m_buffer)[m_pos]))));
    m_pos += 2;
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  if (haveData(len * 2))
  {
    char *dst, *dst_c;
    size_t src_s, src_l, dst_s, dst_l;

    src_s = src_l = len * 2;
    dst_s = dst_l = len;

    char* src_c = reinterpret_cast<char*>(&((*m_buffer)[m_pos]));
    dst = dst_c = new char[dst_s];

    size_t rc = iconv(m_iconvUcsHandler, &src_c, &src_l, &dst_c, &dst_l);

    // Should be handling these errors
    if (static_cast<int>(rc) == -1) {
      switch (errno) {
      case E2BIG:
        break;
      case EILSEQ:
        break;
      case EINVAL:
        break;
      default:
        break;
      }
    }

    str.assign(dst, dst_s);

    delete[] dst;

    m_pos += len * 2;

    m_valid = true;
  }
  else
  {
    m_valid = false;
  }

  return *this;
}
