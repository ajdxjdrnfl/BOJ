#include <stdio.h>
#include <string.h>

int A[4000020];
int min(int a, int b){
    return a<b?a:b;
}
long long manacher(char *str , int len){

    long long ans=0;
    int r=0,p=0;
    A[0] = 0;
    for(int i=0; i<len; i++){

        if(i<=r) A[i] = min(A[2*p-i], r-i);
        else A[i] = 0;

        while(i+A[i]+1<len && i-A[i]-1>=0 && str[i+A[i]+1]==str[i-A[i]-1]) A[i]++;
        
        if(r<i+A[i]){
            r = i+A[i];
            p = i;
        }
    }

    for(int i=0; i<len; i++){
        
       if(A[i]!=0) {
        if(str[i]=='#') ans += (A[i]/2);
        else ans+=(A[i]/2+1);
       }
    }
    return ans;
}
int main(void){
    char str[4000020];
    char temp[2000010];

    scanf("%s", temp);
    int len = strlen(temp);
    for(int i=0; i<len; i++){
        str[i*2+0] = '#';

        str[i*2+1] = temp[i];
    }
    str[len*2] = '#';
    
    printf("%lld\n", manacher(str, len*2+1));
}