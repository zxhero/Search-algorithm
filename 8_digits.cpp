#include<iostream>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#define up 1
#define down 2
#define left 3
#define right 4
using namespace std;
typedef struct state{
	int board[3][3];
	int value;
	int blank_x;
	int blank_y;
}state;

int schedule(int time){
	return time-1;
} 

int evalue(state *next){
	int i, j;
	int value = 0, num;
	for(i = 0;i < 3;i++){
		for(j = 0;j < 3;j++){
			num = next->board[i][j];
			//cout<<num<< " "<<i*3 + j +1<<endl;
			if(num != -1 && num != (i*3 + j +1)){
				value += (abs((num-1)%3 - j) + abs((num-1)/3 - i));
			}
		}
	}
	//cout<<"value = "<<value<<endl;
	return value;
}

void annealing_8_digits(state *initial){
	state *current,*next1,*next2,*next3,*next4,*real_next;
	int i,j,x ,y, flag, direct = 0, pos_direct;
	int T = 1000,deltaE,toll;
	current = initial;
	current->value = evalue(initial);
	while(1){
		T = schedule(T); 
		next1 = new state;
		next2 = new state;
		next3 = new state;
		next4 = new state;
		//cout<<T;
		if(T == 0 || current->value == 0) break;
		flag = 100;
		for(i = 0;i < 3;i++){
			for(j = 0;j < 3;j++){
				next1->board[i][j] = 0;
				next2->board[i][j] = 0;
				next3->board[i][j] = 0;
				next4->board[i][j] = 0;
			}
		}
		x = current->blank_x;
		y = current->blank_y;
		if((x-1)>=0 && direct != up){
			next1->blank_x = x-1;
			next1->blank_y = y;
			next1->board[x-1][y] = -1;
			next1->board[current->blank_x][current->blank_y] = current->board[x-1][y];
			for(i = 0;i < 3;i++){
				for(j = 0;j < 3;j++){
					if(next1->board[i][j] == 0) 
						next1->board[i][j] = current->board[i][j];
				}
			}
			next1->value = evalue(next1);
			flag = next1->value;
			real_next = next1;	
			pos_direct = down;
		}
		else delete next1;
		if((x+1)<3 && direct != down){
			next2->blank_x = x+1;
			next2->blank_y = y;
			next2->board[x+1][y] = -1;
			next2->board[current->blank_x][current->blank_y] = current->board[x+1][y];
			for(i = 0;i < 3;i++){
				for(j = 0;j < 3;j++){
					if(next2->board[i][j] == 0) 
						next2->board[i][j] = current->board[i][j];
				}
			}
			next2->value = evalue(next2);
			if(next2->value < flag){
				if(flag != 100) delete real_next;
				real_next = next2;
				flag = real_next->value;
				pos_direct = up;
			}
			else delete next2;
		}
		else delete next2;
		if((y-1)>=0 && direct != left){
			next3->blank_x = x;
			next3->blank_y = y-1;
			next3->board[x][y-1] = -1;
			next3->board[current->blank_x][current->blank_y] = current->board[x][y-1];
			for(i = 0;i < 3;i++){
				for(j = 0;j < 3;j++){
					if(next3->board[i][j] == 0) 
						next3->board[i][j] = current->board[i][j];
				}
			}
			next3->value = evalue(next3);
			if(next3->value < flag){
				if(flag != 100) delete real_next;
				real_next = next3;
				flag = real_next->value;
				pos_direct = right;
			}
			else delete next3;
		}
		else delete next3;
		if((y+1)<3 && direct != right){
			next4->blank_x = x;
			next4->blank_y = y+1;
			next4->board[x][y+1] = -1;
			next4->board[current->blank_x][current->blank_y] = current->board[x][y+1];
			for(i = 0;i < 3;i++){
				for(j = 0;j < 3;j++){
					if(next4->board[i][j] == 0) 
						next4->board[i][j] = current->board[i][j];
				}
			}
			next4->value = evalue(next4);
			if(next4->value < flag){
				if(flag != 100) delete real_next;
				real_next = next4;
				flag = real_next->value;
				pos_direct = left;
			}
			else delete next4;
		}
		else delete next4;		
		deltaE = current->value - real_next->value;
		if(deltaE > 0 || 1.0*rand()/RAND_MAX < exp(1.0*deltaE/T)){
			delete current;
			current = real_next;
			direct = pos_direct;
		}
		//¸üÐÂcurrent 
		cout<<"current state: "<<endl;
		for(i = 0;i < 3;i++){
			for(j = 0;j < 3;j++){
				cout<<current->board[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<"value = "<<current->value<<endl;
	}
	//output current
}

int main(){
	int i , j, num;
	state *initial = new state;
	srand((unsigned int)time(NULL));
	for(i = 0;i < 3;i++){
		cout<<"input "<<i+1<<" column"<<endl;
		for(j = 0;j < 3;j++){
			cin>>num;
			if(num == -1){
				initial->blank_x = i;
				initial->blank_y = j;
			}
			initial->board[i][j] = num;
		}
	}
	annealing_8_digits(initial);
	return 0;
}
