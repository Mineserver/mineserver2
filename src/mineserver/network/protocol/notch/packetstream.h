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

#ifndef MINESERVER_NETWORK_PROTOCOL_NOTCH_PACKETSTREAM_H
#define MINESERVER_NETWORK_PROTOCOL_NOTCH_PACKETSTREAM_H

#include <vector>
#include <string>
#include <iconv.h>
#include <stdlib.h>

#include <mineserver/byteorder.h>

namespace Mineserver
{
  class Network_Protocol_Notch_PacketStream
  {
  private:
    std::vector<uint8_t>* m_buffer;
    size_t m_pos;
    bool m_valid;
    iconv_t m_iconvUtfHandler;
    iconv_t m_iconvUcsHandler;

  public:
    Network_Protocol_Notch_PacketStream() : m_buffer(NULL),m_pos(0),m_valid(false)
    {
      m_iconvUcsHandler = iconv_open("UTF-8", "UCS-2BE");
      m_iconvUtfHandler = iconv_open("UCS-2BE", "UTF-8");
    }

    ~Network_Protocol_Notch_PacketStream()
    {
      iconv_close(m_iconvUcsHandler);
      iconv_close(m_iconvUtfHandler);
    }

    inline std::vector<uint8_t>* getBuffer()
    {
      return m_buffer;
    }

    inline void setBuffer(std::vector<uint8_t>* buffer)
    {
      m_buffer = buffer;
    }

    inline size_t getPos()
    {
      return m_pos;
    }

    inline void setPos(size_t pos)
    {
      m_pos = pos;
    }

    inline bool isValid()
    {
      return m_valid;
    }

    inline void setValid(bool valid)
    {
      m_valid = valid;
    }

    inline void append(const uint8_t* const buffer, const size_t n)
    {
      m_buffer->insert(m_buffer->end(), buffer, buffer + n);
    }

    inline void remove()
    {
      m_buffer->erase(m_buffer->begin(), m_buffer->begin() + m_pos);
      m_pos = 0;
    }

    inline void reset()
    {
      m_pos = 0;
      m_buffer = NULL;
      m_valid = false;
    }

    inline bool haveData(size_t n)
    {
      return m_valid && (m_buffer->size() - m_pos) >= n;
    }

    void bytesFrom(const uint8_t* src, size_t n);
    void bytesFrom(const std::vector<uint8_t> src);
    void bytesTo(uint8_t* dst, size_t n);
    void bytesTo(std::vector<uint8_t> dst);

    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(bool val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(bool& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(int8_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(int8_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(uint8_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(uint8_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(int16_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(int16_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(uint16_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(uint16_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(int32_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(int32_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(uint32_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(uint32_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(int64_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(int64_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(uint64_t val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(uint64_t& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(float val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(float& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(double val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(double& val);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(const std::string& str);
    Mineserver::Network_Protocol_Notch_PacketStream& operator>>(std::string& str);
    Mineserver::Network_Protocol_Notch_PacketStream& operator<<(const Mineserver::Network_Protocol_Notch_PacketStream& other);
  };
}

#endif
