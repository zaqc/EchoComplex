/*
 * BaseMessageThread.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: zaqc
 */

#include "XThread.h"
#include "MessageThread.h"
#include <pthread.h>
//----------------------------------------------------------------------------

namespace usm {

//============================================================================
//	MessageThread
//============================================================================
MessageThread::MessageThread() :
		m_Thread(this, &MessageThread::Run), m_Ready(), m_Lock() {
	m_Running = false;
	m_Lock.Lock();
	m_Thread.Start();
	m_Running = true;
	m_Lock.Unlock();
}
//----------------------------------------------------------------------------

MessageThread::~MessageThread() {
	m_Lock.Lock();
	m_Running = false;
	m_Ready.Signal();
	m_Lock.Unlock();
	m_Thread.WaitFor();
}
//----------------------------------------------------------------------------

void MessageThread::Run(void) {
	SocketMessage msg;
	while (true) {
		m_Lock.Lock();
		if (0 == m_MessageQueue.size()) {
			if (0 != m_Ready.WaitFor(m_Lock)) {
				m_Lock.Unlock();
				break;
			}
		}
		bool running = m_Running;
		if (running && 0 != m_MessageQueue.size()) {
			msg = m_MessageQueue.front();
			m_MessageQueue.pop_front();
		}
		m_Lock.Unlock();
		if (!running)
			break;

		ProcessMessage(msg);
		if (0 != msg.m_Size && NULL != msg.m_Buf)
			delete[] msg.m_Buf;
	}
}
//----------------------------------------------------------------------------

void MessageThread::PutMessage(const SocketMessage &aMsg) {
//	pthread_mutex_lock(&m_Lock);
//	m_MessageQueue.push_back(aMsg);
//	if (1 == m_MessageQueue.size()) {
//		pthread_cond_signal(&m_Ready);
//	}
//	pthread_mutex_unlock(&m_Lock);
}
//----------------------------------------------------------------------------

void MessageThread::ProcessMessage(const SocketMessage &aMsg) {
}
//----------------------------------------------------------------------------

} /* namespace usm */
