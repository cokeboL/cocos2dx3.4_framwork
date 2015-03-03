#ifndef __CCNET_INETPREDEF_H__
#define __CCNET_INETPREDEF_H__

#include "cocos2d.h"
#include <stdio.h>
#include <stdlib.h>

#include <list>
#include <map>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//typedef int		SOCKET;
#else
	typedef void*	LPVOID;
	typedef int		SOCKET;
	typedef int		HANDLE;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#define INVALID_HANDLE	INVALID_HANDLE_VALUE
	#define	SD_BOTH	0x02
#else
	#define	INVALID_HANDLE			(-1)
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <errno.h>
	#include <sys/syscall.h>
    #include <fcntl.h>
    #include <netinet/tcp.h>
#endif



#endif // __CCNET_INETPREDEF_H__
