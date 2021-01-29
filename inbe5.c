#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

 


 void right(int map[100][45]){
      for(int x=0;x<100;x++){
          if(map[x][43]==1){
              if(x+1>=99 || x+5>=99){
                  break;
              }

              
              map[x+1][43]=1;
              map[x][43]=0;
              break;
          }
      }
  }
  void left(int map[100][45]){
      for(int x=0;x<100;x++){
          if(map[x][43]==1){
              if(x-1<=0){
                  break;
              }
              map[x-1][43]=1;
              map[x][43]=0;
              break;
          }
      }
}

void right_enemy(int map[100][45]){
     		for(int y=45;y>=0;y--){
        		 for(int x=100;x>=0;x--){
                        if(map[x+1][y]==5&&map[x][y]==3){
                            map[x][y]=0;
                            map[x+1][y]=0;
                        }
             			else if(map[x][y]==3){
                	 	map[x+1][y]=3;
                	 	map[x][y]=0;
 
             			}
 				
         		}
 
     		}
 }
 
 void left_enemy(int map[100][45]){
     for(int y=0;y<=45;y++){
         for(int x=0;x<=100;x++){
            if(map[x-1][y]==5&&map[x][y]==3){
                map[x][y]=0;
                map[x-1][y]=0;
            }
            else if(map[x][y]==3){
                 map[x-1][y]=3;
                 map[x][y]=0;
 
             }
 
         }
 
     }
 
 }
 void down_enemy(int map[100][45]){
     for(int y=45;y>=0;y--){
         for(int x=100;x>=0;x--){
             if(map[x][y]==3){
                 map[x][y+1]=3;
                 map[x][y]=0;
 
             }
 
         }
 
     }
 }


int check_side_slid(int map[100][45]){
     for(int y=0;y<=45;y++){
         if(map[1][y]==3){
             return 0;//左側に敵がいたら
         }else if(map[96][y]==3){
             return 1;//右側に敵がいたら
         }
     }
     return 2;//左右どちらにもいない
 }

void shot(int map[100][45]){
     for(int x=0;x<=100;x++){
         if(map[x][43]==1){
             map[x][42]=5;
             break;
         }
     }
 }



void slid_shel2(int map[100][45],int x,int y){
     int y_save=y;
     int y_last=y-4;
     for(y=y-1;y>=y_last;y--){
         if(y-1<=1){
             map[x][y+1]=0;
        }else if(map[x][y]==3){
            map[x][y]=0;
            map[x][y_save]=0;
            break;
 
        }else{
            map[x][y]=5;
            map[x][y+1]=0;
       }
     }
} 
 
 
 void slid_shell(int map[40][45]){
      for(int y=0;y<=45;y++){
         for(int x=0;x<=100;x++){
             if(map[x][y]==5 ){
                 slid_shel2(map,x,y);
             }
         }
      }
 }


void maps(int field[100][45]){
          for(int x=0;x<100;x++){
                    for(int y=0;y<45;y++){
                            switch (field[x][y]){
            //                       case 0:
              //                             mvprintw(y+10,x+75," ");// 
                //                           break;
  
                                   case 1:	
                                           mvprintw(y+10,x+75,"|<@>|");//@
                                           break;
                                   case 2:
                                           mvprintw(y+10,x+75,"|");//|
                                           break;
                                   case 3:
                                           mvprintw(y+10,x+75,"<H>");//E
                                           break;
                                   case 4:
                                           mvprintw(y+10,x+75,"=");//|
                                           break;
					                case 5:
						                    mvprintw(y+10,x+75,"l");//l
						                    break;
					                case 6:
						                    mvprintw(y+10,x+75,"*");//l
						                    break;
                           }
 
                   }
 
           }
 
 
 }

int speed(int field[100][45]){
	int x,y,count;
	for(x=0;x<=100;x++){
		for(y=0;y<=45;y++){
			if(field[x][y]==3){
				count++;
			}		
		}
	}
	return count;	
}

void enemy_shell(int field[100][45]){
	int s;
	for(int x=100;x!=0;x--){
		for(int y=45;y!=0;y--){
			if(field[x][y]==3){
				s = rand()%50+1;
				if(s==2){
					field[x][y+1]=6;	
					break;

				}
                break;		
				
			}
		}
	}
}

void slide_enemy_shell(int field[100][45]){
    for(int x=100;x!=0;x--){
        for(int y=45;y!=0;y--){
            if(field[x][y]==6){
                field[x][y+1]=6;
                field[x][y]=0;	
            }
        }

    }
    for(int x=100;x!=0;x--){
        if(field[x][44]==6){
            field[x][44]=0;
        }
    }

}
int win_lose(int field[100][45]){
    int count=0;
    for(int x=100;x!=0;x--){
        for(int y=45;y!=0;y--){
            if(field[x][y]==3){
                count+=1;
            }
        }

    }
    if(count==0){
        return 1;
    }else{
        return 0;
    }
}




int main(void){
	
	srand(time(NULL));

	initscr();
	int 	map[100][45]={0};
	int flag=1; //0が左1が右

	
    for(int y=0;y<45;y++){
            map[0][y]=2;
    }
    for(int y=0;y<45;y++){
            map[99][y]=2;
    }
    for(int x=0;x<100;x++){
            map[x][44]=4;
    }
	for(int y=2;y<=20;y+=3){
        for(int x=2;x<=45;x+=4){
                    map[x][y]=3;
        }
    }
	map[50][43]=1;

	maps(map);	

	struct timeval _time;
	gettimeofday(&_time, NULL);
	long sec = _time.tv_sec;
	long time=_time.tv_sec;
	long usec = _time.tv_usec;
	long time_mil;
	int ch = getch();
	long time2,shell_mil;	
	timeout(75);
	while (true) {
		gettimeofday(&_time, NULL);
		sec = _time.tv_sec;
		usec = _time.tv_usec;
		time_mil = (int)usec*0.00001;
		shell_mil = (int)usec*0.001;
		
	//	time_shell = (int)usec*0.0001;
        if(win_lose(map)==1){
            break;

        }		
		
		if(time2!=shell_mil){
			 slid_shell(map);
			 time2 = shell_mil;
			 maps(map);
	
		}

		if(time_mil!=time){
			enemy_shell(map);
            slide_enemy_shell(map);
			time=sec;
			if(flag==1 && check_side_slid(map)==1){
			        down_enemy(map);
				flag=0;
			}else if(flag==1){
				 right_enemy(map);
		 	}else if(flag==0 && check_side_slid(map)==0){
				down_enemy(map);
			        flag=1;
			}else if(flag==0){
		        	left_enemy(map);
			}
			clear();
			maps(map);

		}
		ch = getch();
		
	    	if (ch == 'q'){ 
				break;
			}else if(ch=='d') {
				clear();
				right(map);
				maps(map);
			}else if(ch=='a'){
				clear();
				left(map);
				maps(map);
			}else if(ch=='w'){
				shot(map);
				maps(map);	
			}
		
  		
	}	
    clear();
    mvprintw(30,125,"win");//@
    timeout(10000);
    ch = getch();
  	endwin();

	
}