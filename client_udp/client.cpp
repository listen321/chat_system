#include "client.h"


client::client(const string ip, int port)
		: _ip(ip)
		  ,_port(port)
		  ,sock(-1)
{
}

int client::startup()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);	
    if(sock < 0)
	{ 
	   return -1;
	}	
	return sock;
}

int client:: send_msg( const string& msg )
{
	struct sockaddr_in peer;
    socklen_t len = sizeof(peer);

	peer.sin_family = AF_INET;
	peer.sin_addr.s_addr = inet_addr(_ip.c_str());
	peer.sin_port = htons(_port);
    ssize_t s =	sendto(sock, msg.c_str(), msg.length(), 0, (struct sockaddr*)&peer, len);

//	cout<<msg<<"xxx"<<_ip<<":"<<_port<<endl;
    return s;
}
int client:: recv_msg(string& msg)
{
    struct sockaddr_in local;
    socklen_t len = sizeof(local);
    char buf[MAX];	
	ssize_t s = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&local, &len);
	if(s > 0)
    {
	   buf[s] = 0;
       msg = buf;
    }	   
    return s;   
}

client:: ~client()
{
    if(sock >= 0)
	{
		close(sock);
	}
}
