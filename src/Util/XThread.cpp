/*
 * XThread.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: zaqc
 */

#include <pthread.h>
#include "XThread.h"

namespace usm {

void * execute_class_method(void *aParam) {
	((BaseXThread*) aParam)->Run();
	pthread_exit(NULL);
	return NULL;
}
//----------------------------------------------------------------------------

//============================================================================
//	XLock
//============================================================================
XLock::XLock() {
	pthread_mutex_init(&m_Lock, NULL);
}
//----------------------------------------------------------------------------

XLock::~XLock() {
	pthread_mutex_destroy(&m_Lock);
}
//----------------------------------------------------------------------------

void XLock::Lock(void) {
	pthread_mutex_lock(&m_Lock);
}
//----------------------------------------------------------------------------

void XLock::Unlock(void) {
	pthread_mutex_unlock(&m_Lock);
}
//----------------------------------------------------------------------------

//============================================================================
//	XConditin
//============================================================================
XCondition::XCondition() {
	pthread_cond_init(&m_Cond, NULL);
}
//----------------------------------------------------------------------------

XCondition::~XCondition() {
	pthread_cond_destroy(&m_Cond);
}
//----------------------------------------------------------------------------

void XCondition::Signal(void) {
	pthread_cond_signal(&m_Cond);
}
//----------------------------------------------------------------------------

int XCondition::WaitFor(XLock &aLock) {
	return pthread_cond_wait(&m_Cond, aLock);
}
//----------------------------------------------------------------------------

} /* namespace usm */
