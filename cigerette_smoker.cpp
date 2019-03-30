#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
T rand() {
    return uniform_int_distribution<T>()(rng);
}
void semaphore_signal_smoker();
void semaphore_signal_agent(int i);
void semaphore_wait_smoker(int i);
void semaphore_wait_agent();

mutex mu;  // for practical demostration of the running of program
int item =  0;   // item  tells what item is currently on table 
int s=50;  // limited the output to 50 enteries 

void smoker(int i)
{
	while(s>0){
		--s;
		semaphore_wait_smoker(i);
		if(s==0)
			break;
		mu.lock();
		
		cout<<"Smoker "<<i<<" smoked the cigerette\n";
		
		semaphore_signal_smoker();
		mu.unlock();
	}
}
void agent()
{
	while(s>0){
		--s;
		semaphore_wait_agent();
		if(s==0)
			break;
		mu.lock();
		
		int it=rand<int>()%3+1;
		cout<<"Agent produced item "<<it<<"\n";

		semaphore_signal_agent(it);
		mu.unlock();
	}
}
void semaphore_wait_smoker(int i)
{
	while(item!=i&&s);
}
void semaphore_wait_agent()
{
	while(item!=0&&s);
}
void semaphore_signal_smoker()
{
	item = 0;
}
void semaphore_signal_agent(int i)
{
	item = i;
}
signed main()
{
	thread t1(smoker,1);  // smoker 1 started
	thread t2(smoker,2);  // smoker 2 started
	thread t3(smoker,3);  // smoker 3 started
	thread t4(agent);  // agent started
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
