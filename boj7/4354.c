#include <stdio.h>
#include <string.h>

#define MAX 1000005

int kmp[MAX];

void preprocess(char *s){
    int n = strlen(s);
    
    kmp[0] = 0;
    int j = 0;
    for(int i=1; i<n; i++){
        
        while(j>0 && s[i]!=s[j]){
            j = kmp[j-1];
        }
        if(s[i]==s[j]){
            j++;
            kmp[i] = j;
        }
        
    }
    
}

int charSquare(char *s){

    int temp = strlen(s);
    int len = temp - kmp[temp-1];
    
    for(int i=0; i<len; i++){
        if(kmp[temp-len+i]!=temp-len+i-len+1) return 1;
    }
    if(temp%len==0) return temp/len;
    else return 1;
}
int main(void){

    while(1){
        char s[MAX];
        scanf("%s" , s);
        if(strcmp(s, ".")==0) break;
        memset(kmp, 0, sizeof(kmp));
        
        preprocess(s);
        printf("%d\n",charSquare(s));
    }
}