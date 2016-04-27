#include<iostream>
#include<pthread.h>
#include<algorithm>
#include<cmath>
#include<stdio.h>
#include<pthread.h>
#define MAX_LOOP 10

using namespace std;

int num_a=0, num_b=1, M, N;
int global_sem = 1;
int T, Ta, Tb;
pthread_t threads[2];

bool check(){
	return (num_a - num_b>= -M && num_a - num_b <= N);
}

class sem{
	public:
		sem(int*, int);
		int* count;
		int id;
		void P();
		void V();
		void do_something();
};
sem::sem(int *num, int id){
	this->count = num;
	this->id = id;
}
void sem::P(){
	*(this->count)--;
	printf("Start %d \n", this->id);
	while(!check()){
		//DO nothing
	}
}
void sem::V(){
	printf("Exit %d \n", this->id);
	*(this->count)++;
}
void sem::do_something(){
	printf("DO %d \n", this->id);
}

void* runable(void* num){
	int* _num = (int*)num;
	int id = *(int*)num;
	*_num = 0;
	for(int i=0;;i++){
		sem* r_sem = new sem(_num, id);
		r_sem->P();
		r_sem->do_something();
		r_sem->V();
	}
}
int main(){
	cin>>M>>N;
	pthread_create(&threads[0], NULL, runable, (void*)&num_a);
	pthread_create(&threads[1], NULL, runable, (void*)&num_b);
	for(int i=0;i<2;i++){
		pthread_join(threads[i], NULL);
	}
	return 0;
}









