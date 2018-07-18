#ifndef __DATA_H__
#define __DATA_H__
#include <iostream>
#include <string>
#include "base_json.h"
using namespace std;

struct  data
{
	void serialize(string& outstr);
	void deserialize(string& instr);
	string NickName;
	string school;
    string msg;
	string cmd;
    myjson mj;	
};


#endif 
