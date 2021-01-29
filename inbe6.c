#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

 
 void title(){
     int  x, y, w, h;
	char *str = "Hello World";

	initscr();
	getmaxyx(stdscr, h, w);
	y = h/0.5;
	x = (w - strlen(str))/2;
    mvprintw(10,15,".M\"\"\"bgd                                           `7MMF'                                     `7MM");//@
    mvprintw(11,15,",MI    \"Y                                             MM                                         MM");//@
	mvprintw(12,15,"`MMb.     `7MMpdMAo.  ,6\"Yb.   ,p6\"bo   .gP\"Ya        MM  `7MMpMMMb.  `7M'   `MF' ,6\"Yb.    ,M\"\"bMM   .gP\"Ya  `7Mb,od8 ,pP\"Ybd");//@
    mvprintw(13,15," `YMMNq.   MM   `Wb 8)   MM  6M'  OO  ,M'   Yb        MM    MM    MM    VA   ,V  8)   MM  ,AP    MM  ,M'   Yb   MM' \"' 8I   `\"");//@
    mvprintw(14,15,".     `MM   MM    M8  ,pm9MM  8M       8M\"\"\"\"\"\"       MM    MM           VA ,V    ,pm9MM  8MI    MM  8M\"\"\"\"\"\"   MM     `YMMMa.");
    mvprintw(15,15,"Mb     dM   MM   ,AP 8M   MM  YM.    , YM.    ,       MM    MM    MM      VVV    8M   MM  `Mb    MM  YM.    ,   MM     L.   I8");
    mvprintw(16,15,"P\"Ybmmd\"    MMbmmd'  `Moo9^Yo. YMbmd'   `Mbmmd'     .JMML..JMML  JMML.     W     `Moo9^Yo. `Wbmd\"MML. `Mbmmd' .JMML.   M9mmmP'");
    mvprintw(17,15,"           MM                                                                                                                        ");
    mvprintw(18,15,"          .JMML.                                                                                                                  ");
    mvprintw(25,70,"Press anykey");
    
	getch();
    clear();

 }


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
                                   case 1:	
                                           mvprintw(y+10,x+75,"<@>");//@
                                           break;
                                   case 2:
                                           mvprintw(y+10,x+75,"|");//|
                                           break;
                                   case 3:
                                           mvprintw(y+10,x+75,"<H>");//E
                                           break;
                                   case 4:
                                           mvprintw(y+10,x+75," ");//|
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
    title();
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