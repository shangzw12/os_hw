#include<iostream>
#include<cmath>
using namespace std;

class mission{
	float req_time;
	float last_time;
	float con_deadline;
	float deadline;
	bool is_finished;
	int sign;
	float wait_time;
	float response;
	float turnaround;
	public:
		mission(){ is_finished = false;}
		void set_mission(float a, float b, float c, int k){
			req_time = a; last_time = b; con_deadline = c;
			deadline = req_time + con_deadline;
			sign = k;
		}	
		void set_finished(){ is_finished = true; }
		float get_deadline(){ return deadline; }
		bool get_is_finished(){ return is_finished; }
		float get_req_time(){ return req_time; }
		float get_last_time(){ return last_time; }
		int get_sign(){ return sign; }
		void set_wait_time(float t){ wait_time = t; }
		float get_wait_time(){ return wait_time; }
		void set_response(float t) { response = t; } 
		float get_response() {return response; }
		void set_turnaround(float t){ turnaround = t; } 
		float get_turnaround() { return turnaround; }
};
mission* get_first_mission(mission a[], int n, int now){
	mission* choose = &(a[0]);
	for(int i = 1;i< n;i++){
		if(choose->get_is_finished() ||choose->get_req_time()> now || a[i].get_deadline() < choose->get_deadline()){
			if(!(a[i].get_is_finished()) && (a[i].get_req_time() <= now)){
				choose = &(a[i]);
			}
		}
		//cout<<choose->get_sign()<<endl;
	}
	if(choose->get_is_finished()){
		return NULL;
	}
	choose->set_finished();
	return choose;
}
int main(){
	int n;
	cin>>n;
	mission my_mission[n];
	float ta, tb,tc;
	for(int i =0 ; i<n;i++){
		cin>>ta>>tb>>tc;
		(my_mission[i]).set_mission(ta,tb,tc,i);
	}
	mission* curt;
	float now = 0;
	float t_res=0;
	float t_turn=0;
	float t_wait=0;
	cout<<"Execution trace: \n";
	while(curt = get_first_mission(my_mission,n, now)){
		cout<<"[ time "<<now<<" ]"<<"Run job "<<curt->get_sign();
		cout<<" for "<<curt->get_last_time()<<" sec"<<" ( Done at ";
		cout<<(now + curt->get_last_time())<<" )"<<endl;
		curt->set_response(now - curt->get_req_time());
		curt->set_turnaround( curt->get_last_time() + curt->get_response());
		curt->set_wait_time( now - curt->get_req_time());
		now += curt->get_last_time();
	}
	cout<<"Final statistics: \n";
	for(int i=0;i<n;i++){
		cout<<"Job  "<<i;
		cout<<" -- Response: "<<my_mission[i].get_response()<<" ";
		cout<<"Turnaround "<<my_mission[i].get_turnaround()<<" ";
		cout<<"Wait "<<my_mission[i].get_wait_time()<<endl;
		t_res += my_mission[i].get_response();
		t_turn +=my_mission[i].get_turnaround();
		t_wait +=my_mission[i].get_wait_time();
	}
	cout<<"Average -- Response: "<<t_res/n<<" Turnaround: "<<t_turn/n;
	cout<<" Wait "<<t_wait/n<<endl;
	return 0;
}
