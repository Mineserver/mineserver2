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

#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>

#ifdef WIN32
#include <winsock2.h>
#endif

#include <mineserver/nbt.h>

#define ALLOCATE_NBTFILE 1048576

//NBT level file reading
//More info: http://www.minecraft.net/docs/NBT.txt

std::string dtos(double n)
{
  std::ostringstream result;
  result << n;
  return result.str();
}

Mineserver::NBT::NBT(eTAG_Type type, eTAG_Type listType) : m_type(type)
{
  memset(&m_value, 0, sizeof(m_value));
  if (type == TAG_LIST)
  {
    m_value.listVal.type = listType;
  }
}

Mineserver::NBT::NBT(int8_t value) : m_type(TAG_BYTE)
{
  m_value.byteVal = value;
}

Mineserver::NBT::NBT(int16_t value) : m_type(TAG_SHORT)
{
  m_value.shortVal = value;
}

Mineserver::NBT::NBT(int32_t value) : m_type(TAG_INT)
{
  m_value.intVal = value;
}

Mineserver::NBT::NBT(int64_t value) : m_type(TAG_LONG)
{
  m_value.longVal = value;
}

Mineserver::NBT::NBT(float value) : m_type(TAG_FLOAT)
{
  m_value.floatVal = value;
}

Mineserver::NBT::NBT(double value) : m_type(TAG_DOUBLE)
{
  m_value.doubleVal = value;
}

Mineserver::NBT::NBT(uint8_t* buf, int32_t len) : m_type(TAG_BYTE_ARRAY)
{
  m_value.byteArrayVal = new std::vector<uint8_t>(buf, buf + len);
}

Mineserver::NBT::NBT(std::vector<uint8_t> const& bytes) : m_type(TAG_BYTE_ARRAY)
{
  m_value.byteArrayVal = new std::vector<uint8_t>(bytes);
}

Mineserver::NBT::NBT(const std::string& str) : m_type(TAG_STRING)
{
  m_value.stringVal = new std::string(str);
}

Mineserver::NBT::NBT(eTAG_Type type, uint8_t** buf, int& remaining) : m_type(type)
{
  switch (m_type)
  {
  case TAG_BYTE:
    remaining--;
    if (remaining >= 0)
    {
      m_value.byteVal = **buf;
      (*buf)++;
    }
    break;
  case TAG_SHORT:
    remaining -= 2;
    if (remaining >= 0)
    {
      m_value.shortVal = **reinterpret_cast<int16_t**>(buf);
      *buf += 2;
    }
    break;
  case TAG_INT:
    remaining -= 4;
    if (remaining >= 0)
    {
      m_value.intVal = **reinterpret_cast<int32_t**>(buf);
      *buf += 4;
    }
    break;
  case TAG_LONG:
    remaining -= 8;
    if (remaining >= 0)
    {
      m_value.longVal = **reinterpret_cast<int64_t**>(buf);
      *buf += 8;
    }
    break;
  case TAG_FLOAT:
    remaining -= 4;
    if (remaining >= 0)
    {
      m_value.floatVal = **reinterpret_cast<float**>(buf);
      *buf += 4;
    }
    break;
  case TAG_DOUBLE:
    remaining -= 8;
    if (remaining >= 0)
    {
      m_value.doubleVal = **reinterpret_cast<double**>(buf);
      *buf += 8;
    }
    break;
  case TAG_BYTE_ARRAY:
    remaining -= 4;
    if (remaining >= 0)
    {
      int32_t bufLen = **reinterpret_cast<int32_t**>(buf);
      remaining -= bufLen;
      *buf += 4;
      if (remaining >= 0)
      {
        m_value.byteArrayVal = new std::vector<uint8_t>();
        m_value.byteArrayVal->assign(*buf, (*buf) + bufLen);
        *buf += bufLen;
      }
    }
    break;
  case TAG_STRING:
    remaining -= 2;
    if (remaining >= 0)
    {
      int16_t stringLen = **reinterpret_cast<int16_t**>(buf);
      remaining -= stringLen;
      *buf += 2;
      if (remaining >= 0)
      {
        m_value.stringVal = new std::string((char*)*buf, stringLen);
        *buf += stringLen;
      }
    }
    break;
  case TAG_LIST:
    remaining -= 5;
    if (remaining >= 0)
    {
      int8_t type = **buf;
      (*buf)++;
      m_value.listVal.type = (eTAG_Type)type;
      int32_t count = **reinterpret_cast<int32_t**>(buf);
      *buf += 4;
      m_value.listVal.data = new std::vector<NBT*>();
      if (count)
      {
        m_value.listVal.data->resize(count);
      }

      for (int i = 0; i < count; i++)
      {
        (*m_value.listVal.data)[i] = new NBT((eTAG_Type)type, buf, remaining);
      }
    }
    break;
  case TAG_COMPOUND:
    m_value.compoundVal = new std::map<std::string, NBT*>();
    while (remaining > 0)
    {
      remaining--;
      int8_t type = **buf;
      (*buf)++;
      if (type == TAG_END)
      {
        break;
      }

      remaining -= 2;
      if (remaining <= 0)
      {
        break;
      }

      int16_t stringLen = **reinterpret_cast<int16_t**>(buf);
      *buf += 2;

      remaining -= stringLen;

      if (remaining <= 0)
      {
        break;
      }

      std::string key((char*)*buf, stringLen);
      *buf += stringLen;

      (*m_value.compoundVal)[key] = new NBT((eTAG_Type)type, buf, remaining);
    }
    break;
  case TAG_END:
    break;
  }
}

Mineserver::NBT::~NBT()
{
  cleanup();
}

Mineserver::NBT* Mineserver::NBT::operator[](const std::string& index)
{
  if (m_type != TAG_COMPOUND)
  {
    return NULL;
  }

  if (!m_value.compoundVal->count(index))
  {
    return NULL;
  }

  return (*m_value.compoundVal)[index];
}

Mineserver::NBT* Mineserver::NBT::operator[](const char* index)
{
  if (m_type != TAG_COMPOUND)
  {
    return NULL;
  }

  std::string stdIndex(index, strlen(index));

  if (!m_value.compoundVal->count(stdIndex))
  {
    return NULL;
  }

  return (*m_value.compoundVal)[stdIndex];
}

void Mineserver::NBT::Insert(const std::string& str, NBT* val)
{
  if (m_type != Mineserver::NBT::TAG_COMPOUND)
  {
    return;
  }

  if (m_value.compoundVal == 0)
  {
    m_value.compoundVal = new std::map<std::string, NBT*>();
  }

  if ((*m_value.compoundVal)[str] != 0)
  {
    delete(*m_value.compoundVal)[str];
  }

  (*m_value.compoundVal)[str] = val;
}

Mineserver::NBT::operator int8_t()
{
  if (!this || m_type != TAG_BYTE)
  {
    return 0;
  }

  return m_value.byteVal;
}

Mineserver::NBT::operator int16_t()
{
  if (!this || m_type != TAG_SHORT)
  {
    return 0;
  }

  return m_value.shortVal;
}

Mineserver::NBT::operator int32_t()
{
  if (!this || m_type != TAG_INT)
  {
    return 0;
  }

  return m_value.intVal;
}

Mineserver::NBT::operator int64_t()
{
  if (!this || m_type != TAG_LONG)
  {
    return 0;
  }

  return m_value.longVal;
}

Mineserver::NBT::operator float()
{
  if (!this || m_type != TAG_FLOAT)
  {
    return 0;
  }

  return m_value.floatVal;
}

Mineserver::NBT::operator double()
{
  if (!this || m_type != TAG_DOUBLE)
  {
    return 0;
  }

  return m_value.doubleVal;
}

Mineserver::NBT& Mineserver::NBT::operator =(int8_t val)
{
  cleanup();
  m_type = TAG_BYTE;
  m_value.byteVal = val;
  return *this;
}

Mineserver::NBT& Mineserver::NBT::operator =(int16_t val)
{
  cleanup();
  m_type = TAG_SHORT;
  m_value.shortVal = val;
  return *this;
}

Mineserver::NBT& Mineserver::NBT::operator =(int32_t val)
{
  cleanup();
  m_type = TAG_INT;
  m_value.intVal = val;
  return *this;
}

Mineserver::NBT& Mineserver::NBT::operator =(int64_t val)
{
  cleanup();
  m_type = TAG_LONG;
  m_value.longVal = val;
  return *this;
}

Mineserver::NBT& Mineserver::NBT::operator =(float val)
{
  cleanup();
  m_type = TAG_FLOAT;
  m_value.floatVal = val;
  return *this;
}

Mineserver::NBT& Mineserver::NBT::operator =(double val)
{
  cleanup();
  m_type = TAG_DOUBLE;
  m_value.doubleVal = val;
  return *this;
}

std::vector<uint8_t> *Mineserver::NBT::GetByteArray()
{
  if (m_type != TAG_BYTE_ARRAY)
  {
    return NULL;
  }
  if (m_value.byteArrayVal == NULL)
  {
    m_value.byteArrayVal = new std::vector<uint8_t>();
  }
  return m_value.byteArrayVal;
}


std::string* Mineserver::NBT::GetString()
{
  if (m_type != TAG_STRING)
  {
    return NULL;
  }
  if (m_value.stringVal == NULL)
  {
    m_value.stringVal = new std::string();
  }
  return m_value.stringVal;
}

Mineserver::NBT::eTAG_Type Mineserver::NBT::GetListType()
{
  if (m_type != TAG_LIST)
  {
    return TAG_END;
  }
  return m_value.listVal.type;
}

std::vector<Mineserver::NBT*> *Mineserver::NBT::GetList()
{
  if (m_type != TAG_LIST)
  {
    return NULL;
  }
  if (m_value.listVal.data == NULL)
  {
    m_value.listVal.data = new std::vector<NBT*>();
  }
  return m_value.listVal.data;
}


void Mineserver::NBT::SetType(eTAG_Type type, eTAG_Type listType)
{
  cleanup();
  m_type = type;

  if (m_type == TAG_LIST)
  {
    m_value.listVal.type = listType;
  }
}

Mineserver::NBT::eTAG_Type Mineserver::NBT::GetType()
{
  return m_type;
}

void Mineserver::NBT::cleanup()
{
  if (m_type == TAG_STRING)
  {
    delete m_value.stringVal;
  }
  if (m_type == TAG_BYTE_ARRAY)
  {
    delete m_value.byteArrayVal;
  }
  if (m_type == TAG_LIST)
  {
    if (m_value.listVal.data != NULL)
    {
      std::vector<NBT*>::iterator iter = m_value.listVal.data->begin(), end = m_value.listVal.data->end();
      for (; iter != end ; iter++)
      {
        delete *iter;
      }
      delete m_value.listVal.data;
    }
  }
  if (m_type == TAG_COMPOUND)
  {
    if (m_value.compoundVal != NULL)
    {
      std::map<std::string, NBT*>::iterator iter = m_value.compoundVal->begin(), end = m_value.compoundVal->end();
      for (; iter != end ; iter++)
      {
        delete iter->second;
      }

      delete m_value.compoundVal;
    }
  }

  memset(&m_value, 0, sizeof(m_value));
  m_type = TAG_END;
}

Mineserver::NBT* Mineserver::NBT::LoadFromFile(const std::string& filename)
{
  FILE* fp = fopen(filename.c_str(), "rb");
  if (fp == NULL)
  {
    return NULL;
  }
  fseek(fp, -4, SEEK_END);
  uint32_t uncompressedSize = 0;
  fread(&uncompressedSize, 4, 1, fp);
  fclose(fp);

  //Do endian testing!
  int32_t endiantestint = 1;
  int8_t* endiantestchar = (int8_t*)&endiantestint;
  if (*endiantestchar != 1)
  {
    //Swap order
    int uncompressedSizeOld = uncompressedSize;
    uint8_t* newpointer = reinterpret_cast<uint8_t*>(&uncompressedSize);
    uint8_t* oldpointer = reinterpret_cast<uint8_t*>(&uncompressedSizeOld);
    newpointer[0] = oldpointer[3];
    newpointer[1] = oldpointer[2];
    newpointer[2] = oldpointer[1];
    newpointer[3] = oldpointer[0];
  }

  if (uncompressedSize == 0)
  {
//    LOG2(WARNING, "Unable to determine uncompressed size of " + filename);
    uncompressedSize = ALLOCATE_NBTFILE * 10;
  }

  uint8_t* uncompressedData = new uint8_t[uncompressedSize];
  gzFile nbtFile = gzopen(filename.c_str(), "rb");
  if (nbtFile == NULL)
  {
    delete[] uncompressedData;
    return NULL;
  }
  gzread(nbtFile, uncompressedData, uncompressedSize);
  gzclose(nbtFile);

  uint8_t* ptr = uncompressedData + 3; // Jump blank compound
  int remaining = uncompressedSize;

  NBT* root = new NBT(TAG_COMPOUND, &ptr, remaining);

  delete[] uncompressedData;

  return root;
}

Mineserver::NBT* Mineserver::NBT::LoadFromMemory(uint8_t* buffer, uint32_t len)
{
  //Initialize zstream to handle gzip format
  z_stream zstream;
  zstream.zalloc    = (alloc_func)0;
  zstream.zfree     = (free_func)0;
  zstream.opaque    = (voidpf)0;
  zstream.next_in   = buffer;
  zstream.next_out  = 0;
  zstream.avail_in  = len;
  zstream.avail_out = 0;
  zstream.total_in  = 0;
  zstream.total_out = 0;
  zstream.data_type = Z_BINARY;
  //inflateInit2(&zstream,16+MAX_WBITS);
  inflateInit(&zstream);

  uint32_t uncompressedSize   = ALLOCATE_NBTFILE * 10;
  uint8_t* uncompressedBuffer = new uint8_t[uncompressedSize];

  zstream.avail_out = uncompressedSize;
  zstream.next_out = uncompressedBuffer;

  //Uncompress
  int returnvalue = 0;
  if ((returnvalue = inflate(&zstream, Z_FINISH)) != Z_STREAM_END && returnvalue != Z_BUF_ERROR)
  {

    std::cout << "Error in inflate! " << returnvalue << std::endl;
    delete[] uncompressedBuffer;
    return NULL;
  }

  inflateEnd(&zstream);

  uint8_t* ptr = uncompressedBuffer + 3; // Jump blank compound
  int remaining = uncompressedSize;

  NBT* root = new NBT(TAG_COMPOUND, &ptr, remaining);

  delete[] uncompressedBuffer;

  return root;
}

void Mineserver::NBT::SaveToFile(const std::string& filename)
{
  std::vector<uint8_t> buffer;

  // Blank compound tag
  buffer.push_back(TAG_COMPOUND);
  buffer.push_back(0);
  buffer.push_back(0);

  Write(buffer);

  buffer.push_back(0);
  buffer.push_back(0);
  buffer.push_back(0);

  gzFile nbtFile = gzopen(filename.c_str(), "wb");
  gzwrite(nbtFile, &buffer[0], buffer.size());
  gzclose(nbtFile);
}


void Mineserver::NBT::SaveToMemory(uint8_t* buffer, uint32_t* len)
{

  std::vector<uint8_t> NBTBuffer;
  // Blank compound tag
  NBTBuffer.push_back(TAG_COMPOUND);
  NBTBuffer.push_back(0);
  NBTBuffer.push_back(0);

  Write(NBTBuffer);

  NBTBuffer.push_back(0);
  NBTBuffer.push_back(0);
  NBTBuffer.push_back(0);

  uLongf written = ALLOCATE_NBTFILE * 10;
  compress(buffer, &written, &NBTBuffer[0], NBTBuffer.size());
  *len = written;

}

void Mineserver::NBT::Write(std::vector<uint8_t> &buffer)
{
  int storeAt = buffer.size();;
  switch (m_type)
  {
  case TAG_BYTE:
    buffer.push_back(m_value.byteVal);
    break;
  case TAG_SHORT:
    buffer.resize(storeAt + 2);
    *reinterpret_cast<int16_t*>(&buffer[storeAt]) = m_value.shortVal;
    break;
  case TAG_INT:
    buffer.resize(storeAt + 4);
    *reinterpret_cast<int32_t*>(&buffer[storeAt]) = m_value.intVal;
    break;
  case TAG_LONG:
    buffer.resize(storeAt + 8);
    *reinterpret_cast<int64_t*>(&buffer[storeAt]) = m_value.longVal;
    break;
  case TAG_FLOAT:
    buffer.resize(storeAt + 4);
    *reinterpret_cast<float*>(&buffer[storeAt]) = m_value.floatVal;
    break;
  case TAG_DOUBLE:
    buffer.resize(storeAt + 8);
    *reinterpret_cast<double*>(&buffer[storeAt]) = m_value.doubleVal;
    break;
  case TAG_BYTE_ARRAY:
  {
    int arraySize = m_value.byteArrayVal ? m_value.byteArrayVal->size() : 0;
    buffer.resize(storeAt + 4 + arraySize);
    *reinterpret_cast<int32_t*>(&buffer[storeAt]) = arraySize;
    storeAt += 4;
    if (arraySize)
    {
      memcpy(&buffer[storeAt], &(*m_value.byteArrayVal)[0], arraySize);
    }
    break;
  }
  case TAG_STRING:
  {
    int stringLen = m_value.stringVal ? m_value.stringVal->size() : 0;
    buffer.resize(storeAt + 2 + stringLen);
    *reinterpret_cast<int16_t*>(&buffer[storeAt]) = (int16_t)stringLen;
    storeAt += 2;
    if (stringLen > 0)
    {
      memcpy(&buffer[storeAt], m_value.stringVal->c_str(), stringLen);
    }
    break;
  }
  case TAG_LIST:
  {
    buffer.resize(storeAt + 5);
    int listCount = m_value.listVal.data ? m_value.listVal.data->size() : 0;
    buffer[storeAt] = m_value.listVal.type;
    storeAt++;
    *reinterpret_cast<int32_t*>(&buffer[storeAt]) = listCount;
    for (int i = 0; i < listCount; i++)
    {
      (*m_value.listVal.data)[i]->Write(buffer);
    }
    break;
  }
  case TAG_COMPOUND:
  {
    int compoundCount = m_value.compoundVal ? m_value.compoundVal->size() : 0;
    if (compoundCount)
    {
      std::map<std::string, NBT*>::iterator iter = m_value.compoundVal->begin(), end = m_value.compoundVal->end();
      for (; iter != end; iter++)
      {
        const std::string& key = iter->first;
        int keySize = key.size();
        NBT* val = iter->second;
        int curPos = buffer.size();
        buffer.resize(curPos + 3 + keySize);
        buffer[curPos] = (uint8_t)val->GetType();
        curPos++;
        *reinterpret_cast<int16_t*>(&buffer[curPos]) = keySize;
        curPos += 2;
        if (keySize)
        {
          memcpy(&buffer[curPos], key.c_str(), keySize);
        }
        val->Write(buffer);
      }
    }
    buffer.push_back(TAG_END);
    break;
  }
  case TAG_END:
    break; //for completeness
  }
}

void Mineserver::NBT::Dump(std::string& data, const std::string& name, int tabs)
{
  std::string tabPrefix = "";
  for (int i = 0; i < tabs; i++)
  {
    tabPrefix += "  ";
  }

  switch (m_type)
  {
  case TAG_END:
    data += tabPrefix + "TAG_End(\"" + name + "\")\n";
    break;
  case TAG_BYTE:
    data += tabPrefix + "TAG_Byte(\"" + name + "\"): " + dtos((int)m_value.byteVal) + "\n";
    break;
  case TAG_SHORT:
    data += tabPrefix + "TAG_Short(\"" + name + "\"): " + dtos(m_value.shortVal) + "\n";
    break;
  case TAG_INT:
    data += tabPrefix + "TAG_Int(\"" + name + "\"): " + dtos(m_value.intVal) + "\n";
    break;
  case TAG_LONG:
    data += tabPrefix + "TAG_Long(\"" + name + "\"): " + dtos(m_value.longVal) + "\n";
    break;
  case TAG_FLOAT:
    data += tabPrefix + "TAG_Float(\"" + name + "\"): " + dtos(m_value.floatVal) + "\n";
    break;
  case TAG_DOUBLE:
    data += tabPrefix + "TAG_Double(\"" + name + "\"): " + dtos(m_value.doubleVal) + "\n";
    break;
  case TAG_BYTE_ARRAY:
    data += tabPrefix + "TAG_Byte_Array(\"" + name + "\"): \n";
    if (m_value.byteArrayVal != NULL)
    {
      data += tabPrefix + dtos(m_value.byteArrayVal->size()) + " bytes\n";
    }
    else
    {
      data += tabPrefix + "0 bytes\n";
    }
    break;
  case TAG_STRING:
    data += tabPrefix + "TAG_String(\"" + name + "\"): \n";
    if (m_value.stringVal != NULL)
    {
      data += tabPrefix + *m_value.stringVal + "\n";
    }
    else
    {
      data += tabPrefix + "\n";
    }
    break;
  case TAG_LIST:
    data += tabPrefix + "TAG_List(\"" + name + "\"): Type " + dtos(m_value.listVal.type) + "\n";
    if (m_value.listVal.data != NULL)
    {
      std::vector<NBT*>::iterator iter = m_value.listVal.data->begin(), end = m_value.listVal.data->end();
      for (; iter != end ; iter++)
      {
        (*iter)->Dump(data, std::string(""), tabs + 1);
      }
    }
    break;
  case TAG_COMPOUND:
    data += tabPrefix + "TAG_Compound(\"" + name + "\"):\n";
    if (m_value.compoundVal != NULL)
    {
      std::map<std::string, NBT*>::iterator iter = m_value.compoundVal->begin(), end = m_value.compoundVal->end();
      for (; iter != end; iter++)
      {
        iter->second->Dump(data, iter->first, tabs + 1);
      }
    }
    break;
  default:
    data += tabPrefix + "Invalid TAG:" + dtos(m_type) + "\n";
  }
}

