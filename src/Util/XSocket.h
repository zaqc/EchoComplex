/*
 * XSocket.h
 *
 *  Created on: Jan 9, 2015
 *      Author: zaqc
 */

#ifndef UTIL_XSOCKET_H_
#define UTIL_XSOCKET_H_
//----------------------------------------------------------------------------

#include "XThread.h"
//----------------------------------------------------------------------------

#define SOCK_FLAG_MASK		0xFFFF0000
#define SOCK_REQ_RESP_MASK	0x0000FFFF

#define SOCK_MESSAGE_FLAG	0xA15C0000
#define SOCK_REQ_FLAG		0xB2A30000
#define SOCK_RESP_FLAG		0xD4590000
#define SOCK_DATA_FLAG		0xE8A60000

#define SOCK_SERVER_STATE	0x00001234
//----------------------------------------------------------------------------

namespace usm {

class XSocket {
protected:
	int m_Socket;
public:
	XSocket();
	XSocket(int aSocket);
	virtual ~XSocket();

	void InitSocket(void);

	void WriteBuf(char *aBuf, int aSize);
	void WriteInt(int aVal);
	void ReadBuf(char *aBuf, int aSize);
	int ReadInt(void);
};
//----------------------------------------------------------------------------

} /* namespace usm */

#endif /* UTIL_XSOCKET_H_ */
