/*
 * MessageThread.h
 *
 *  Created on: Dec 31, 2014
 *      Author: zaqc
 */

#ifndef UTIL_MESSAGETHREAD_H_
#define UTIL_MESSAGETHREAD_H_
//----------------------------------------------------------------------------

#include <deque>
#include <stdlib.h>

#include "XThread.h"
//----------------------------------------------------------------------------

namespace usm {

struct SocketMessage {
	int m_ID;
	int m_Size;
	char *m_Buf;
	SocketMessage() {
		m_ID = 0;
		m_Size = 0;
		m_Buf = NULL;
	}
};
//----------------------------------------------------------------------------

class MessageThread {
protected:
	XThread<MessageThread> m_Thread;
	XCondition m_Ready;
	XLock m_Lock;
	bool m_Running;
	std::deque<SocketMessage> m_MessageQueue;
public:
	MessageThread();
	virtual ~MessageThread();

	void Run(void);

	void PutMessage(const SocketMessage &aMsg);
	void ProcessMessage(const SocketMessage &aMsg);
};
//----------------------------------------------------------------------------

}
/* namespace usm */

#endif /* UTIL_MESSAGETHREAD_H_ */
