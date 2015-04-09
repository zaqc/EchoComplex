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

#include <sqlite3.h>

#include <xercesc/util/PlatformUtils.hpp>

using namespace std;

int cb(void *a, int b, char **c, char **d) {

	for (int i = 0; i < b; i++) {
		cout << " c[i]=" << c[i] << " d[i]=" << d[i] << endl;
	}

	return 0;
}

using namespace xercesc;

int main() {

	sqlite3 *db;
	int res = sqlite3_open("/home/zaqc/mydb", &db);

	sqlite3_exec(db, "select name from Trip", &cb, NULL, NULL);

	cout << "!!!Hello World!!! res=" << res << endl;

	sqlite3_close(db);

	try {
		XMLPlatformUtils::Initialize();
	} catch (...) {
		return -1;
	}

	XMLPlatformUtils::Terminate();

	usm::DataFile df;

	usm::ServerThread st;
	st.StartServer();
	cout << "Server started..." << endl;

	usm::ClientSocket cs;
	cs.Connect((char*) "10.0.0.42", 17345);
	cs.SendRequest();

	getchar();

	cout << "go to stoping" << endl;
	st.StopServer();
	cout << "Server is stoped now..." << endl;

	return 0;
}
