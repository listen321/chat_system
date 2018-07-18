#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>
using namespace std;
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <signal.h>
#define MAX 1024
class client
{
public:
     client(const string ip, int port);
     int startup();
	 int send_msg(const string& msg);
	 int recv_msg(string& msg);
     ~client();
private:	
    string _ip;
    unsigned short _port;
    int sock;	
};
#endif

