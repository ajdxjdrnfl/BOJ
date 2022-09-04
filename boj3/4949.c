#include <stdio.h>
#include <string.h>

int main(void){
    
    
    while(1){
        char s[200];
        fgets(s, 101, stdin);
        if(strcmp(s,".\n")==0) break;
        int stack[101];
        int stackTop=0;
        for(int i=0; i<strlen(s); i++){

            char temp = s[i];
            if(temp=='('){
                stack[stackTop++]=1;
            }
            else if(temp==')'){
                if(stack[stackTop-1]!=1) stackTop=-2000;
                else if(stack[stackTop-1]==1) stackTop--;
            }
            else if(temp=='['){
                stack[stackTop++]=2;
           }
            else if(temp==']'){
                if(stack[stackTop-1]!=2) stackTop=-2000;
                else if(stack[stackTop-1]==2) stackTop--;
            }
        }
        if(stackTop==0){
            printf("yes\n");
        }
        else{
            printf("no\n");
        }
        
        
    }
}