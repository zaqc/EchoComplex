/*
 * XSocket.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: zaqc
 */

#include "XSocket.h"
#include <sys/socket.h>
#include <sys/types.h>
//----------------------------------------------------------------------------

namespace usm {

XSocket::XSocket() {
	m_Socket = -1;
}
//----------------------------------------------------------------------------

XSocket::XSocket(int aSocket) {
	m_Socket = aSocket;
}
//----------------------------------------------------------------------------

XSocket::~XSocket() {
}
//----------------------------------------------------------------------------

void XSocket::InitSocket(void) {
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
}
//----------------------------------------------------------------------------

void XSocket::WriteBuf(char *aBuf, int aSize) {
	char *ptr = aBuf;
	while (ptr - aBuf < aSize) {
		int bs = send(m_Socket, aBuf, aSize - (ptr - aBuf), 0);
		if (bs <= 0)
			throw "Can't sent data to server...";
		ptr += bs;
	}
}
//----------------------------------------------------------------------------

void XSocket::WriteInt(int aVal) {
	WriteBuf((char*) &aVal, sizeof(int));
}
//----------------------------------------------------------------------------

void XSocket::ReadBuf(char *aBuf, int aSize) {
	char *ptr = aBuf;
	while (ptr - aBuf < aSize) {
		int br = recv(m_Socket, ptr, aSize - (ptr - aBuf), 0);
		if (br <= 0)
			throw "Can't read from Client Socket...";
		ptr += br;
	}
}
//----------------------------------------------------------------------------

int XSocket::ReadInt(void) {
	int res = 0;
	ReadBuf((char*) &res, sizeof(int));
	return res;
}
//----------------------------------------------------------------------------

} /* namespace usm */
