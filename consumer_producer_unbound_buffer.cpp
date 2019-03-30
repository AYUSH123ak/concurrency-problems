#include<bits/stdc++.h>
using namespace std;

void semaphore_signal_produced();
void semaphore_signal_consumed();
void semaphore_wait();
void semaphore_wait_empty();


int last_item_produced=0;
int last_item_consumed=1;
int total=0;  // number of  items in buffer
int s=50;  // limited the output to 50 enteries 
mutex mu;  // for practical demostration of the running of program
int m=0;   // m is used to keep track of critical section 
void producer()
{
	string str;
	while(s>0){
		--s;
		semaphore_wait();
		mu.lock();
		
		str = "Item " + to_string(++last_item_produced) + " produced "+to_string(total+1)+ " items in buffer\n";
		cout << str;
		
		semaphore_signal_produced();
		mu.unlock();
	}
}
void consumer()
{
	string str;
	while(s>0){
		--s;
		semaphore_wait_empty();
		mu.lock();
		
		str = "Item " + to_string(last_item_consumed++) + " consumed "+to_string(total-1)+ " items in buffer\n";
		cout << str;
		
		semaphore_signal_consumed();
		mu.unlock();
	}
}
void semaphore_wait()
{
	while(m);
	m=1;
}
void semaphore_wait_empty()
{
	while(m||total==0);
	m=1;
}
void semaphore_signal_produced()
{
	m=0;
	total++;
}
void semaphore_signal_consumed()
{
	m=0;
	total--;
}
signed main()
{
	thread t1(producer);  // producer started
	thread t2(consumer);  // consumer started
	t1.join();
	t2.join();
}
