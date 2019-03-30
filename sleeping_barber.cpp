#include<bits/stdc++.h>
using namespace std;

void semaphore_signal_barber();
void semaphore_signal_customer();
void semaphore_wait_barber();
void semaphore_wait_customer();

mutex mu;  // for practical demostration of the running of program
int m=0; 	// variable to ensure mutual exclusion
int limit=3; 	// variable to know the limit of seats
int cust=0; // cust is used to keep track of number of customers
int s=20;  // limited the output to 50 enteries 
int bar=0; // keeps track of whether barber is sleeping or not

void barber()
{
	while(s>0){
		--s;
		semaphore_wait_barber();
		if(s<0)
			break;
		mu.lock();

		cout<<"Barber complete cutting hair of a customer\n";
		
		semaphore_signal_barber();
		mu.unlock();
	}
}
void customer()
{
	while(s>0){
		--s;
		semaphore_wait_customer();
		if(s<=0)
			break;
		mu.lock();
		
		cout<<"Customer enters\n";
		
		semaphore_signal_customer();
		mu.unlock();
	}
}
void semaphore_wait_barber()
{
	while(cust==0&&s);
}
void semaphore_wait_customer()
{
	while(cust>=limit&&s);
}
void semaphore_signal_barber()
{
	--cust;
	if(cust==0){
		bar=0;
		cout<<"Barber sleeps\n";
	}
}
void semaphore_signal_customer()
{
	++cust;
	if(cust==1)
	{
		cout<<"Customer wakes barber up\n";
		bar=1;
	}
}
signed main()
{
	thread t1(barber);  // barber started
	thread t2(customer);  // customer started
	t1.join();
	t2.join();
}
