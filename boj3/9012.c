#include <stdio.h>
#include <string.h>


int main(void){

    int N;
    
    scanf("%d", &N);

    for(int i=0; i<N; i++){
        int stack[50];
        int stackTop=0;
        char s[50];
    
        scanf("%s", s);
        for(int j=0; j<strlen(s); j++){
            char temp;
            temp = s[j];
            if(temp=='('){
                stackTop++;
            }
            else if(temp==')'){
                if(stackTop==0){
                    printf("NO\n");
                    break;
                }
                else{
                    stackTop--;
                }
            }
            if(j==strlen(s)-1 && stackTop==0){
                printf("YES\n");
            }
            else if(j==strlen(s)-1 && stackTop!=0){
                printf("NO\n");
            }
        }
        

    }
}