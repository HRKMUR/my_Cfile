#include <stdio.h>

int main(void){

    int map[8][8] = {0};

  
    map[3][3]=1; //白
    map[4][3]=2; //黒
    map[3][4]=2;//黒
    map[4][4]=1;//白
   
    int flag=1;
    int x,y;
    int i,j;
    int a=0;
    int count=0;
    int count2=0;
    int countnull=0;
    int black=0;
    int white=0;
  

    printf("  ");
    for(a=0;a<=7;a++){
        printf("%d ",a);
    }

    for(y=0;y<=7;y++){
         printf("\n ");
         printf("%d",y);
         for(x=0;x<=7;x++){
            switch(map[x][y]){
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
    while(flag==1){
        x=0;
        y=0;
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
    
    //右突き当たりの処理クロの処理
        for(i=i;i<=8;i++){ //白==1 クロ=2
            if(map[i+1][j]==2){
               
                while(1){
                    if (i==x){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    i--;
                }    
                break; 

            }else if(map[i+1][j]==0 || i+1>=8){
                count=count+1;
                break;
               
            } 
    
        }
    //ここまで
  
        i=x;
        j=y;

    //左突き当たりのクロの処理処理
        for(i=i;i>=0;i--){
           
            if(map[i-1][j]==2){//白==1 クロ=2
               
                 while(1){
                    if (i==x){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    i++;
                }
                 break;
            }else if(map[i-1][j]==0|| i-1<=-1){
                count=count+1;
                break;
        }
        }
    //ここまで
        i=x;
        j=y;
    //した突き当たりの黒の処理
        for(j=j;j>=0;j++){
          
            if(map[i][j+1]==2){

                while(1){
                    if(y==j){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    j--;
                }
                break;
            }else if(map[i][j+1]==0 || j+1 >= 8){
                count=count+1;
                break;
                
            }

        }
    //ここまで
    i=x;
    j=y;
    //上突き当たりの黒の処理
        for(j=j;j>=0;j--){
            if(map[i][j-1]==2){

                while(1){
                    if(y==j){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    j++;
                }
                break;
            }else if(map[i][j-1]==0 || j-1<=-1){
                count=count+1;
                break;
               
            }

        }
         //ここまで
        i=x;
        j=y;
      
        //右斜め上の黒の探索
        while(1){
            if(map[i+1][j-1]==2){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    i--;j++;
                }
                break;
            }else if(map[i+1][j-1]==0|| i+1 >= 8|| j-1 <=-1){
                count=count+1;
                break;
                
            }
           i++;j--;
        }
        //ここまで
        i=x;
        j=y;
        //右斜め下の黒の探索
        while(1){       
            if(map[i+1][j+1]==2){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    i--; j--;
                }break;
            }else if(map[i+1][j+1]==0 || i+1 >=8 || j+1 >=8){
                count=count+1;
                break;
               
            }
           i++;j++;
        }
        //ここまで
         i=x;
          j=y;

        //左斜め下の黒の探索
          while(1){
            if(map[i-1][j+1]==2){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    i++; j--;
                }break;
            }else if(map[i-1][j+1]==0 || i-1 <=-1|| j+1 >=8){
                count=count+1;
                break;
                
            }
           i--;j++;
        }
        //ここまで
        i=x;
        j=y;

        //左斜め上の黒の探索
        while(1){
            if(map[i-1][j-1]==2){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=2;
                    count2=count2+1;
                    i++; j++;
                }break;
            }else if(map[i-1][j-1]==0 || i-1 <=0||j-1<=0){
                count=count+1;
                break;
                
            }
           i--;j--;
        }
        //ここまで
       
       //おけるか　勝利かの判定
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
        
       
        printf("  ");
        for(a=0;a<=7;a++){
          printf("%d ",a);
       }

          for(y=0;y<=7;y++){
            printf("\n ");
             printf("%d",y);
            for(x=0;x<=7;x++){
                switch(map[x][y]){
                    case 0:
                        printf( "\x1b[32m# \x1b[m" );
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

//--------------------------------------白の処理------------------------------------------
   
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
            goto first2;
        }
    x=i;
    y=j;
    //右突き当たりの処理白の処理
        for(i=i;i<=8;i++){ //白==1 クロ=2
           
            if(map[i+1][j]==1){
               
                while(1){
                    if (i==x){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                     i--;
                }
                   
                    
            break;

            }else if(map[i+1][j]==0 ||i+1 >=8){
                count=count+1;
                break;
                
            } 
    
        }
    //ここまで

    i=x;
    j=y;

    //左突き当たりの白の処理処理
        for(i=i;i>=0;i--){
           
            if(map[i-1][j]==1){//白==1 クロ=2
               
                 while(1){
                    if (i==x){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                    i++;
                }
                 break;
            }else if(map[i-1][j]==0|| i-1 <=-1){
                count=count+1;
                break;
                 
            }
        }
    //ここまで
    i=x;
    j=y;
    //した突き当たりの白の処理
        for(j=j;j>=0;j++){
            if(map[i][j+1]==1){

                while(1){
                    if(y==j){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                    j--;
                }
                break;
            }else if(map[i][j+1]==0 || j+1 >=8){
                count=count+1;
                break;
                
            }

        }
    //ここまで
    i=x;
    j=y;
    //上突き当たりの白の処理
        for(j=j;j>=0;j--){
            if(map[i][j-1]==1){

                while(1){
                    if(y==j){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                    j++;
                }
                break;
            }else if(map[i][j-1]==0|| j-1 <=-1){
                count=count+1;
                break;
                 
            }

        }
    //ここまで
    i=x;
    j=y; 
    //右斜め上の白の探索
        while(1){
            if(map[i+1][j-1]==1){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                        i--;j++;
                }
                break;
            }else if(map[i+1][j-1]==0|| i+1 >= 8|| j-1 <=-1){
                count=count+1;
                break;
                
            }
           i++;j--;
        }
        //ここまで
        i=x;
        j=y;
        //右斜め下の白の探索
        while(1){       
            if(map[i+1][j+1]==1){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                    i--; j--;
                }break;
            }else if(map[i+1][j+1]==0|| i+1 >=8 || j+1 >=8){
                count=count+1;
                break;
                
            }
           i++;j++;
        }
        //ここまで
         i=x;
          j=y;

        //左斜め下の白の探索
          while(1){
            if(map[i-1][j+1]==1){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                    i++; j--;
                }break;
            }else if(map[i-1][j+1]==0 || i-1 <=-1|| j+1 >=8){
                count=count+1;
                break;
                 
            }
           i--;j++;
        }
        //ここまで
        i=x;
        j=y;

        //左斜め上の白の探索
        while(1){
            if(map[i-1][j-1]==1){
                while(1){
                    if(y==j||x==i){
                        break;
                    }
                    map[i][j]=1;
                    count2=count2+1;
                    i++; j++;
                }break;
            }else if(map[i-1][j-1]==0|| i-1 <=0||j-1<=0){
                count=count+1;
                break;
                
            }
           i--;j--;
        }
        //ここまで
       
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



         map[x][y]=1;
         printf("  ");
         for(a=0;a<=7;a++){
            printf("%d ",a);
         }
         for(y=0;y<=7;y++){
            printf("\n ");
             printf("%d",y);
            for(x=0;x<=7;x++){
                switch(map[x][y]){
                    case 0:
                        printf("\x1b[32m# \x1b[m");
                        break;
                    case 1:
                        printf("\x1b[30m\x1b[47mW\x1b[m");
                        printf(" ");
                        break;
                    case 2:
                        printf("B ");
                        break;
                }
            }

        }

    }
    if(flag==3){
        printf("同点です");
    }else if(flag ==1){
        printf("白の勝ち");
    }else if(flag==2){
         printf("黒の勝ち");
    }

    
    



return 0;
}