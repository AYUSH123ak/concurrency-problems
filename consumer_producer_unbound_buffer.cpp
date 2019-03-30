#include<bits/stdc++.h>
using namespace std;

int last_item_produced=0;
int last_item_consumed=1;
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
		str = "Item " + to_string(++last_item_produced) + " produced\n";
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
			str = "Buffer empty\n";
		else
			str = "Item " + to_string(last_item_consumed++) + " consumed\n";
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