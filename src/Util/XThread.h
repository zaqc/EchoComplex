/*
 * XThread.h
 *
 *  Created on: Jan 7, 2015
 *      Author: zaqc
 */

#ifndef XTHREAD_H_
#define XTHREAD_H_
//----------------------------------------------------------------------------

#include <stdlib.h>
#include <pthread.h>
//----------------------------------------------------------------------------

namespace usm {

void * execute_class_method(void *aParam);
//----------------------------------------------------------------------------

class BaseXThread {
public:
	BaseXThread() {
	}
	virtual ~BaseXThread() {
	}
	virtual void Run(void) = 0;
};
//----------------------------------------------------------------------------

template<class ExecuteClass>
class XThread: public BaseXThread {
protected:
	ExecuteClass *m_ExecuteClass;
	void (ExecuteClass::*m_ExecuteMethod)(void);
public:
	pthread_t m_Thread;
	XThread(ExecuteClass *aExecuteClass,
			void (ExecuteClass::*aExecuteMethod)(void)) :
			BaseXThread() {
		m_ExecuteClass = aExecuteClass;
		m_ExecuteMethod = aExecuteMethod;
		m_Thread = -1;
	}

	virtual ~XThread() {
	}

	void Start(void) {
		int res = pthread_create(&m_Thread, NULL, &execute_class_method, this);
		if (res != 0) {
			throw "Can't create new thread...";
		}
	}

	void WaitFor(void) {
		pthread_join(m_Thread, NULL);
	}

	virtual void Run(void) {
		(m_ExecuteClass->*m_ExecuteMethod)();
	}
};
//----------------------------------------------------------------------------

template<typename ValType>
class XSafeVal {
protected:
	ValType m_Val;
	pthread_mutex_t m_Lock;
public:
	XSafeVal() {
		m_Val = false;
		pthread_mutex_init(&m_Lock, NULL);
	}

	virtual ~XSafeVal() {
		pthread_mutex_destroy(&m_Lock);
	}

	void Lock(void) {
		pthread_mutex_lock(&m_Lock);
	}

	void Unlock(void) {
		pthread_mutex_unlock(&m_Lock);
	}

	void operator =(const ValType &aVal) {
		Lock();
		m_Val = aVal;
		Unlock();
	}

	operator ValType() {
		Lock();
		ValType val = m_Val;
		Unlock();
		return val;
	}
};
//----------------------------------------------------------------------------

typedef pthread_mutex_t* ppthread_mutex_t;

class XLock {
protected:
	pthread_mutex_t m_Lock;
public:
	XLock();
	virtual ~XLock();

	operator ppthread_mutex_t() {
		return &m_Lock;
	}

	void Lock(void);
	void Unlock(void);
};
//----------------------------------------------------------------------------

class XCondition {
protected:
	pthread_cond_t m_Cond;
public:
	XCondition();
	virtual ~XCondition();
	void Signal(void);
	int WaitFor(XLock &aLock);
};
//----------------------------------------------------------------------------

}
/* namespace usm */

#endif /* XTHREAD_H_ */
