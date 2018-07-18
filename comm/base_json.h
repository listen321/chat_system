#ifndef __BASE_JSON_H__
#define __BASE_JSON_H__

#include "json/json.h"
#include <iostream>
#include <string>
using namespace std;

class myjson
{
public:
	 int val_str(string& outstr);
	 int str_val(string& instr);
   	 Json::Value val;
};


#endif 
