#include "socket.h"


CSocket::CSocket()
{
	m_Socket = INVALID_SOCKET;
}


CSocket::~CSocket()
{
	if(m_Socket != INVALID_SOCKET)
	{
		Close();
	}
}


bool CSocket::Create()
{
//choose socket version of win32
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif

	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_Socket == INVALID_SOCKET)
	{
		//LOG_ERROR("create socket fd failed");
		return false;
	}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	unsigned long ul = 1;
	int nRet = ioctlsocket(m_Socket, FIONBIO, (unsigned long*)&ul);
	if (nRet == SOCKET_ERROR)
	{
		Close();
		//LOG_ERROR("set non block failed");
		return false;
	}
#else
    int nFlags = fcntl(m_Socket, F_GETFL, 0);
    int nRet = fcntl(m_Socket, F_SETFL, nFlags | O_NONBLOCK);
	if (nRet == SOCKET_ERROR)
	{
		Close();
		//LOG_ERROR("set block failed");
		return false;
	}
#endif

	int nNoDelay = 1;
	if(setsockopt (m_Socket , IPPROTO_TCP , TCP_NODELAY , (char *)&nNoDelay , sizeof(nNoDelay)) == SOCKET_ERROR)
	{
		Close();
		//LOG_ERROR("set socket fd delay failed");
		return false;
	}

	return true;
}


bool CSocket::Connect(const char* pIp, unsigned short uPort)
{
	if(pIp == NULL)
	{
		return false;
	}
	else
	{
		return Connect(inet_addr(pIp), uPort);
	}
}


bool CSocket::Connect(unsigned int uIp, unsigned short uPort)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	CInetAddress oAddr;
	oAddr.SetIP(uIp);
	oAddr.SetPorT(uPort);
    
	int nRet = connect(m_Socket, oAddr, oAddr.GetLength());
	if(nRet == 0)
	{
		return true;
	}
	else
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		int nError = WSAGetLastError();
		if(nError ==  WSAEWOULDBLOCK)
		{
			return true;
		}
		else
		{
			return false;
		}
#else
		if(nRet == SOCKET_ERROR && errno == EINPROGRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
#endif
	}
}


bool CSocket::Bind(const char* pIp, unsigned short uPort)
{
	return Bind(inet_addr(pIp), uPort);
}


bool CSocket::Bind(unsigned int uIp, unsigned short uPort)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	CInetAddress oAddr;
	oAddr.SetIP(uIp);
	oAddr.SetPorT(uPort);

	return ::bind(m_Socket, oAddr, oAddr.GetLength()) == 0;
}


bool CSocket::Listen()
{
	if(m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	return listen(m_Socket, 5) == 0;
}


int CSocket::Read(char* pBuffer, int nLen)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}

	return recv(m_Socket, pBuffer, nLen, 0);
}


int CSocket::Write(char* pBuffer, int nLen)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}
#if ( (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) )
	return send(m_Socket, pBuffer, nLen, 0);
#else
    return send(m_Socket, pBuffer, nLen, SO_NOSIGPIPE);
#endif
}


void CSocket::Disconnect()
{
	if(m_Socket != INVALID_SOCKET)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		shutdown(m_Socket, SD_BOTH);
#else
        shutdown(m_Socket, SHUT_RDWR);
#endif
	}
}


void CSocket::Close()
{
	if(m_Socket != INVALID_SOCKET)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		closesocket(m_Socket);
#else
		close(m_Socket);
#endif
		m_Socket = INVALID_SOCKET;
	}
}


bool CSocket::IsReadable()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_Socket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if(select((int)(m_Socket + 1), &fd, NULL, NULL, &tv) > 0)
	{
		if(FD_ISSET(m_Socket, &fd))
		{
			return true;
		}
	}

	return false;
}


bool CSocket::IsWritable()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_Socket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if(select((int)(m_Socket + 1), NULL, &fd, NULL, &tv) >	0)
	{
		if(FD_ISSET(m_Socket, &fd))
		{
			return true;
		}
	}

	return false;
}


int CSocket::IsConnected()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_Socket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if(select((int)(m_Socket + 1), NULL, &fd, NULL, &tv) > 0)
	{
		if(FD_ISSET(m_Socket, &fd))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			return 1;
#else
			int error;
			socklen_t len = sizeof (error);
			if (getsockopt(m_Socket, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
			{
				return -1;
			}
			//LINUX ECONNREFUSED 111
			//UNIX ECONNREFUSED 61
			if(error == ECONNREFUSED)
			{
				return -1;
			}
			return 1;
#endif
		}
	}
	return 0;
}


bool CSocket::IsAcceptable()
{
	return IsReadable();
}
