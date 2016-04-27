#include<iostream>
#include<pthread.h>
#include<algorithm>
#include<cmath>
#include<stdio.h>
#include<pthread.h>
#include<string>
#include <semaphore.h>
#define MAX_LOOP 10
using namespace std;

pthread_t threads[2];

int count_a, count_b, M, N;
class Sem{
	public:
		int sem;
		char name;
		Sem(int a, char n){ sem =a; name = n;}
		void P(){ 
			this->sem--;
			while(this->sem < 0);
		}
		void V(Sem* another){
			another->sem++;
		}
};

class Metux{
	public:
		int sem;
		Metux(int a){ sem = a;}
		void P(){
			sem--;
			while(this->sem <0);
		}
		void V(){
			sem++;
		}
};
class paraSem{
	public:
		Sem* self;
		Sem* another;
		Metux* metux;
		paraSem(Sem* a, Sem* b, Metux* m){
			self = a;
			another = b;
			metux = m;
		}
};
void* runable(void *pa){
	paraSem* temp = (paraSem*)pa;
	for(int i=0;;i++){
		temp->self->P();
		temp->metux->P();
		printf("Name:%c ----%d\n", (temp->self->name), temp->self->sem);
		temp->metux->V();
		temp->self->V(temp->another);	
	}
}
int main(){
	cin>>M>>N;
	Metux *metux = new Metux(1);
	Sem* sema = new Sem(N, 'a');
	Sem* semb = new Sem(M, 'b');
	paraSem* for_a = new paraSem(sema, semb, metux);
	paraSem* for_b = new paraSem(semb, sema, metux);
	pthread_create(&threads[0], NULL, runable, (void*)for_a);
	pthread_create(&threads[1], NULL, runable, (void*)for_b);
	for(int i=0;i<2;i++){
		pthread_join(threads[i], NULL);
	}
	return 0;
}
