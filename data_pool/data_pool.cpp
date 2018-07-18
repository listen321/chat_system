#include "data_pool.h"


data_pool::data_pool(const int cap=100)
		:_cap(cap)
		 ,_start(0)
		 ,_end(0)
		 ,pool(100)
{
		sem_init(&full, 0, 0);
		sem_init(&empty, 0, 100);
}
void data_pool::get_str(string& outstr)
{
     sem_wait(&full);
	 outstr=pool[_start];
	 _start = (_start+1)%_cap;
	 sem_post(&empty);

}
void data_pool::put_str(const string& instr)
{
	sem_wait(&empty);
	pool[_end]=instr;
	_end = (_end+1)%_cap;
	sem_post(&full);
}
void data_pool:: show()
{
	cout<<"?????????"<<endl;
}
data_pool::~data_pool()
{
     sem_destroy(&full);
	 sem_destroy(&empty);
}


