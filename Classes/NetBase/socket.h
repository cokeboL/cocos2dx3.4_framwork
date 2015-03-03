#ifndef __CCNET_SOCKET_H__
#define __CCNET_SOCKET_H__

#include "inetaddress.h"


class CSocket
{
public:
	CSocket();

	virtual ~CSocket();

public:

	bool Listen();

	bool Create();

	void Close();

	void Disconnect();


	bool Connect(const char* pIp, unsigned short uPort);

	bool Connect(unsigned int uIp, unsigned short uPort);

	bool Bind(const char* pIp, unsigned short uPort);

	bool Bind(unsigned int uIp, unsigned short uPort);


	int	Read(char* pBuffer, int nLen);

	int	Write(char* pBuffer, int nLen);

public:
	bool IsReadable();

	bool IsWritable();

	int	IsConnected();

	bool IsAcceptable();

protected:

	SOCKET	m_Socket;
};

#endif // _SOCKET_INCLUDE_