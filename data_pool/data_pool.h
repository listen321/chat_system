#ifndef __DATA_POOL_H__
#define __DATA_POOL_H__
#include <iostream>
using namespace std;
#include <string>
#include <stdlib.h>
#include <semaphore.h>
#include <vector>
class data_pool
{
public:
		data_pool(int cap);
		void get_str(string& outstr);
		void put_str(const string& instr);
        void show();
		~data_pool();
private:
		sem_t full;
		sem_t empty;
		vector<string> pool;
		int _cap;
		int _start;
		int _end;
};

#endif 
