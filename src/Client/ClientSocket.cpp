/*
 * ClientSocket.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: zaqc
 */

#include "ClientSocket.h"
#include "../Util/XSocket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
//----------------------------------------------------------------------------

namespace usm {

ClientSocket::ClientSocket() :
		XSocket() {
}
//----------------------------------------------------------------------------

ClientSocket::~ClientSocket() {
}
//----------------------------------------------------------------------------

void ClientSocket::Connect(char *aAddr, int aPort) {

	InitSocket();

	sockaddr_in addr;
	bzero(&addr, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(aAddr);
	addr.sin_port = htons(17345);

	int res = connect(m_Socket, (sockaddr*) &addr, sizeof(sockaddr_in));
	std::cout << "Connecting to server (RESULT=" << res << ")" << std::endl;
}
//----------------------------------------------------------------------------

void ClientSocket::SendRequest(void) {
	WriteInt(SOCK_REQ_FLAG | SOCK_SERVER_STATE);
	WriteInt(0);

	int id = ReadInt();
	int size = ReadInt();
	char *buf = NULL;
	if(size > 0){
		buf = new char[size];
		ReadBuf(buf, size);
		std::cout << "RESPOONBSE: id=" << id << " size=" << size << " " << buf;
	}
}
//----------------------------------------------------------------------------

} /* namespace usm */
