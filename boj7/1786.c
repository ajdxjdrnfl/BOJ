#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000005

int kmp[MAX];
int stack[MAX];
int top=0;

void preprocess(char *P, int size){
    

    kmp[0] = 0;
    int j =0;
    for(int i=1; i<size; i++){
        while(j>0 && P[i]!=P[j]){
            j = kmp[j-1];
        }

        if(P[i]==P[j]){
            j++;
            kmp[i] = j;
        }
    }

}
int main(void){
    char T[MAX];
    char P[MAX];
    
    fgets(T, MAX, stdin);
    int n = strlen(T);
    T[n-1] = '\0';
    n = n-1;
    fgets(P, MAX, stdin);
    int m = strlen(P);
    P[m-1] = '\0';
    m = m-1;

    
    
    preprocess(P, m);
    
    int j = 0;
    int result=0;
    for(int i=0; i<n; i++){
        
        while(j>0 && T[i]!=P[j]){
            j = kmp[j-1];
        }

        if(T[i]==P[j]){
            if(j==m-1){
                result++;
                stack[top++] = i-j+1;
                j = kmp[j];

            }
            else j++;
        }
        
    }

    printf("%d\n", result);
   for(int i=0; i<top; i++){
       printf("%d ", stack[i]);
   }
   printf("\n");
}