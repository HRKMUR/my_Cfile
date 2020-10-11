#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
/*________  ________  ________  ________  _______           ___  ________   ___      ___ ________  ________  _______   ________  ________      
|\   ____\|\   __  \|\   __  \|\   ____\|\  ___ \         |\  \|\   ___  \|\  \    /  /|\   __  \|\   ___ \|\  ___ \ |\   __  \|\   ____\     
\ \  \___|\ \  \|\  \ \  \|\  \ \  \___|\ \   __/|        \ \  \ \  \\ \  \ \  \  /  / | \  \|\  \ \  \_|\ \ \   __/|\ \  \|\  \ \  \___|_    
 \ \_____  \ \   ____\ \   __  \ \  \    \ \  \_|/__       \ \  \ \  \\ \  \ \  \/  / / \ \   __  \ \  \ \\ \ \  \_|/_\ \   _  _\ \_____  \   
  \|____|\  \ \  \___|\ \  \ \  \ \  \____\ \  \_|\ \       \ \  \ \  \\ \  \ \    / /   \ \  \ \  \ \  \_\\ \ \  \_|\ \ \  \\  \\|____|\  \  
    ____\_\  \ \__\    \ \__\ \__\ \_______\ \_______\       \ \__\ \__\\ \__\ \__/ /     \ \__\ \__\ \_______\ \_______\ \__\\ _\ ____\_\  \ 
   |\_________\|__|     \|__|\|__|\|_______|\|_______|        \|__|\|__| \|__|\|__|/       \|__|\|__|\|_______|\|_______|\|__|\|__|\_________\
   \|_________|                                                                                                                   \|_________|
                                                                                                                                              
                                            
*/
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
            return 1;
    }

    return 0;
}


void maps(int field[40][45]){
    for(int y=0;y<45;y++){
        for(int x=0;x<40;x++){
              switch (field[x][y]){
                case 0:
                    printf("　");
                    break;
        
                case 1:
                    printf("\x1b[33m＠\x1b[m");
                    break;
                case 2:
                    printf("\x1b[36m⬜︎\x1b[m");
                    break;
                case 3:
                    printf("\x1b[31m敵\x1b[m");
                    break;
                case 4:
                    printf("\x1b[36m⬜︎\x1b[m");
                     break;
                case 5:
                    printf("\x1b[33m｜\x1b[m");
                     break;
              }
        }
        printf("\n");
    }

}

void right(int map[40][45]){
    for(int x=0;x<40;x++){
        if(map[x][43]==1){
            if(x+1>=39){
                break;
            }
            map[x+1][43]=1;
            map[x][43]=0;
            break;
        }
    }
}
void left(int map[40][45]){
    for(int x=0;x<40;x++){
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

void right_enemy(int map[40][45]){
    for(int y=45;y>=0;y--){
        for(int x=40;x>=0;x--){
            if(map[x][y]==3){
                map[x+1][y]=3;
                map[x][y]=0;
                
            }

        }

    }

}
void left_enemy(int map[40][45]){
    for(int y=0;y<=45;y++){
        for(int x=0;x<=40;x++){
            if(map[x][y]==3){
                map[x-1][y]=3;
                map[x][y]=0;
                
            }

        }

    }

}
void down_enemy(int map[40][45]){
    for(int y=45;y>=0;y--){
        for(int x=40;x>=0;x--){
            if(map[x][y]==3){
                map[x][y+1]=3;
                map[x][y]=0;
                
            }

        }

    }
}
int check_side_slid(int map[40][45]){
    for(int y=0;y<=45;y++){
        if(map[1][y]==3){
            return 0;//左側に敵がいたら
        }else if(map[38][y]==3){
            return 1;//右側に敵がいたら
        }
    }
    return 2;//左右どちらにもいない
}

void  slid_enemy_down(int map[40][45]){
     for(int y=45;y>=0;y--){
        for(int x=40;x>=0;x--){
            if(map[x][y]==3){
                map[x][y+3]=3;
                map[x][y]=0;
                
            }
        }

    }
    
}
void shot(int map[40][45]){
    for(int x=0;x<=40;x++){
        if(map[x][43]==1){
            map[x][42]=5;
            break;
        }
    }
}



void slid_shel2(int map[40][45],int x,int y){
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
        for(int x=0;x<=40;x++){
            if(map[x][y]==5 ){
                slid_shel2(map,x,y);
            }
        }
     }
}




int main(void){
   
    int flag=1; //0が左1が右
    int map[40][45]={0};
    map[35][43]=1;
    for(int y=0;y<45;y++){
        map[0][y]=2;
    }
    for(int y=0;y<45;y++){
        map[39][y]=2;
    }
    for(int x=0;x<40;x++){
        map[x][44]=4;
    }
   /* for(int x=0;x<40;x++){
        map[x][0]=4;
    }*/
    
    for(int y=2;y<=10;y+=2){
        for(int x=2;x<=20;x+=2){
                map[x][y]=3;
        }
    }
   
   
   
    maps(map);
     int t = time(NULL);
     while(1){
         if (kbhit()) {
          switch(getchar()){
                case 100:
                    right(map);
                    printf("\033[2J\n");
                    maps(map);
                    break;
                case 97:
                    left(map);
                    printf("\033[2J\n");
                    maps(map);
                    break;
                case 119:
                    shot(map);
                    printf("\033[2J\n");
                    maps(map);
                    break;
          }
        }
        if (t != time(NULL)) {
            t = time(NULL);
        slid_shell(map);
        if(flag==1 && check_side_slid(map)==1){
            slid_enemy_down(map);
            flag=0;
        //   printf("1");
        }else if(flag==1){
            right_enemy(map);
          //  printf("2");
        }else if(flag==0 && check_side_slid(map)==0){
            slid_enemy_down(map);
            flag=1;
         //   printf("3");
        }else if(flag==0){
            left_enemy(map);
         //      printf("4");
        }
            printf("\033[2J\n");
           

            maps(map);
        }

    }

}
/*
  ___    ___  ________      ___  ___          ___       __       ___      ________      
 |\  \  /  /||\   __  \    |\  \|\  \        |\  \     |\  \    |\  \    |\   ___  \    
 \ \  \/  / /\ \  \|\  \   \ \  \\\  \       \ \  \    \ \  \   \ \  \   \ \  \\ \  \   
  \ \    / /  \ \  \\\  \   \ \  \\\  \       \ \  \  __\ \  \   \ \  \   \ \  \\ \  \  
   \/  /  /    \ \  \\\  \   \ \  \\\  \       \ \  \|\__\_\  \   \ \  \   \ \  \\ \  \ 
 __/  / /       \ \_______\   \ \_______\       \ \____________\   \ \__\   \ \__\\ \__\
|\___/ /         \|_______|    \|_______|        \|____________|    \|__|    \|__| \|__|
\|___|/                                                                                 
                                                                                        
                                                                                        
*/
