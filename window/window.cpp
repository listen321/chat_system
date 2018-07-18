#include "window.h"

window::window()
{
    initscr();
    curs_set(0);  
}

void window::drawtitle()
{
     int x = 0;
	 int y = 0;
	 int width = 0;
	 int hight = LINES/5;
	 title = newwin(hight, width, y, x);
	 box(title, 0, 0);
	 wrefresh(title);
}
void window::drawoutput()
{ 
     int x = 0;
	 int y = LINES/5;
	 int width = (COLS*3)/5;
	 int hight = (LINES*3)/5;
	 output = newwin(hight, width, y, x);
	 box(output, 0, 0);
	 wrefresh(output);	  
}
void window::drawinput()
{
     int x = 0;
	 int y = (LINES*4)/5;
	 int width = 0;
	 int hight = (LINES)/5;
	 input = newwin(hight, width, y, x);
	 box(input, 0, 0);
	 wrefresh(input);	  
}
void window::drawfriendlist()
{ 
     int x = (COLS*3)/5;
	 int y = (LINES)/5;
	 int width = 0;
	 int hight = (LINES*3)/5;
	 friendlist = newwin(hight, width, y, x);
	 box(friendlist, 0, 0);
	 wrefresh(friendlist);	  
}
void window::mvtitle(const string& str)
{
    int x = 0;
    int y = 0;
    getmaxyx(title, y, x);	
    int i = 1;
	
	while(1)
   {
		mvwaddstr(title, y/2, i++, str.c_str());
		if( i >= (x - str.length()) )
		{
             i = 1;
		}
		box(title, 0, 0);
		wrefresh(title);
		usleep(300000);
		clear_line_win(title, y/2, i-1);
   }
}
void window:: clear_line_win(WINDOW* w, int y, int x)
{
	   wmove(w, y, x);
	   wclrtoeol(w);
	   box(w, 0, 0);
	   wrefresh(w);
  //	wclear(w);	
}
void window:: str_to_input_win(string& s)
{      
    int x = 0;
    int y = 0;
	int i = 1;
	char buf[SIZE] = { 0 };
	string str = "Please Entry# ";
    getmaxyx(input, y, x);
    int k = 0;
    int t = 0;	
	mvwaddstr(input, y/2, 3, str.c_str());
	box(input, 0, 0);
	wrefresh(input);
	wgetnstr(input, buf, sizeof(buf));
	s = buf;
	clear_line_win(input, y/2, 3);
}
void window::clear_output_win()
{
     wclear(output);
     box(output, 0, 0);
	 wrefresh(output);
}
void window::clear_friendlist_win()
{
	wclear(friendlist);
	box(friendlist, 0, 0);
	wrefresh(friendlist);
}
void window:: str_to_output_win(string str, int nums)
{ 
     int x = 0;
	 int y = 0;
	 getmaxyx(output, y, x);
     mvwaddstr(output, nums, 1, str.c_str());
	 box(output, 0, 0);
     wrefresh(output);
}
void window:: str_to_friendlist_win(string str, int nums)
{
	mvwaddstr(friendlist, nums, 1, str.c_str());
	box(friendlist, 0, 0);
	wrefresh(friendlist);
}
void window::get_output_xy(int& x, int& y)
{
	getmaxyx(output, y, x);
}
window::~window()
{
    delwin(title);
    delwin(output);
    delwin(input);
    delwin(friendlist);
    curs_set(1);
	endwin();
}


