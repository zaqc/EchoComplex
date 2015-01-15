//============================================================================
// Name        : Tst.cpp
// Author      : Zaqc
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Util/MessageThread.h"
#include "Server/ServerThread.h"
#include "Client/ClientSocket.h"
#include "DataFile/DataFile.h"

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl;

	usm::DataFile df;

	usm::ServerThread st;
	st.StartServer();
	cout << "Server started..." << endl;

	usm::ClientSocket cs;
	cs.Connect((char*) "10.0.0.39", 17345);
	cs.SendRequest();

	getchar();

	cout << "go to stoping" << endl;
	st.StopServer();
	cout << "Server is stoped now..." << endl;

	return 0;
}
