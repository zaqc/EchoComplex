/*
 * ServerThread.h
 *
 *  Created on: Jan 9, 2015
 *      Author: zaqc
 */

#ifndef SERVER_SERVERTHREAD_H_
#define SERVER_SERVERTHREAD_H_

#include "../Util/XSocket.h"
#include "../Util/XThread.h"
#include "ServerItem.h"
#include <vector>
//----------------------------------------------------------------------------

namespace usm {

class ServerThread {
private:
	int m_ServerSocket;
	XThread<ServerThread> m_ServerThread;
	XLock m_Lock;
	bool m_Running;
	XLock m_ServerItemLock;
	std::vector<ServerItem*> m_ServerItem;
public:
	ServerThread();
	virtual ~ServerThread();

	void StartServer(void);
	void StopServer(void);

	void ServerThreadExecute(void);

	void Broadcast(int aID, char *aBuf, int aSize);
};
//----------------------------------------------------------------------------

} /* namespace usm */

#endif /* SERVER_SERVERTHREAD_H_ */
