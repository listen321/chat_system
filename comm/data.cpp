#include "data.h"


void data:: serialize(string& outstr)
{ 
   mj.val["NickName"] = NickName;	
   mj.val["school"] = school;
   mj.val["msg"] = msg;
   mj.val["cmd"] = cmd;
   mj.val_str(outstr);
}
void data::deserialize(string& instr)
{
  if( mj.str_val(instr) == 0)
   {
	   NickName = mj.val["NickName"].asString();
	   school = mj.val["school"].asString();
	   msg = mj.val["msg"].asString();
	   cmd = mj.val["cmd"].asString();
   }
}
