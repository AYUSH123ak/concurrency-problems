#include<bits/stdc++.h>
using namespace std;

void semaphore_signal_read();
void semaphore_signal_write();
void semaphore_wait_read();
void semaphore_wait_write();

mutex mu;  // for practical demostration of the running of program
int rd=0;   // rd is used to keep track of how many reader are reading 
int wrt=0; // wrt is used to keep track of whether any writer is writing or not
int s=50;  // limited the output to 50 enteries 

void reader(int i)
{
	while(s>0){
		--s;
		semaphore_wait_read();
		mu.lock();
		
		cout<<"Reader "<<i<<" reading\n";
		
		semaphore_signal_read();
		mu.unlock();
	}
}
void writer(int i)
{
	while(s>0){
		--s;
		semaphore_wait_write();
		mu.lock();
		
		cout<<"Writer "<<i<<" writing\n";
		
		semaphore_signal_write();
		mu.unlock();
	}
}
void semaphore_wait_read()
{
	while(wrt);
	rd++;
}
void semaphore_wait_write()
{
	while(rd);
	wrt=1;
}
void semaphore_signal_read()
{
	rd--;
}
void semaphore_signal_write()
{
	wrt=0;
}
signed main()
{
	thread t1(reader,1);  // reader started
	thread t4(writer,1);  // writer started
	thread t2(reader,2);  // reader started
	thread t5(writer,2);  // writer started
	thread t3(reader,3);  // reader started
	thread t6(writer,3);  // writer started
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}
