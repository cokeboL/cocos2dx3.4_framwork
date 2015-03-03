#ifndef __CCNET_STREAM_H__
#define __CCNET_STREAM_H__

#include <vector>
using namespace std;


class CStream
{
public:
	CStream();

	CStream(char* buffer, int len);

	~CStream();

public:
	void writeShort(short num);

	void writeInt(int num);

	void writeByte(char ch);

	void writeUTF(const char* str);

	char* flush();

public:
	int	readInt();

	short readShort();

	char readByte();

	char* readUTF();

public:
	int	size();

protected:
	char* m_pData;

	int	m_nReadIdx;

	vector<char> m_Buffer;

	vector<char*> m_DeleteCharList;
};


#endif
