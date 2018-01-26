#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct node{
	int x;
	int y;
}node;

int hillclimb_TSP(node *location,int **map, int &city_num,int dest,int source){
	unsigned int total_cost = 10000,cost;
	int delta_cost;
	node current[city_num];
	int i,j,x,y,loop = 1000,pre;	
	srand(1);
	while(loop > 0){	
		for(i = 0,current[0].x = source,cost = 0;;){
			x = current[i].x;
			pre = 0;
			if(map[x][dest] == 100){
				while(1){
					y = rand()%city_num;
					if(map[x][y] < 100 && y != x && y != pre) break;
				}
				//cout<<y<<endl;
				cost += map[x][y];
				current[i].y = y;
				current[++i].x = y;	
				pre = x;
			}
			else break;
		}
		current[i].y = dest;
		cost += map[x][dest];
		delta_cost = total_cost - cost;
		if(delta_cost > 0 ){
			total_cost = cost;
			for(j = 0;j <= i;j++){
				location[j].x = current[j].x;
				location[j].y = current[j].y;
			}
		} 
		loop--;		
	}
	cout<<"path is "<<endl;
	for(j = 0; j<= i; j++){
		cout<<location[j].x+1 <<" --> ";
	}
	cout<<location[i].y+1<<endl;
	return total_cost;
} 

int main(){
	int city_num;
	int i,j;
	int cost,dest,source;
	cout<<"please input the number of cities"<<endl;
	cin>>city_num;
	cout<<"destination is "<<endl;
	cin>>dest;
	cout<<"source is "<<endl;
	cin>>source;
	node *location = new node[city_num];
	int **map = new int*[city_num];
	cout<<"please input the map"<<endl;
	for(i = 0; i< city_num; i++){
		map[i] = new int[city_num];
	}
	for(i = 0; i< city_num; i++){
		for(j = i;j < city_num;j++){
			cout<<"length between the city "<<i+1<<" and the city "<<j+1<<endl;
			cin>>map[i][j];
			map[j][i] = map[i][j];
		}	
	}
	for(i = 0;i < city_num;i++){
		for(j = 0;j < city_num;j++){
			cout <<map[i][j]<<" ";
		}
		cout<<endl;
	}
	cost = hillclimb_TSP(location,map,city_num,dest-1,source-1);
	cout<<endl<<"cost is "<<cost<<endl;
	return 0;
}
