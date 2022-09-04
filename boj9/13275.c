#include <stdio.h>
#include <string.h>

int A[200020];

int min(int a, int b){
    return a<b?a:b;
}
int manacher(char *str, int len){
    memset(A, 0 ,sizeof(A));
    A[0]=0;
    int r=0,p=0;
   
    for(int i=1;i<len;i++){
        if(i<=r){
            A[i] = min(r-i, A[2*p-i]);
        }
        else{
            A[i] = 0;
        }

        while(str[i+A[i]+1]==str[i-A[i]-1] && i-A[i]-1>=0 && i+A[i]+1<len){
            A[i]++;
        }
        if(r<i+A[i]){
            p=i;
            r=i+A[i];
        }
      
    }    
    int lar=-1;
    for(int i=0; i<len; i++){
        if(lar<A[i]) lar=A[i];
    }
    return lar;
}
int main(void){

    char temp[100010];
    scanf("%s", temp);
    char str[200020];
    for(int i=0; i<strlen(temp); i++){
        str[2*i+0] = '#';
        str[2*i+1] = temp[i];
    }
    str[strlen(temp)*2]='#';
    printf("%d\n",manacher(str, strlen(temp)*2+1));
}