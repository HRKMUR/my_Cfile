#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
 #include <sys/time.h>

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
             			if(map[x][y]==3){
                	 	map[x+1][y]=3;
                	 	map[x][y]=0;
 
             			}
 				
         		}
 
     		}
 }
 
 void left_enemy(int map[100][45]){
     for(int y=0;y<=45;y++){
         for(int x=0;x<=100;x++){
             if(map[x][y]==3){
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
         }else if(map[98][y]==3){
             return 1;//右側に敵がいたら
         }
     }
     return 2;//左右どちらにもいない
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
                           }
 
                   }
 
           }
 
 
 }


int main(void){

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
	 map[35][43]=1;

	maps(map);	

	struct timeval _time;
	gettimeofday(&_time, NULL);
	long sec = _time.tv_sec;
	long time=_time.tv_sec;
	int ch = getch();	
	while (true) {
		gettimeofday(&_time, NULL);
		sec = _time.tv_sec;
		

		if(sec!=time){
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
		if(ch = getch()){
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
			}
		
  		}
	}	
  	endwin();

	
}
