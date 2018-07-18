
#ifndef __SERVER_H__
#define __SERVER_H__

#include "../data_pool/data_pool.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <map>
#include <set>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "window.h"
#include "data.h"
#include <iostream>
using namespace std;
#define SIZE 1024

class Server
{
public:
   Server(int port);
   const int  startup();
	int  reliable_recv(string& s_ip, string& str);
	int  reliable_send(std::string& msg, struct sockaddr_in* client);
    void  broadcast_quitOronline( string& s);
	int  broadcast_send(); 
    void delusr(const string& s_ip);	
    void addusr(struct sockaddr_in client, string sip);
	bool usrexist(const string& s_ip);
	~Server();	
private:
	unsigned short _port;
    int sock;
    map<std::string, struct sockaddr_in>  usrlist;
    int recv_msg(std::string& msg, string& s_ip);
    int send_msg(std::string& msg, struct sockaddr_in*& client);
    data_pool* p;	
};



#endif
