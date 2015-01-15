/*
 * ServerItem.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: zaqc
 */

#include "ServerItem.h"
#include "ServerThread.h"
#include "../Util/XThread.h"
#include "../Util/XSocket.h"
#include "../Util/MessageThread.h"
#include <memory.h>
#include <deque>
#include <iostream>
//----------------------------------------------------------------------------

namespace usm {

ServerItem::ServerItem(int aSocket, ServerThread *aServerThread) :
		XSocket(aSocket), m_Lock(), m_Thread(this,
				&ServerItem::ServerItemExecute), m_SocketMessageLock(), m_SocketMessageCond(), m_SocketMessage(), m_SenderLock(), m_MessageSenderThread(
				this, &ServerItem::MessageSenderThreadExecute) {
	m_Running = false;
	m_ServerThread = aServerThread;

	m_Lock.Lock();
	m_MessageSenderThread.Start();
	m_Thread.Start();
	m_Running = true;
	m_Lock.Unlock();
}
//----------------------------------------------------------------------------

ServerItem::~ServerItem() {
}
//----------------------------------------------------------------------------

void ServerItem::ServerItemExecute(void) {
	while (true) {
		m_Lock.Lock();
		bool running = m_Running;
		m_Lock.Unlock();
		if (!running)
			break;

		try {
			int id = ReadInt();
			int size = ReadInt();
			char *buf = NULL;
			if (size > 0) {
				buf = new char[size];
				ReadBuf(buf, size);
			}
			if ((id & SOCK_FLAG_MASK) == SOCK_REQ_FLAG)
				ProcessRequest(id, buf, size);
			delete[] buf;
		} catch (...) {
		}
	}
}
//----------------------------------------------------------------------------

void ServerItem::ProcessRequest(int aID, char *aBuf, int aSize) {
	switch (aID & 0xFFFF) {
	case SOCK_SERVER_STATE: {
		std::cout << std::endl << "---=== server state accepted ===---"
				<< std::endl;
		char *buf = (char*) "<root><config ext_sync=\"true\"></config></root>";
		int len = strlen(buf);
		m_SenderLock.Lock();
		WriteInt(SOCK_RESP_FLAG | SOCK_SERVER_STATE);
		WriteInt(len);
		WriteBuf(buf, len);
		m_SenderLock.Unlock();
		break;
	}
	}
}

void ServerItem::SendMessage(int aID, char *aBuf, int aSize) {
	SocketMessage msg;
	msg.m_ID = aID;
	msg.m_Size = aSize;
	msg.m_Buf = NULL;
	if (aSize > 0) {
		msg.m_Buf = new char[aSize];
		memcpy(msg.m_Buf, aBuf, aSize);
	}
	m_SocketMessageLock.Lock();
	m_SocketMessage.push_back(msg);
	if (m_SocketMessage.size() == 1)
		m_SocketMessageCond.Signal();
	m_SocketMessageLock.Unlock();
}
//----------------------------------------------------------------------------

void ServerItem::MessageSenderThreadExecute(void) {
	while (true) {
		SocketMessage sm;
		m_SocketMessageLock.Lock();
		if (0 == m_SocketMessage.size()) {
			if (0 != m_SocketMessageCond.WaitFor(m_SocketMessageLock)) {
				m_SocketMessageLock.Unlock();
				break;
			}
		}

		m_Lock.Lock();
		bool running = m_Running;
		m_Lock.Unlock();

		if (running && 0 != m_SocketMessage.size()) {
			sm = m_SocketMessage.front();
			m_SocketMessage.pop_front();
		} else {
			m_SocketMessageLock.Unlock();
			break;
		}

		m_SocketMessageLock.Unlock();

		m_SenderLock.Lock();
		WriteInt(sm.m_ID);
		WriteInt(sm.m_Size);
		if (sm.m_Size > 0)
			WriteBuf(sm.m_Buf, sm.m_Size);
		m_SenderLock.Unlock();

		if (0 != sm.m_Size && NULL != sm.m_Buf)
			delete[] sm.m_Buf;
	}
}
//----------------------------------------------------------------------------

} /* namespace usm */
