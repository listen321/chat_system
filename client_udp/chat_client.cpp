#include "client.h"
#include "../window/window.h"
#include "../comm/data.h"
#include <set>
struct client_t 
{
  client_t(const string ip, int port)
		  :c(ip, port)
  {
  }
  client c;
  window w;
  data  da;
};

client_t *cl = NULL;
void usage(const char* us)
{
   cout<<"Usage:"<<us<<" ip port"<<endl;
}
void* headle_title(void* arg)
{
    client_t* ct = (client_t *)arg;
	ct->w.drawtitle();
    string st = "Welcome To Chat System";
	ct->w.mvtitle(st);
}

void* headle_output(void* arg)
{
    client_t* ct = (client_t *)arg;
	ct->w.drawoutput();
	ct->w.drawfriendlist();
	
    string rec;
    int i = 1;
	int x = 0;
	int y = 0;
	string s;
    ct->w.get_output_xy(x, y);
	string name = ct->da.NickName;
	string school = ct->da.school;


	data d;
	set<string> vs;
	string temp;
	string fr;
	while(1)
	{	
		s = "";
	    ct->c.recv_msg(rec);
		d.deserialize(rec);
		fr = "";
        fr += d.NickName;
		fr += "::";
		fr += d.school;
		vs.insert(fr);
		if(d.cmd == "Online")
		{
		    if(d.NickName == name && d.school == school)
			{
					continue;
			}
			d.msg = "     Online <---------- System";
		}
		else if(d.cmd == "quit")
		{
			vs.erase(fr);
		    ct->w.clear_friendlist_win();
		
		}

		s += d.NickName;
		s += "::";
		s += d.school;
		s += "# ";
		s += d.msg;

		ct->w.str_to_output_win(s, i++);
	   
	    set<string>::iterator it = vs.begin();

		int k = 1;
		while(it != vs.end())
		{
			ct->w.str_to_friendlist_win(*it, k++);
		    it++;
		}
	   

		if(i == y-1)
		{
		   sleep(1);
		   ct->w.clear_output_win();
		   i = 1;
		}
      

	}
}
void* headle_input(void* arg)
{
    client_t* ct = (client_t *)arg;
	ct->w.drawinput();
    string s;
    while(1)
	{
		ct->w.str_to_input_win(s);
	    ct->da.msg = s;
		string outstr;	
	    ct->da.serialize(outstr);
	    ct->c.send_msg(outstr);	
	}
}
void quit_handle(int signo) // ,siginfo_t *info, void* myact)
{	
   string s;
   window* win = &(cl->w);
   win->~window();
   cl->da.msg = "     quit now <---------- System";
   cl->da.cmd = "quit";
   s="";
   cl->da.serialize(s);
   cl->c.send_msg(s);
   exit(0); 
}	
int main(int argc, char* argv[])
{
	if(argc != 3)
	{
	   usage(argv[0]);
	   return 1;
	}
    
    string ne;
	string sl;
	cout<<"Please Entry NickName# ";
	cin>>ne;
	cout<<"Please Entry school# ";
	cin>>sl;
	client_t  client(argv[1], atoi(argv[2]));
	client.c.startup();
    client.da.NickName=ne;
	client.da.school = sl;
    cl = &client;
    struct sigaction act;
    act.sa_handler = quit_handle;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
//	act.sa_flags = SA_SIGINFO;
 	sigaction(SIGINT, &act, NULL); 
//    union sigval sal;
//    sal.sival_ptr = (void*)&client;
//    sigqueue(getpid(),SIGINT, sal);
	pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, headle_title, (void*)&client);
    pthread_create(&t2, NULL, headle_output, (void*)&client);
    pthread_create(&t3, NULL, headle_input, (void*)&client);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

//    for(;;)
//	{
//        string msg;
//		string rv;
//
//	  cout<<"Please Entry# ";
//	  string msg;
//	  string rv;
//	  cin>>msg;
//	  cl.send_msg(msg);
//	  cl.recv_msg(rv);
//	  cout<<"Server:"<<rv<<endl;
//	}

	return 0;
}
