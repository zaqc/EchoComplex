/*
 * ServerItem.h
 *
 *  Created on: Jan 9, 2015
 *      Author: zaqc
 */

#ifndef SERVER_SERVERITEM_H_
#define SERVER_SERVERITEM_H_
//----------------------------------------------------------------------------

#include "../Util/XThread.h"
#include "../Util/XSocket.h"
#include "../Util/MessageThread.h"
#include <deque>
//----------------------------------------------------------------------------

namespace usm {

class ServerThread;
//----------------------------------------------------------------------------

class ServerItem: public XSocket {
protected:
	ServerThread *m_ServerThread;

	bool m_Running;
	XLock m_Lock;
	XThread<ServerItem> m_Thread;
	XLock m_SocketMessageLock;
	XCondition m_SocketMessageCond;
	std::deque<SocketMessage> m_SocketMessage;
	XLock m_SenderLock;
	XThread<ServerItem> m_MessageSenderThread;
public:
	ServerItem(int aSocket, ServerThread *aServerThread);
	virtual ~ServerItem();

	void ServerItemExecute(void);
	void ProcessRequest(int aID, char *aBuf, int aSize);

	void MessageSenderThreadExecute(void);
	void SendMessage(int aID, char *aBuf, int aSize);
};
//----------------------------------------------------------------------------

} /* namespace usm */

#endif /* SERVER_SERVERITEM_H_ */
