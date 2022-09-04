#include <stdio.h>
#include <string.h>

int main(void){
    int M;
    scanf("%d", &M);
    int S = 0b00000000000000000000;
    for(int i=0; i<M; i++){
        char s[10];
        int x;
        scanf("%s", s);
        if(strcmp(s, "add") == 0) {
            scanf("%d", &x);
            int temp = 1;
            temp  = temp << (x-1);
            S = S | temp;
        }
        else if(strcmp(s, "remove") == 0){
            scanf("%d", &x);
            if((S & (1<<(x-1)))>0) S = S - (1<<(x-1));
        }
        else if(strcmp(s, "check")==0){
            scanf("%d", &x);
            if((S & (1<<(x-1)))>0) printf("1\n");
            else printf("0\n"); 
        } 
        else if(strcmp(s, "toggle") ==0){
            scanf("%d", &x);
            if((S & (1<<(x-1)))>0) S = S - (1<<(x-1));
            else S = S | (1<<(x-1));
        }
        else if(strcmp(s, "all") ==0){
            S = 0b11111111111111111111;
        }
        else if(strcmp(s, "empty") == 0){
            S = 0b00000000000000000000;
        }
                      
    }
}