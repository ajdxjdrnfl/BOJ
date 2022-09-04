#include <stdio.h>
#include <string.h>

#define MAX 1000005

int kmp[MAX];

void pre(char *s){

    kmp[0] = 0;
    int n  = strlen(s);
    int j = 0;    
    for(int i=1; i<n; i++){
        while(j>0 && s[i]!=s[j]){
            j = kmp[j-1];
        }

        if(s[i]==s[j]) kmp[i] = ++j;
    }
}

int promote(char *s){

    int len = strlen(s);
    int index = kmp[len-1];
    int temp = len - index;
    return temp;
}

int main(void){


    int L;
    char s[MAX];
    scanf("%d", &L);
    scanf("%s", s);
    pre(s);
    
    printf("%d\n",promote(s));

}