#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <pthread.h>

#define P_NUM 4
#define LOOP_NUM 4

using namespace std;
enum p_state{
	IDLE,
	WAITING,
	ACTIVE	
} flags[P_NUM];

int turn = 0;
pthread_t threads[P_NUM];

void* run(void* id){
	int pid = *(int*)id,index;
	cout<<"Proc "<<pid<<" start"<<endl;
	for(int i=0;i<LOOP_NUM; i++){
		while(true){
			//announce that we need the resource
			flags[pid]= WAITING;
			index = turn;
			/*
			scan all the process from the one with the turn up to ourselves
			repeat if necessary until the scan finds all are idle
			*/
			while(index!=pid){
				if(flags[index]!=IDLE) index = turn;
				else index++;
			}
			// claim the resource tentatively
			flags[i] = ACTIVE;
			//find all the first process active besides ourselves
			index = 0;
			while((index< P_NUM) &&(index == pid)||(flags[index]!= ACTIVE)){
				index ++;
			}
			if((index>=P_NUM)&&((turn==pid) || flags[turn] == IDLE)) break;
		}
		cout<<"ENTER "<<pid<<endl;
		// claim the turn and proceed
		turn= pid;
		cout<<"ENTER THE CRITICAL SECTION PID "<<pid<<endl;
		//exit 
		index = (pid+1) % P_NUM;
		while(flags[index] == IDLE){
			index = (index+1) % P_NUM;
		}
		turn = index;
		flags[pid] = IDLE;
		cout<<"EXIT "<<pid<<endl;
	}
}
int main(){
	int th_id[P_NUM];
	for(int i=0;i<P_NUM;i++){
		flags[i] = IDLE;
		th_id[i] = i;
	}
	cout<<"Test Begin:"<<endl;
	for(int i=0;i<P_NUM;i++){
		pthread_create(&threads[i], NULL, process, (void*)&th_id[i]);
	}
	for(int i=0;i<P_NUM;i++){
		pthread_join(thread[i],NULL);
	}
	return 0;
}
