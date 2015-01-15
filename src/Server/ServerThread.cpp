/*
 * ServerThread.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: zaqc
 */

#include "ServerThread.h"
#include "ServerItem.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
//----------------------------------------------------------------------------

namespace usm {

ServerThread::ServerThread() :
		m_ServerThread(this, &ServerThread::ServerThreadExecute), m_Lock(), m_ServerItemLock() {
	m_ServerSocket = -1;
	m_Running = false;
}
//----------------------------------------------------------------------------

ServerThread::~ServerThread() {
}
//----------------------------------------------------------------------------

void ServerThread::StartServer(void) {
	sockaddr_in addr;

	m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ServerSocket < 0)
		throw "Can't create server listener socket...";
	bzero((char*) &addr, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(17345);
	if (0 != bind(m_ServerSocket, (sockaddr*) &addr, sizeof(sockaddr_in)))
		throw "Can't bind main server socket...";
	if (0 != listen(m_ServerSocket, 5))
		throw "Can't listen main server socket...";

	m_Lock.Lock();
	m_ServerThread.Start();
	m_Running = true;
	m_Lock.Unlock();
}
//----------------------------------------------------------------------------

void ServerThread::StopServer() {
	m_ServerItemLock.Lock();
	m_Running = false;
	shutdown(m_ServerSocket, SHUT_RDWR);
	close(m_ServerSocket);
	m_ServerItemLock.Unlock();

	m_ServerThread.WaitFor();
}
//----------------------------------------------------------------------------

void ServerThread::ServerThreadExecute(void) {
	sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(sockaddr_in);
	while (true) {
		int client_sock = accept(m_ServerSocket, (sockaddr*) &client_addr,
				&client_addr_len);
		if (client_sock < 0) {
			break;
		}

		std::cout << "Client accepted (" << client_sock << ") from address="
				<< inet_ntoa(client_addr.sin_addr) << std::endl;

		m_Lock.Lock();
		bool running = m_Running;
		m_Lock.Unlock();

		if (!running)
			break;

		m_ServerItemLock.Lock();
		ServerItem *item = new ServerItem(client_sock, this);
		m_ServerItem.push_back(item);
		m_ServerItemLock.Unlock();
	}
}
//----------------------------------------------------------------------------

void ServerThread::Broadcast(int aID, char *aBuf, int aSize) {
	m_ServerItemLock.Lock();
	for (std::vector<ServerItem*>::iterator i = m_ServerItem.begin();
			i != m_ServerItem.end(); i++) {
		(*i)->SendMessage(aID, aBuf, aSize);
	}
	m_ServerItemLock.Unlock();
}
//----------------------------------------------------------------------------

} /* namespace usm */
