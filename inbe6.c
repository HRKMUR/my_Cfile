#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
 
void title(){
     int  x, y, w, h;
	char *str = "Hello World";

	initscr();
    
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    attrset(COLOR_PAIR(2));	
	getmaxyx(stdscr, h, w);
	y = h/0.5;
	x = (w - strlen(str))/2;
    mvprintw(10,40,".M\"\"\"bgd                                           `7MMF'                                     `7MM");//@
    mvprintw(11,40,",MI    \"Y                                             MM                                         MM");//@
	mvprintw(12,40,"`MMb.     `7MMpdMAo.  ,6\"Yb.   ,p6\"bo   .gP\"Ya        MM  `7MMpMMMb.  `7M'   `MF' ,6\"Yb.    ,M\"\"bMM   .gP\"Ya  `7Mb,od8 ,pP\"Ybd");//@
    mvprintw(13,40," `YMMNq.   MM   `Wb 8)   MM  6M'  OO  ,M'   Yb        MM    MM    MM    VA   ,V  8)   MM  ,AP    MM  ,M'   Yb   MM' \"' 8I   `\"");//@
    mvprintw(14,40,".     `MM   MM    M8  ,pm9MM  8M       8M\"\"\"\"\"\"       MM    MM    MM     VA ,V    ,pm9MM  8MI    MM  8M\"\"\"\"\"\"   MM     `YMMMa.");
    mvprintw(15,40,"Mb     dM   MM   ,AP 8M   MM  YM.    , YM.    ,       MM    MM    MM      VVV    8M   MM  `Mb    MM  YM.    ,   MM     L.   I8");
    mvprintw(16,40,"P\"Ybmmd\"    MMbmmd'  `Moo9^Yo. YMbmd'   `Mbmmd'     .JMML..JMML  JMML.     W     `Moo9^Yo. `Wbmd\"MML. `Mbmmd' .JMML.   M9mmmP'");
    mvprintw(17,40,"           MM                                                                                                                        ");
    mvprintw(18,40,"          .JMML.                                                                                                                  ");
    mvprintw(25,90,"Press anykey");
    
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



int slid_shel2(int map[100][45],int x,int y){
     int y_save=y;
     int y_last=y-4;
     int count=0;
     for(y=y-1;y>=y_last;y--){
         if(y-1<=1){
             map[x][y+1]=0;
        }else if(map[x][y]==3||map[x][y]==6){
            if(map[x][y]==3){
                count=100;
            }
            map[x][y]=0;
            map[x][y_save]=0;
            break;
 
        }else{
            map[x][y]=5;
            map[x][y+1]=0;
       }
     }
     return count;
} 
 
 
 int slid_shell(int map[40][45]){
    int count=0;
      for(int y=0;y<=45;y++){
         for(int x=0;x<=100;x++){
             if(map[x][y]==5 ){
                 count += slid_shel2(map,x,y);
             }
         }
      }
      return count;
 }


void maps(int field[100][45],int count){
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
          for(int x=0;x<100;x++){
                    for(int y=0;y<45;y++){
                            switch (field[x][y]){
                                   case 1:	    
                                            attrset(COLOR_PAIR(1));		
                                           mvprintw(y+10,x+75,"|<@>|");//@
                                           break;
                                   case 2:
                                            attrset(COLOR_PAIR(2));		
                                           mvprintw(y+10,x+75,"|");//|
                                           break;
                                   case 3:
                                            attrset(COLOR_PAIR(3));		
                                           mvprintw(y+10,x+75,"/H\\");//E
                                           break;
                                   case 4:
                                            attrset(COLOR_PAIR(2));		
                                           mvprintw(y+10,x+75,"=");//|
                                           break;
					                case 5:
                                            attrset(COLOR_PAIR(1));		
						                    mvprintw(y+10,x+75,"l");//l
						                    break;
					                case 6:
                                            attrset(COLOR_PAIR(3));		
						                    mvprintw(y+10,x+75,"*");//l
						                    break;
                           }
 
                   }
 
           }
        attrset(COLOR_PAIR(2));		
        mvprintw(10,25,"____HOW TO PLAY____");//l
        mvprintw(12,25,"[a]move to left");
        mvprintw(13,25,"[d]move to right");
        mvprintw(14,25,"[w]shot");
        mvprintw(15,25,"[q]quit from game ");
        mvprintw(16,25,"___________________");

        mvprintw(20,25,"_______SCORE_______");
        mvprintw(21,25,"|                 |");
        mvprintw(22,25,"      %d          ",count);
        mvprintw(23,25,"|_________________|");
        
       
        
        
 
 }
 void maps2(int field[100][45],int count){
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
          for(int x=0;x<100;x++){
                    for(int y=0;y<45;y++){
                            switch (field[x][y]){
                                   case 1:	    
                                            attrset(COLOR_PAIR(1));		
                                           mvprintw(y+10,x+75,"|<@>|");//@
                                           break;
                                   case 2:
                                            attrset(COLOR_PAIR(2));		
                                           mvprintw(y+10,x+75,"|");//|
                                           break;
                                   case 3:
                                            attrset(COLOR_PAIR(3));		
                                           mvprintw(y+10,x+75,"\\H/");//E
                                           break;
                                   case 4:
                                            attrset(COLOR_PAIR(2));		
                                           mvprintw(y+10,x+75,"=");//|
                                           break;
					                case 5:
                                            attrset(COLOR_PAIR(1));		
						                    mvprintw(y+10,x+75,"l");//l
						                    break;
					                case 6:
                                            attrset(COLOR_PAIR(3));		
						                    mvprintw(y+10,x+75,"*");//l
						                    break;
                           }
 
                   }
 
           }
        attrset(COLOR_PAIR(2));		
        mvprintw(10,25,"____HOW TO PLAY____");//l
        mvprintw(12,25,"[a]move to left");
        mvprintw(13,25,"[d]move to right");
        mvprintw(14,25,"[w]shot");
        mvprintw(15,25,"[q]quit from game ");
        mvprintw(16,25,"___________________");

        mvprintw(20,25,"_______SCORE_______");
        mvprintw(21,25,"|                 |");
        mvprintw(22,25,"      %d          ",count);
        mvprintw(23,25,"|_________________|");
        
       
        
        
 
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
				s = rand()%25+1;
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
int win(int field[100][45]){
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

int lose(int field[100][45]){
    for(int x=0;x<=100;x++){
        if(field[x][40]==3){
            return 1;
        }

    }
    return 0;
}

int lose2(int field[100][45]){
    int count=0;
    for(int x=0;x<=99;x++){
        if(field[x][43]==1){
            count++;
        }

    }
    if(count==0)return 1;
    return 0;
}




int main(void){
	
	srand(time(NULL));

	initscr();
    start_color();
    use_default_colors();
	int 	map[100][45]={0};
	int flag=1; //0が左1が右
    int flag_about_win_or_lose=0;
    int count=0;
	

	struct timeval _time;
	gettimeofday(&_time, NULL);
	long sec = _time.tv_sec;
	long time=_time.tv_sec;
	long usec = _time.tv_usec;
	long time_mil;
	long time2,shell_mil;	
    int pin=0;

	
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
	maps(map,count);	
    timeout(75);
    int ch =getch();
	while (true) {
		gettimeofday(&_time, NULL);
		sec = _time.tv_sec;
		usec = _time.tv_usec;
		time_mil = (int)usec*0.00001;
		shell_mil = (int)usec*0.001;
		
        if(lose(map)==1){
            flag_about_win_or_lose =1;
            break;
        }
        else if(win(map)==1){
            flag_about_win_or_lose =2;
            break;

        }else if(lose2(map)==1)	{
            flag_about_win_or_lose =1;
            break;
        }	
		
		if(time2!=shell_mil){
			 count += slid_shell(map);
			 time2 = shell_mil;
             if(pin==0)maps(map,count);
            else if(pin==1)maps2(map,count);
		}

		if(time_mil!=time){
			enemy_shell(map);
            slide_enemy_shell(map);
			time=sec;
            if(pin==1)pin=0;
            else if(pin==0)pin=1;
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
            if(pin==0)maps(map,count);
            else if(pin==1)maps2(map,count);

		}
		ch = getch();
		
	    	if (ch == 'q'){ 
				break;
			}else if(ch=='d') {
				clear();
				right(map);
				if(pin==0)maps(map,count);
                else if(pin==1)maps2(map,count);
			}else if(ch=='a'){
				clear();
				left(map);
				if(pin==0)maps(map,count);
                else if(pin==1)maps2(map,count);
			}else if(ch=='w'){
				shot(map);
				if(pin==0)maps(map,count);
                else if(pin==1)maps2(map,count);	
			}
		
  		
	}	
    clear();
    if(flag_about_win_or_lose==1){
        mvprintw(10,40," ___    ___ ________  ___  ___          ___       ________  ________  _______      ");
       mvprintw(11,40,"|\\ \\ /  /|\\  __  \\|\\\\|\\\\       |\\  \\     |\\   __  \\|\\   ____\\|\\  ___ \\    ");
       mvprintw(12,40,"\\ \\  \\/  / | \\  \\|\\  \\ \\  \\\\  \\       \\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|\\ \\   __/|   ");
       mvprintw(13,40," \\ \\    / / \\ \\  \\\\  \\ \\  \\\\  \\       \\ \\  \\    \\ \\  \\\\  \\ \\_____  \\ \\  \\_|/__  ");
       mvprintw(14,40,"   \\/  /  /   \\ \\  \\\\  \\ \\  \\\\  \\       \\ \\  \\____\\ \\  \\\\  \\|____|\\  \\ \\  \\_|\\ \\ ");
       mvprintw(14,40," __/  / /      \\ \\_______\\ \\_______\\       \\ \\_______\\ \\_______\\____\\_\\  \\ \\_______\\");
       mvprintw(16,40,"|\\___/ /        \\|_______|\\|_______|        \\|_______|\\|_______|\\_________\\|_______|");
       mvprintw(17,40,"\\|___|/                                                        \\|_________|         ");

       mvprintw(25,40,"YOUR SCORE IS %d",count);
       
    }else if(flag_about_win_or_lose==2){
       mvprintw(10,40," ___    ___ ________  ___  ___          ___       __   ___  ________    ");
       mvprintw(11,40,"|\\  \\  /  /|\\   __  \\|\\  \\|\\  \\        |\\  \\     |\\  \\|\\ \\|\\  ___  \\ ");
       mvprintw(12,40,"\\ \\  \\/  / | \\  \\|\\  \\ \\  \\\\  \\       \\ \\  \\    \\ \\  \\ \\  \\ \\  \\ \\  \\  ");
       mvprintw(13,40," \\ \\  / / \\ \\ \\\\ \\ \\ \\\\  \\            \\\\ \\ __\\ \\ \\ \\  \\ \\  \\ \\  \\  ");
       mvprintw(14,40,"  \\/  /  /   \\ \\  \\\\  \\ \\  \\\\  \\       \\ \\  \\|\\__\\_\\  \\ \\  \\ \\  \\ \\  \\ ");
       mvprintw(15,40,"__/  / /      \\ \\_______\\ \\_______\\       \\ \\____________\\ \\__\\ \\__\\ \\__\\");
       mvprintw(16,40,"|\\___/ /        \\|_______|\\|_______|        \\|____________|\\|__|\\|__| \\|__|");
       mvprintw(17,40,"\\|___|/                                                                    ");

       mvprintw(25,40,"YOUR SCORE IS %d",count);
      
    }
    
    getch();
    timeout(10000);
  	endwin();
}