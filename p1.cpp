#include <iostream>
#include"thread.h"
#include<vector>
#include<ifstream>
#include<string>

using namespace std;

struct Requester{
	int id;
	string name;
};

mutex mutex1;
//cv cv1;

vector <int> done;  // global variable; shared between the all threads.
//vector <Requester> rqs;
vector <int> waitQueue;

void sentRq(int track){
	waitQueue.push_back(track);
}

void requester(void *id)
{
	int * message = (int *) id;

	vector<int> input;
	ifstream fin;
	fin.open(argv[i+2]);
	while(line = fin.getline()){
		input.push_back(atoi(line));
	}
	fin.close();

	// enter critical section
	mutex1.lock();
	for (int i = 0; i < input.size(); i++)
	{
		sentRq(input[i]);
		cout << "requester " << id << " track " << input[i] << endl;
	}

	done[id] = 1;
	cv1.signal();
	mutex1.unlock();
}

void service(void *numRq)
{
	mutex1.lock();
	while (!child_done) {
	cout << "parent waiting for child to run\n";
	cv1.wait(mutex1);
	}
	cout << "parent finishing" << endl;
	mutex1.unlock();
}

int main(int argc, char* argv[])
{

	int numRq = argc - 2;
	
	// initialize the global record
	for (int i = 0; i < numRq; i++)
	{
		done.push_back(0);
	}

	// Trigger service's thread
	cpu::boot((thread_startfunc_t) service, (void *) numRq, 0);

	// Trigger requesters' threads
	ifstream fin;
	for(int i = 0; i < numRq; i++){
		Requester rq;
		rq.id = i;
		rq.name = (string)argv[i+2];
		//rqs.push_back(rq);
		thread requester_t ((thread_startfunc_t) requester, (void *) rq );
	}

	
	for (int i = 0; i < numRq; i++)
	{
		//join();
	}
	return 0;
}
