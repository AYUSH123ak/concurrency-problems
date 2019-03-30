#include<bits/stdc++.h>
using namespace std;

int x=0;
int s=50;
int m=0,st=1;
mutex mu;
void producer()
{
	string str;
	while(s>0){
		--s;
		while(m);
		mu.lock();
		m=1;
		st=0;
		str = "Item " + to_string(++x) + " produced\n";
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
		while(m||st);
		mu.lock();
		m=1;
		if(x==0)
			str = "Buffer empty\n";
		else
			str = "Item " + to_string(x--) + " consumed\n";
		m=0;
		cout << str;
		mu.unlock();
	}
}
signed main()
{
	thread t1(producer);
	thread t2(consumer);
	t1.join();
	t2.join();
}
