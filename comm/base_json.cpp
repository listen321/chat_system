#include "base_json.h"


int myjson:: val_str(string& outstr)
{
     Json::FastWriter fw;
	 outstr=fw.write(val);
	 return 0;
}
int myjson:: str_val(string& outstr)
{
	Json::Reader read;
	if(read.parse(outstr, val, false))
	{
		   return 0;
	}
     return 1;
}
