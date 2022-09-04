#include <stdio.h>
#include <string.h>

int stack[10000];
int stackTop=0;
int main(void){
    int N;
    scanf("%d", &N);

    for(int i=0; i<N; i++){
        char temp[100];
        int num;
        scanf("%s", temp);
        if(strcmp(temp, "push")==0){
            scanf("%d", &num);
           stack[stackTop++] = num;
        }
        else if(strcmp(temp, "pop")==0){
            if(stackTop!=0) printf("%d\n", stack[--stackTop]);
            else printf("-1\n");
        }
        else if(strcmp(temp, "size")==0){
            printf("%d\n", stackTop);
        }
        else if(strcmp(temp, "empty")==0){
            if(stackTop!=0) printf("0\n");
            else printf("1\n");
        }
        else if(strcmp(temp, "top") ==0){
            if(stackTop!=0) printf("%d\n", stack[stackTop-1]);
            else printf("-1\n");
        }

    }
}