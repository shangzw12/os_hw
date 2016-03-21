#include<iostream>
using namespace std;

#define WIN_SIZE 5 
#define _UN_USE 	1000
/* 
	if page missed; load page;
	only mark the recent win_size page
*/
class node{
	public:
		int node_num;
		node* pre;
		node* next;
};

class win_slide{
	private:
		node* crt;	//enter pointer
	public:
		win_slide(){
		node* all_node= new node[WIN_SIZE];
		for(int i=0;i<WIN_SIZE;i++){
			all_node[i].next = &all_node[(i+1)%WIN_SIZE];
			all_node[i].pre  = &all_node[(i+WIN_SIZE-1)%WIN_SIZE];
			all_node[(i+1)%WIN_SIZE].pre = &all_node[i];
			all_node[(i+WIN_SIZE-1)%WIN_SIZE].next = &all_node[i];
			all_node[i].node_num = _UN_USE;
		}
		this->crt = &all_node[0];
	}
		node* get_current(){ return this->crt; }
		void get_work_set(){
			int page_num[WIN_SIZE];
			node* current = get_current();
			for(int i=0;i<WIN_SIZE;i++){
				page_num[i] = current->node_num;
				current = current->next;
				bool already_have = false;
				for(int j=0; j<i;j++){
					if(page_num[j] == page_num[i]) already_have = true;
				}
				if(!already_have){
					if(page_num[i] != _UN_USE) cout<<page_num[i]<<' ';
				}
			}
		}
		void print_work_set(){
			cout<<"Work set Size is: "<<WIN_SIZE<<endl;
			cout<<"{ ";
			this->get_work_set();
			cout<<"}"<<endl;
		}
		void update(int new_num){
			this->crt->node_num = new_num;
			this->crt = this->crt->pre;
		}
};

int main(){
	win_slide *my_win = new win_slide();
	int temp_num = _UN_USE;
	while(true){
		cout<<"Input next page wanted: ";
		cin>>temp_num;
		my_win->update(temp_num);
		my_win->print_work_set();
	}
}