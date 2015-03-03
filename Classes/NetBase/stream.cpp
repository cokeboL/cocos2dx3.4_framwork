#include <stdlib.h>
#include "stream.h"


#define STREAM_BUFFER_SIZE 4096


CStream::CStream()
{
	this->m_pData = NULL;
	this->m_nReadIdx = 0;
	this->m_Buffer.reserve(STREAM_BUFFER_SIZE);
}


CStream::CStream(char* buffer, int len)
{
	this->m_pData = NULL;
	this->m_nReadIdx = 0;
	this->m_Buffer.reserve(STREAM_BUFFER_SIZE);
	for(int i = 0; i < len; i++)
	{
		this->m_Buffer.push_back(buffer[i]);
	}
}


CStream::~CStream()
{
	if(m_pData != NULL)
	{
		delete m_pData;
	}

	if(!m_DeleteCharList.empty())
	{
		for(vector<char*>::iterator iter = m_DeleteCharList.begin(); iter != m_DeleteCharList.end(); iter++)
		{
			delete *iter;
		}
	}
}


int	CStream::size()
{
	return (this->m_Buffer.size());
}


char* CStream::flush()
{
	int nBufferSize = m_Buffer.size();
	if(nBufferSize != 0)
	{
		int nIdx = 0;
		this->m_pData = new char[nBufferSize];
		for(vector<char>::iterator iter = m_Buffer.begin(); iter != m_Buffer.end(); iter++, nIdx++)
		{
			this->m_pData[nIdx] = *iter;
		}
		return this->m_pData;
	}
	return NULL;
}


void CStream::writeShort(short num)
{
	this->m_Buffer.push_back( ((0xff00 & num) >> 8) );
	this->m_Buffer.push_back( (0xff & num) );
}


void CStream::writeInt(int num)
{
	this->m_Buffer.push_back( ((0xff000000 & num) >> 24) );
	this->m_Buffer.push_back( ((0xff0000 & num) >> 16) );
	this->m_Buffer.push_back( ((0xff00 & num) >> 8) );
	this->m_Buffer.push_back( (0xff & num) );
}


void CStream::writeByte(char ch)
{
	this->m_Buffer.push_back(ch);
}


void CStream::writeUTF(const char* str)
{
	int size = strlen(str);
	this->writeInt(size);
	for(int i = 0; i < size; i++){
		this->m_Buffer.push_back(str[i]);
	}
}


int	CStream::readInt()
{
	if( (m_nReadIdx + 3) < (int)m_Buffer.size())
	{
		int addr = m_Buffer[m_nReadIdx + 3] & 0xff;
		addr |= ((m_Buffer[m_nReadIdx + 2] << 8) & 0xff00);
		addr |= ((m_Buffer[m_nReadIdx + 1] << 16) & 0xff0000);
		addr |= ((m_Buffer[m_nReadIdx] << 24) & 0xff000000);

		m_nReadIdx += 4;
		return addr;
	}
	return 0;
}


short CStream::readShort()
{
	if( (m_nReadIdx + 1) < (int)m_Buffer.size())
	{
		short addr = m_Buffer[m_nReadIdx + 1] & 0xff;
		addr |= ((m_Buffer[m_nReadIdx] << 8) & 0xff00);

		m_nReadIdx += 2;
		return addr;
	}
	return 0;
}


char CStream::readByte()
{
	if( (m_nReadIdx) < (int)m_Buffer.size())
	{
		char addr = m_Buffer[m_nReadIdx];
		m_nReadIdx += 1;
		return addr;
	}
	return 0;
}


char* CStream::readUTF()
{
	if( (m_nReadIdx + 3) < (int)m_Buffer.size())
	{
		int size = m_Buffer[m_nReadIdx + 3] & 0xff;
		size |= ((m_Buffer[m_nReadIdx + 2] << 8) & 0xff00);
		size |= ((m_Buffer[m_nReadIdx + 1] << 16) & 0xff0000);
		size |= ((m_Buffer[m_nReadIdx] << 24) & 0xff000000);

		if( ( (m_nReadIdx + 4) + (size - 1)) < (int)m_Buffer.size() )
		{
			m_nReadIdx += 4;
			char* pUTF = new char[size + 1];
			for(int i = 0; i < size; i++, m_nReadIdx++)
			{
				pUTF[i] = m_Buffer[m_nReadIdx];
			}
			pUTF[size] = '\0';
			m_DeleteCharList.push_back(pUTF);
			return pUTF;
		}
	}
	return NULL;
}
