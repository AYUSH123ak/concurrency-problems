#include<bits/stdc++.h>
using namespace std;

void semaphore_signal(int i);
void semaphore_wait(int i);

mutex mu;  // for practical demostration of the running of program
int s=10;  // limited the output to 10 enteries 
int stick[5]={}; // keeps track of chopsticks in use

void philosopher(int i)
{
	while(s>0){
		--s;
		mu.lock();
		cout<<"philosopher "<<i+1<<" wishes to eat\n";
		mu.unlock();

		semaphore_wait(i);
		if(s<0)	
			break;

		mu.lock();

		stick[i]=1;
		stick[(i+1)%5]=1;
		cout<<"philosopher "<<i+1<<" is eating\n";

		mu.unlock();
		
		mu.lock();
		
		cout<<"philosopher "<<i+1<<" finished eating and now (s)he will think\n";
		semaphore_signal(i);
		
		mu.unlock();
		
	}
}
void semaphore_wait(int i)
{
	while(stick[i]==1||stick[(i+1)%5]==1);
}
void semaphore_signal(int i)
{
	stick[i]=0;
	stick[(i+1)%5]=0;
}
signed main()
{
	thread t1(philosopher,0);  // philosopher 1 started
	thread t2(philosopher,1);  // philosopher 2 started
	thread t3(philosopher,2);  // philosopher 3 started
	thread t4(philosopher,3);  // philosopher 4 started
	thread t5(philosopher,4);  // philosopher 5 started
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}
