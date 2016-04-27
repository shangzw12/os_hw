#include<iostream>
#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#define MAX_LOOP 1000

using namespace std;
int Acount, Bcount;
int M, N;
sem_t A_left, B_left;
sem_t Metux;

bool check(){
	return (Acount - Bcount >=-M && Acount -Bcount <=N);
}
void print(){
	//cout<<"Acount: "<<Acount<<' '<<"Bcount: "<<Bcount<<" Minus"<<Acount-Bcount<<' '<<check()<<endl;
	if(Acount - Bcount >5) cout<<"YES"<<endl;
}
void* procA(void* ){
	for(int i=0;i<MAX_LOOP; i++){
		sem_wait(&A_left);
		sem_wait(&Metux);
		if(!check()){
			sem_post(&Metux);
			sem_post(&A_left);
			continue;
		}
		Acount++;
		print();
		sem_post(&Metux);
		sem_post(&B_left);
	}
	return NULL;
}
void* procB(void* ){
	for(int i=0;i<MAX_LOOP; i++){
		sem_wait(&B_left);
		sem_wait(&Metux);
		if(!check()){
			sem_post(&Metux);
			sem_post(&B_left);
			continue;
		}
		Bcount++;
		print();
		sem_post(&Metux);
		sem_post(&A_left);
	}
	return NULL;
}
int main(){
	cin>>M>>N;
	sem_init(&A_left,0, N);
	sem_init(&B_left,0, M);
	sem_init(&Metux, 0, 1);
	pthread_t threads[2];
	pthread_create(&threads[0], NULL, procA, NULL);
	pthread_create(&threads[1], NULL, procB, NULL);
	for(int i=0;i<2;i++)	{ pthread_join(threads[i], NULL);}
	return 0;
}