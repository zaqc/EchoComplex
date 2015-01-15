/*
 * ClientSocket.h
 *
 *  Created on: Jan 13, 2015
 *      Author: zaqc
 */

#ifndef CLIENT_CLIENTSOCKET_H_
#define CLIENT_CLIENTSOCKET_H_
//----------------------------------------------------------------------------

#include "../Util/XThread.h"
#include "../Util/XSocket.h"
//----------------------------------------------------------------------------

namespace usm {

class ClientSocket: public XSocket {
protected:
public:
	ClientSocket();
	virtual ~ClientSocket();

	void Connect(char *aAddr, int aPort);

	void SendRequest(void);
};
//----------------------------------------------------------------------------

} /* namespace usm */

#endif /* CLIENT_CLIENTSOCKET_H_ */
