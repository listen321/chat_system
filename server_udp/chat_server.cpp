#include "server.h"

void useage(const char* us)
{
	cout<<"Usage:"<<us<<" port"<<endl;
}

void* recv_m(void* arg)
{
	
	Server *sv = (Server *)arg;
	data da;
	string sip;
	string str;
	string msg;
	bool flag = false;
	set<string> s;

	for(;;)
	{
	  	//	cout<<"recv_m"<<endl;
		sv->reliable_recv(sip, str);
		da.deserialize(str);
        if(da.cmd == "quit")
		{
		   //sv->broadcast_quitOronline(str);
		   sv->delusr(sip);
		   s.erase(sip);
		   continue;
		}
        flag = s.insert(sip).second;
		if(flag == true)
		{
			str="";
			da.msg = "Online";
			da.cmd = "Online";
            da.serialize(str);
			sv->broadcast_quitOronline(str);
			flag = false;
		}
	   

	}
}

void* broadc_m(void *arg)
{ 
	Server *sv = (Server *)arg;
    for(;;)
	{
	    //cout<<"aaaaa"<<endl;
	    sv->broadcast_send();
	}
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
	    useage(argv[0]);
		return 1;
	}
	Server sv(atoi(argv[1]));
    sv.startup();

    pthread_t re, br;
    pthread_create(&re, NULL, recv_m, (void*)&sv);
	pthread_create(&br, NULL, broadc_m, (void*)&sv);

	pthread_join(re, NULL);
	pthread_join(br, NULL);

    return 0;
}
