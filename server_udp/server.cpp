#include "server.h"

Server::Server(const int port = 9999)
	:p(new data_pool(256)),_port(port),sock(-1)
{
}
const int Server::startup()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
	{
	   cerr<<"sock"<<endl;
	   return -1;
	
	}	
    struct sockaddr_in local;
	socklen_t len = sizeof(local);
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = htonl(INADDR_ANY); 
    if(bind(sock, (struct sockaddr*)&local, len) < 0)
	{
	   cerr<<"bind"<<endl;
	   return -2;
	}
	return sock;
}

int Server:: recv_msg(std::string& outstr, string& s_ip)
{
   char buf[SIZE];
   struct sockaddr_in client;
   socklen_t len = sizeof(client);
   memset(&client, 0x00, sizeof(client));
   ssize_t s = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&client, &len);
   
   if(s > 0)
   {
   	 buf[s] = 0;
	 outstr = buf;
	 string sip;
     char ip[40] = {0};
	 inet_ntop(AF_INET, &(client.sin_addr), ip,  sizeof(ip));
	 sip = ip;
	 s_ip = ip;
//	 cout<<"outstr::"<<outstr<<endl;
//     ssize_t s = sendto(sock, outstr.c_str(), outstr.length(), 0,\
//					 (struct sockaddr*)&client, sizeof(client));
//    cout<<"sock::"<<sock<<endl; 
//	 cout<<"recv::"<<s<<endl;
	 addusr(client, sip);	
   }
   return s; 
}
void Server:: addusr(struct sockaddr_in client, string sip)
{
//	 cout<<sip<<endl;
     usrlist.insert(pair<string, \
		struct sockaddr_in>(sip, client));    
}
void Server:: delusr(const string& s_ip)
{
     usrlist.erase(s_ip);
}
int Server:: send_msg(std::string & msg,struct sockaddr_in*& client)
{
	 char sp[40] = {0};
	 inet_ntop(AF_INET, &(client->sin_addr), sp, sizeof(sp));
	 string sip = sp;
	 cout<<sip<<":"<<client->sin_port<<": "<< msg<<endl;
     ssize_t s = sendto(sock, msg.c_str(), msg.length(),\
					 0, (struct sockaddr*)client, sizeof(*client));
    cout<<s<<endl;
	return s;
}
int Server:: reliable_recv(string& ip, string& str)
{
	
	std::string outstr;
    int s = recv_msg(outstr, ip);
	if(s > 0)
	{
		str = outstr;
		p->put_str(outstr);
	}
}
int Server:: reliable_send(std::string &msg, struct sockaddr_in* client)
{
		
	return send_msg(msg, client);

}
int Server:: broadcast_send()
{
		std::string str;
		p->get_str(str);
		map<string, struct sockaddr_in>::iterator it = usrlist.begin();		
		while(it != usrlist.end())
		{
	       reliable_send(str, &(*it).second); 
	   	   it++;	
		}
}
void Server:: broadcast_quitOronline( string& s)
{
		map<string, struct sockaddr_in>::iterator it = usrlist.begin();	
		while(it != usrlist.end())
		{
	       reliable_send(s, &(*it).second); 
	   	   it++;	
		}
}
bool Server:: usrexist(const string& s_ip)
{
     return (usrlist.end() != usrlist.find(s_ip));
}
Server::~Server()
{
     if(sock != -1)
	 {
	 	close(sock);
	 }
}


