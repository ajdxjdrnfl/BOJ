#include <stdio.h>

#define LENGTH 11

int max[5];

int cut_rod(int *arr, int len);
int Max(int a, int b);
int main(void){
    int length[LENGTH+1]={-1,1,5,8,9,10,17,17,20,24,30};
    for(int i=1; i<5; i++){
        max[i]=-1;
    }
    int result = cut_rod(length, 4);
    printf("result : %d\n", result); 

}
int cut_rod(int *arr, int len){
    
    if(len==0) return 0;
    if(max[len]>=0) return max[len];
     
    int result=0;
    for(int i=1; i<=len; i++){
        result = Max(result,arr[i]+cut_rod(arr, len-i));
    }
    max[len]=result;
    return result;
}

int Max(int a, int b){
    if(a>b) return a;
    return b;
}
