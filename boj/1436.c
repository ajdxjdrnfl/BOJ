#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int showm(int N){

    char c[10];
    int result; 
    int i=0;
        for(int j=666; j<100000000; j++){
            sprintf(c,"%d",j);
            if(strstr(c,"666")!=NULL) i++;
            if(i==N) break;
        }
    result = atoi(c);
        
    
    return result;

}

int main(void){
    int N,result;
    scanf("%d", &N);
    result = showm(N);

    printf("%d",result);
}