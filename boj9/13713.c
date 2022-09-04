#include <stdio.h>
#include <string.h>

int Z[1000010];
int Zalgorithm(char *str, int size){

    int L=0,R=0;
    Z[0] = size;
    for(int i=1; i<size; i++){
        if(i>R){
            L=R=i;
            while(R<size && str[R-L] == str[R]) R++;
            R--;
            Z[i]= R-L+1;
            
        }
        else{
            int k = i-L;
            if(Z[k]<R-i+1) Z[i] = Z[k];
            else{
                L=i;
                while(R<size && str[R-L]==str[R]) R++;
                R--;
                Z[i] = R-L+1;
            }
        }
    }
    return 1;
}

int main(void){

    char str[1000010];
    char temp[1000010];
    scanf("%s", temp);
    int len = strlen(temp);

    for(int i=0; i<len; i++){
        str[i] = temp[len-i-1];
    }

    Zalgorithm(str, len);
    int M;
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int a;
        scanf("%d", &a);
        printf("%d\n", Z[len-1-(a-1)]);
    }


}