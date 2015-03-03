#include "netbean.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif


CNetBean::CNetBean():
m_nnPort(0),
m_nConnectStatus(ENULL),
m_isRunning(false),
m_nRecvPackLength(0)
{
}


CNetBean::~CNetBean()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Sleep(100);
#else
	usleep(100);
#endif
}

/*
void CNetBean::setAddress(const char* ip, unsigned short port)
{
	this->m_nnPort = port;
	this->m_nnAddress = ip;
}
*/

bool CNetBean::connect(const char* ip, unsigned short port)
{
	this->m_nnPort = port;

	if(ip[0] >= '0' && ip[0] <= '9')
	{
		this->m_nnAddress = ip;
	}
	else
	{
		struct hostent *host = gethostbyname(ip);
		
		if(host)
		{
			struct in_addr in;
			struct sockaddr_in addr;

			memcpy(&addr.sin_addr.s_addr, host->h_addr, 4);
			in.s_addr = addr.sin_addr.s_addr;
			this->m_nnAddress = std::string(inet_ntoa(in));
		}
	}

	
	//there is connected or connecting 
	if(this->m_nConnectStatus == EConnected || this->m_nConnectStatus == EConnecting){
		return false;
	}
	//validate value
	if(this->m_nnAddress == "" || this->m_nnPort == 0) {
		return false;
	}
	if(!m_Sock.Create()) {
		return false;
	}
	if(!m_Sock.Connect(this->m_nnAddress.c_str(), this->m_nnPort)) {
		return false;
	}
	//set the connecting status
	this->m_nConnectStatus = EConnecting;
	//get the connect time of started.
	gettimeofday(&m_ccConnectTime, NULL);
	//call back to virtual function 
	this->onCreate();

	return true;
}

bool CNetBean::isConnected()
{
	if(this->m_nConnectStatus == EConnected)
	{
		return true;
	}
	return false;
}

void CNetBean::close()
{
	m_netMutex.lock();
	this->m_Sock.Close();
	//this->m_nConnectStatus = EDisconnected;
	this->m_nConnectStatus = ENULL;
	this->m_vFrameDecodeBuffer.clear();
	this->m_nRecvPackLength = 0;
	m_netMutex.unlock();
}


void CNetBean::release()
{
	this->close();
	delete this;
}

//void CNetBean::write(CStream &stream)
int CNetBean::write(char* data, uint16_t length)
{
	//check status
	if( this->m_nConnectStatus != EConnected ) {
		//this->onDisconnected();
		return SOCKET_ERROR;
	}
	//check io is alive
	if( m_Sock.IsWritable() ) 
	{
		//pack length
		//int length = stream.size();
		//char* data = stream.flush();
		if( length != 0 ) {
			int nLen = m_Sock.Write( data, length );
			if( nLen == SOCKET_ERROR ) {
				//set the connecting status
				this->m_nConnectStatus = EDisconnected;
				//call back to virtual function
				this->close();
				this->onDisconnected();
				//log
				CCLOG("## [DEBUG] Write Disconnected if(nLen == SOCKET_ERROR)");
			}
			return nLen;
		}
		return 0;
	} 
	else 
	{
		CCLOG("## [DEBUG] Write Disconnected if( m_Sock.IsWritable() )");
		return SOCKET_ERROR;
	}
}

bool CNetBean::parseMessage()
{
	//check pack recv
	if(this->m_nRecvPackLength == 0) 
	{
		//read length of pack head
		if(this->m_vFrameDecodeBuffer.size() > pack_len_bytes) 
		{
			//read 4 char to int
			this->m_nRecvPackLength = 0;
			for(int i = 0; i < pack_len_bytes; i++) 
			{
				//this->m_nRecvPackLength <<= 8;
				this->m_nRecvPackLength |= (uint32_t((this->m_vFrameDecodeBuffer[0] & 0xff)) << (i*8));
				this->m_vFrameDecodeBuffer.pop_front();
			}
		} else {
			//there is no 4 bytes in buffer
			return false;
		}
	}
	int readable_size = this->m_vFrameDecodeBuffer.size();// - pack_len_bytes;
	//if readable
	if(readable_size >= (this->m_nRecvPackLength + pack_head_bytes - pack_len_bytes))
	{
		int len = this->m_nRecvPackLength;
		
		uint32_t error = 0;
		for(int i = 0; i < pack_len_bytes; i++) 
		{
			error |= (uint32_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
			this->m_vFrameDecodeBuffer.pop_front();
		}

		uint8_t cmd = (uint8_t)this->m_vFrameDecodeBuffer.front();
		this->m_vFrameDecodeBuffer.pop_front();

		uint8_t action = (uint8_t)this->m_vFrameDecodeBuffer.front();
		this->m_vFrameDecodeBuffer.pop_front();

		uint8_t flags = (uint8_t)this->m_vFrameDecodeBuffer.front();
		this->m_vFrameDecodeBuffer.pop_front();

		uint8_t option = (uint8_t)this->m_vFrameDecodeBuffer.front();
		this->m_vFrameDecodeBuffer.pop_front();

		uint32_t time = 0;
		for(int i = 0; i < pack_len_bytes; i++) 
		{
			time |= (uint32_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
			this->m_vFrameDecodeBuffer.pop_front();
		}

		char *message = new char[len];
		//read data from buffer
		for(int idx = 0; idx < len; idx++) 
		{
			message[idx] = this->m_vFrameDecodeBuffer.front();
			this->m_vFrameDecodeBuffer.pop_front();
		}
		
		this->m_nRecvPackLength = 0;


		this->m_MessageQueue.push_back(TMessage(len, error, cmd, action, flags, option, time, message));

		delete message;

		return true;
	}
	return false;
}

void CNetBean::read(char* buff, int len)
{
	for(int idx = 0; idx < len; idx++ ) {
		this->m_vFrameDecodeBuffer.push_back(m_RecvBuffer[idx]);
	}
	while(this->parseMessage());
}




