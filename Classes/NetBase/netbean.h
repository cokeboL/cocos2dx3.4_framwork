
#ifndef __CCNET_NETBEAN_H__
#define __CCNET_NETBEAN_H__

#include "socket.h"
#include "stream.h"
#include "CCLuaEngine.h"
#include "ThreadSafeQueue.h"

USING_NS_CC;

typedef CStream STREAM;
#define SOCK_CONNECT_TIMEOUT 5
#define SOCK_RECVBUFFERSIZE (1024 * 8)
#define SOCK_SENDBUFFERSIZE (1024 * 2)
#define CLIP_PACKET 1

#define pack_head_bytes 16
#define pack_len_bytes 4
#define pack_flag_bytes 1


#define DEFINE_SINGLE_FUNCTION(__TYPE__) \
static __TYPE__* sharedNetBean() { \
static __TYPE__ *pInstance = NULL; \
if(pInstance == NULL){ \
	pInstance = new __TYPE__(); \
} \
return pInstance; \
}

#if 0
struct MessageHead
{
    enum Limits
    {
        MaxCommand = 255,		//最大命令
        MaxAction = 255,		//最大活动
    };

    enum MessageFlags
    {
        FlagEncrypt = 0x0001,   	//后面的数据是经过加密的
        FlagCompress = 0x0002, 		//后面的数据是经过压缩的
    };

    uint32_t    len = 0;		//数据长度
    uint32_t    error = 0;		//错误码
    uint8_t     cmd = 0;		//命令，原样返回客户端
    uint8_t     action = 0;		//活动，原样返回客户端
    uint8_t    	flags = 0;		//标记
    uint8_t    	option = 0;		//客户端填0
    uint32_t    time = 0;      		//时间戳，防重放与处理客户端延迟，原样返回客户端
};
#endif

//message
class TMessage{
public:
	enum Limits
    {
        MaxCommand = 255,
        MaxAction = 255,
    };

    enum MessageFlags
    {
        FlagEncrypt = 0x0001,
        FlagCompress = 0x0002,
    };

	TMessage(uint32_t len_, uint32_t error_, uint8_t cmd_, uint8_t action_, uint8_t flags_, uint8_t option_, uint32_t time_, char *content): 
		len(len_),
		error(error_), 
		cmd(cmd_),
		action(action_),
		flags(flags_),
		option(option_),
		time(time_),
		message(NULL)
	{
		if(len > 0)
		{
			message = new char[len];
			memcpy(message, content, len);
		}
	}
	TMessage(const TMessage &m): 
		len(m.len),
		error(m.error),
		cmd(m.cmd),
		action(m.action),
		flags(m.flags),
		option(m.option),
		time(m.time),
		message(NULL)
	{
		if(m.len > 0)
		{
			message = new char[m.len];
			memcpy(message, m.message, m.len);
		}
	}
	~TMessage()
	{
		if(message)
		{
			delete [] message;
		}
	}
	
	uint32_t    len;		//数据长度
    uint32_t    error;		//错误码
    uint8_t     cmd;		//命令，原样返回客户端
    uint8_t     action;		//活动，原样返回客户端
    uint8_t    	flags;		//标记
    uint8_t    	option;		//客户端填0
    uint32_t    time;      		//时间戳，防重放与处理客户端延迟，原样返回客户端
	char *message;
};


class CNetBean: public Node
{
public:
	CNetBean();
	
	virtual ~CNetBean();

	//void setAddress(const char* ip, unsigned short port);

	virtual bool connect(const char* ip, unsigned short port);
	
	virtual bool isConnected();
	
	virtual void close();

	virtual int write(char*, uint16_t);
	
	virtual void release();
	
	virtual void onCreate(){};
	
	virtual void onConnected(){};
	
	virtual void onDisconnected(){};
	
	virtual void onConnectError(){};
	
	virtual void onConnectTimeout(){};
	
	void read(char* buff, int len);

private:
	bool parseMessage();

protected:
	
	enum {
		ENULL			= 1,	
		EConnecting		= 2,	
		EConnected		= 3,	
		EConnectTimeout = 4,	
		EConnectError	= 5,	
		EDisconnected	= 6		
	} 
	m_nConnectStatus;

	struct timeval m_ccConnectTime;

protected:
	
	char m_RecvBuffer[SOCK_RECVBUFFERSIZE];
	char m_SendBuffer[SOCK_SENDBUFFERSIZE];

	deque<uint8_t> m_vFrameDecodeBuffer;
	ThreadSafeQueue<uint8_t> m_vSendBuffer;
	
	uint32_t m_nRecvPackLength;

protected:
	
	string m_nnAddress;
	
	unsigned short m_nnPort;

protected:
	
	CSocket	m_Sock;

protected:
	
	bool m_isRunning;

	std::mutex m_netMutex;

	ThreadSafeQueue<TMessage> m_MessageQueue;
};

#endif //__CCNET_NETBEAN_H__


