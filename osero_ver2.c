#include <stdio.h>

   
//マップを書く関数-----------------------------------
void drew_map(int field[8][8]){
    int a=0;
    int g=0;
    int r=0;
   
    printf("  ");
    for(a=0;a<=7;a++){
        printf("%d ",a);
    }

    for(r=0;r<=7;r++){
         printf("\n ");
         printf("%d",r);
         for(g=0;g<=7;g++){
            switch(field[g][r]){
                case 0:
                    printf("\x1b[32m# \x1b[m" );
                    break;
                case 1:
                    printf("\x1b[30m\x1b[47mW\x1b[m" );
                    printf(" ");
                    break;
                case 2:
                    printf("B ");
                    break;
            }
         }
    }
    printf("\n ");
}
//ここまで---------------------------------------------
//右判定関数-------------------------------------------------
void serch_right(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_x,int black_or_white,int field[8][8] ){
    for(scan_gyou=scan_gyou;scan_gyou<=8;scan_gyou++){ //白==1 クロ=2
            if(field[scan_gyou+1][scan_retu]==black_or_white){
                while(1){
                    if (scan_gyou==first_x){
                        break;
                    }
                    field[scan_gyou][scan_retu]=black_or_white;
                    
                    *count_can=*count_can+1;//配置完了の印
                   
                    scan_gyou--;
                }    
                break; 

            }else if(field[scan_gyou+1][scan_retu]==0 || scan_gyou+1>=8){
                *count_cant=*count_cant+1;//配置できなかった場合のカウント
                break;
               
            } 
    
        }
}
//ここまで---------------------------------------------ーーーー
//左判定関数-------------------------------------------------
void serch_left(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_x,int black_or_white,int field[8][8] ){
    for(scan_gyou=scan_gyou;scan_gyou>=0;scan_gyou--){
            if(field[scan_gyou-1][scan_retu]==black_or_white){//白==1 クロ=2
                while(1){
                    if (scan_gyou==first_x){
                        break;
                    }
                    field[scan_gyou][scan_retu]=black_or_white;
                    *count_can=*count_can+1;
                    scan_gyou++;
                }
                break;
            }else if(field[scan_gyou-1][scan_retu]==0|| scan_gyou-1<=-1){
                *count_cant=*count_cant+1;
                break;
        }
    }
}
//ここまで---------------------------------------------------
//上判定関数-------------------------------------------------
void serch_up(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_y,int black_or_white,int field[8][8] ){
    for(scan_retu=scan_retu;scan_retu>=0;scan_retu--){
            if(field[scan_gyou][scan_retu-1]==black_or_white){

                while(1){
                    if(first_y==scan_retu){
                        break;
                    }
                    field[scan_gyou][scan_retu]=black_or_white;
                    *count_can=*count_can+1;
                    scan_retu++;
                }
                break;
            }else if(field[scan_gyou][scan_retu-1]==0 || scan_retu-1<=-1){
                *count_cant=*count_cant+1;
                break;
               
            }

        }
}
//ここまで---------------------------------------------------
//した判定関数------------------------------------------------
void serch_down(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_y,int black_or_white,int field[8][8] ){
    for(scan_retu=scan_retu;scan_retu>=0;scan_retu++){      
        if(field[scan_gyou][scan_retu+1]==black_or_white){
            while(1){
                if(first_y==scan_retu){
                    break;
                }
                field[scan_gyou][scan_retu]=black_or_white;
                *count_can=*count_can+1;
                scan_retu--;
                }
                break;
            }else if(field[scan_gyou][scan_retu+1]==0 || scan_retu+1 >= 8){
                *count_cant=*count_cant+1;
                break;
                
            }

        }
}
//ここまで------------------------------------------------
//右斜め上------------------------------------------------
void serch_right_up(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_x,int first_y ,int black_or_white,int field[8][8] ){
    while(1){
        if(field[scan_gyou+1][scan_retu-1]==black_or_white){
            while(1){
                if(first_y==scan_retu||first_x==scan_gyou){
                    break;
                }
                field[scan_gyou][scan_retu]=black_or_white;
                *count_can=*count_can+1;
                scan_gyou--;scan_retu++;
                }
                break;
            }else if(field[scan_gyou+1][scan_retu-1]==0|| scan_gyou+1 >= 8|| scan_retu-1 <=-1){
                *count_cant=*count_cant+1;
                break;
                
            }
           scan_gyou++;scan_retu--;
    }
}
//ここまで-----------------------------------------------
//右斜め下------------------------------------------------
void serch_right_down(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_x,int first_y ,int black_or_white,int field[8][8] ){
    while(1){       
        if(field[scan_gyou+1][scan_retu+1]==black_or_white){
            while(1){
                if(first_y==scan_retu||first_x==scan_gyou){
                    break;
                }
                field[scan_gyou][scan_retu]=black_or_white;
                *count_can=*count_can+1;
                scan_gyou--; scan_retu--;
                }break;
            }else if(field[scan_gyou+1][scan_retu+1]==0 || scan_gyou+1 >=8 || scan_retu+1 >=8){
                *count_cant=*count_cant+1;
                break;
               
            }
            scan_gyou++;scan_retu++;
    }
}
//ここまで-------------------------------------------------
//左斜め下------------------------------------------------
void serch_left_down(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_x,int first_y ,int black_or_white,int field[8][8] ){
    while(1){
        if(field[scan_gyou-1][scan_retu+1]==black_or_white){
            while(1){
                if(first_y==scan_retu||first_x==scan_gyou){
                    break;
                }
                field[scan_gyou][scan_retu]=black_or_white;
                *count_can=*count_can+1;
                scan_gyou++; scan_retu--;
                }break;
            }else if(field[scan_gyou-1][scan_retu+1]==0 || scan_gyou-1 <=-1|| scan_retu+1 >=8){
                *count_cant=*count_cant+1;
                break;
                
            }
           scan_gyou--;scan_retu++;
        }
}
//ここまで----------------------------------------------
//左斜め上---------------------------------------------
void serch_left_up(int *count_can,int *count_cant,int scan_gyou ,int scan_retu,int first_x,int first_y ,int black_or_white,int field[8][8] ){
    while(1){
        if(field[scan_gyou-1][scan_retu-1]==black_or_white){
            while(1){
                if(first_y==scan_retu||first_x==scan_gyou){
                    break;
                    }
                field[scan_gyou][scan_retu]=black_or_white;
                *count_can=*count_can+1;
                scan_gyou++; scan_retu++;
                }break;
            }else if(field[scan_gyou-1][scan_retu-1]==0 || scan_gyou-1 <=0||scan_retu-1<=0){
                *count_cant=*count_cant+1;
                break;
                
            }
           scan_gyou--;scan_retu--;
    }
}
//ここまで-------------------------------------------
//勝ち負けやおけるか判定機------------------------------

//------------------------------------------------


int main(void){
    int map[8][8] = {};

    int flag=1;
    int x,y;
    int i,j;
    int a=0;
    int count=0;
    int count2=0;
    int countnull=0;
    int black=0;
    int white=0;

    map[3][3]=1; //白
    map[4][3]=2; //黒
    map[3][4]=2;//黒
    map[4][4]=1;//白
    drew_map(map);
    while(flag==1){
      
        
       first1:
        count=0;
        count2=0;
       printf("\n黒の番です");
       printf("\nどこの列に入れますか >");
       scanf("%d",&i);
       printf("\nどこの行に入れますか >");
        scanf("%d",&j);
        
       if(map[i][j]==2 ||map[i][j]==1 ){
           printf("できません");
               goto first1;
           }
        x=i;
        y=j;
        serch_right(&count2,&count,i,j,x,2,map);
        serch_left(&count2,&count,i,j,x,2,map);
        serch_up(&count2,&count,i,j,y,2,map);
        serch_down(&count2,&count,i,j,y,2,map);
        serch_right_up(&count2,&count,i,j,x,y,2,map);
        serch_right_down(&count2,&count,i,j,x,y,2,map);
        serch_left_up(&count2,&count,i,j,x,y,2,map);
        serch_left_down(&count2,&count,i,j,x,y,2,map);
         //おけるか　//勝利かの判定
         printf("%d\n",count);//////////////////////////////////
        if(count==8 || count2==0){
            printf("できません");
          
            goto first1;
        }else if(count < 8){
             map[x][y]=2;
        }
      
        for(y=0;y<=7;y++){
            for(x=0;x<=7;x++){
                if(map[x][y]==0){
                    countnull=countnull+1;

                }else if(map[x][y]==1){
                    white=white+1;
                }else if(map[x][y]==2){
                    black=black+1;
                }
            }
        }
       
        if(countnull==0 && black < white){
            flag=1;
            break;
        }else if(countnull==0 && white < black){
            flag=2;
            break;

        }else if(countnull==0 && white==black){
            flag=3;
            break;
        }
        countnull=0;
        white=0;
        black=0;
        drew_map(map);
       
       
        x=0;
        y=0;
        first2:
        count=0;
        count2=0;
        printf("\n白の番です");
        printf("\nどこの列に入れますか >");
        scanf("%d",&i);
        printf("\nどこの行に入れますか >");
        scanf("%d",&j);

        if(map[i][j]==2 ||map[i][j]==1 ){
           printf("できません");
               goto first1;
           }
        x=i;
        y=j;
        serch_right(&count2,&count,i,j,x,1,map);
        serch_left(&count2,&count,i,j,x,1,map);
        serch_up(&count2,&count,i,j,y,1,map);
        serch_down(&count2,&count,i,j,y,1,map);
        serch_right_up(&count2,&count,i,j,x,y,1,map);
        serch_right_down(&count2,&count,i,j,x,y,1,map);
        serch_left_up(&count2,&count,i,j,x,y,1,map);
        serch_left_down(&count2,&count,i,j,x,y,1,map);
      
          if(count==8||count2==0){
                
            printf("できません");
            goto first2;
        }else if(count < 8){
             map[x][y]=1;
        }


        for(y=0;y<=7;y++){
            for(x=0;x<=7;x++){
                if(map[x][y]==0){
                    countnull=countnull+1;

                }else if(map[x][y]==1){
                    white=white+1;
                }else if(map[x][y]==2){
                    black=black+1;
                }
            }
        }
     
        if(countnull==0 && black < white){
            flag=1;
            break;
        }else if(countnull==0 && white < black){
            flag=2;
            break;

        }else if(countnull==0 && white==black){
            flag=3;
            break;
        }
         countnull=0;
         white=0;
         black=0;
        drew_map(map);

        
    }
     if(flag==3){
        printf("同点です");
    }else if(flag ==1){
        printf("白の勝ち");
    }else if(flag==2){
         printf("黒の勝ち");
    }
}