#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
typedef struct node{
	int x;
	int y;
}node;

int evalue(node *queens,int loc){
	int i,score = 0;
	for(i = 0;i < 8;i++){
		if(i != loc){
			if(queens[loc].x == queens[i].x || queens[loc].y == queens[i].y){
				score+=1;
			}
			else if(abs(queens[loc].x - queens[i].x) == abs(queens[loc].y - queens[i].y)){
				score+=1;
			}
		}
		else continue;	
	}
	return score;
}

void queens8(node *queens){
	int board[8][8];
	int loop = 50, score, i, j, y;
	int mini_score, mini_loc, current_score,oriy,total,max,max_loc;
	srand(1);
	for(i = 0;i < 8;i++){
		for(j = 0;j < 8;j++){
			board[i][j] = 0;
		}
	}
	for(i = 0;i < 8;i++){
		board[queens[i].x][queens[i].y] = -1;
	}
	while(1){
		while(loop > 0){
			for(i = 0,score = 0;i<8;i++){
				score += evalue(queens,i);
			}	
			max = 0;			
			if(score != 0){
				for(total = 0 ,i = 0;i < 8;i++){
					total = evalue(queens,i);
					if(total > max){
						max = total;
						max_loc = i;
					}
				}		
				oriy = queens[max_loc].y;
				for(mini_score = 100, y = 0;y < 8;y++){
					if(board[max_loc][y]==0){
						queens[max_loc].y = y;
						current_score = evalue(queens,max_loc);
						if(current_score < mini_score){
							mini_score = current_score;
							mini_loc = y;
						}
						else if(current_score == mini_score){
							if(rand()%4 == 1){
								mini_loc = y;
							}
						}
					}
					else continue;
				}		
				board[max_loc][mini_loc] = -1;
				board[max_loc][oriy] = 0;
				queens[max_loc].y = mini_loc;
			}
			else break;
			loop--;
		}
		if(score == 0) break;
		loop = 50;
		for(i = 0;i < 8;i++){
			for(j = 0;j < 8;j++){
				board[i][j] = 0;
			}
		}
		for(i = 0;i < 8;i++){
			queens[i].y = rand()%8;
			board[queens[i].x][queens[i].y] = -1;	
		}
		//cout<<"next loop"<<endl;
	}
	for(i = 0;i < 8;i++){
		cout<<"x = "<<queens[i].x<<" y = "<<queens[i].y<<endl;
	}
}

int main(){
	int i;
	node queens[8];
	cout<<"input the location of each queen"<<endl;
	for(i = 0;i < 8;i++){
		cout<<"queen"<<i+1<<"x = "<<endl;
		cin>>queens[i].x;
		queens[i].x --;
		cout<<"queen"<<i+1<<"y = "<<endl;
		cin>>queens[i].y;
		queens[i].y--;
	}
	queens8(queens);
	return 0;
}
