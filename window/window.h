#ifndef __window_H__
#define __window_H__

#include <iostream>
using namespace std;
#include <string>
#include <ncurses.h>
#include <pthread.h>

#define SIZE 1024

class window
{
public:
	window();
    void mvtitle(const string& str);
    void str_to_input_win(string& s);	
    void str_to_output_win(string str, int nums);
	void get_output_xy(int& x, int& y);
	void clear_output_win();
    void drawtitle();
	void drawoutput();
	void drawinput();
	void drawfriendlist();
    void clear_friendlist_win();
	void str_to_friendlist_win(string str, int nums);
	~window();
private:
	void clear_line_win(WINDOW* w, int y, int x);
    WINDOW* title;
	WINDOW* output;
	WINDOW* input;
	WINDOW* friendlist;
};



#endif
