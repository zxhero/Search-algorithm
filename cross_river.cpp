#include<iostream>
using namespace std;

void cross_river(int *time,int num,int &cost){
	if(num == 1){
		cout<<"Let 1st person pass the river"<<endl;
		cost += time[0];
	}
	if(num == 3){
		cout<<"Let 1st person and 2nd person pass the river, then 1st person comes back"<<endl;
		cost += (time[1] + time[0]);
		cout<<"Let 1st person and 3rd person pass the river"<<endl;
		cost += time[2];
	}
	else if(num == 2){
		cout<<"Let 1st person and 2nd person pass the river"<<endl;
		cost += time[1];
	}
	else if(2*time[1] < time[0] + time[num-2]){
		cout<<"Let 1st person and 2nd person pass the river, then 1st person comes back"<<endl;
		cost += (time[1] + time[0]);
		cout<<"Let "<<num-1<<" person and "<<num<<" person pass the river, then 2nd person comes back"<<endl;
		cost += (time[num-1] + time[1]);
		cross_river(time,num-2,cost);
	}
	else{
		cout<<"Let 1st person and "<<num<<" person pass the river, then 1st person comes back"<<endl;
		cost += (time[num-1] + time[0]);
		cout<<"Let 1st person and "<<num-1<<" person pass the river, then 1st person comes back"<<endl;
		cost += (time[num-2] + time[0]);
		cross_river(time,num-2,cost);
	}
}

int main(){
	int people_num,i,cost = 0;
	cin>>people_num;
	int *time = new int[people_num];
	for(i = 0; i < people_num; i++){
		cin>>time[i];
	}
	cross_river(time,people_num,cost);
	cout<<"Total time cost is "<<cost<<endl;
	return 0;
}
