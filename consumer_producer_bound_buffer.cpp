#include<bits/stdc++.h>
using namespace std;

int last_item_produced=0;
int last_item_consumed=1;
int buffer_limit=5;
int to=0;  // number of  items in buffer
int s=50;  // limited the output to 50 enteries 
mutex mu;  // for practical demostration of the running of program
int m=0;   // m is used to keep track of critical section 
void producer()
{
	string str;
	while(s>0){
		--s;
		while(m);
		mu.lock();
		m=1;
		if(to==buffer_limit)
			str = "Buffer full "+to_string(to)+ " items in buffer\n";
		else{
			++to;
			str = "Item " + to_string(++last_item_produced) + " produced "+to_string(to)+ " items in buffer\n";
		}
		cout << str;
		m=0;
		mu.unlock();
	}
}
void consumer()
{
	string str;
	while(s>0){
		--s;
		while(m);
		mu.lock();
		m=1;
		if(last_item_consumed==last_item_produced+1)
			str = "Buffer empty 0 items in buffer\n";
		else{
			--to;
			str = "Item " + to_string(last_item_consumed++) + " consumed "+to_string(to)+ " items in buffer\n";
		}
		m=0;
		cout << str;
		mu.unlock();
	}
}
signed main()
{
	thread t1(producer);  // producer started
	thread t2(consumer);  // consumer started
	t1.join();
	t2.join();
}
