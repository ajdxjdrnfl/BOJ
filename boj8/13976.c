#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007

typedef struct _MATRIX{
    long long x[2][2];
}MATRIX;

void mult(MATRIX *a, MATRIX *b){
    MATRIX temp;
   
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            temp.x[i][j] = ((a->x[i][0] * b->x[0][j]+ MOD)%MOD + (a->x[i][1]*b->x[1][j]+MOD)%MOD)%MOD;
        }
    }
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            a->x[i][j] = temp.x[i][j];
        }
    }

}
int main(void){

    long long N;
    scanf("%lld", &N);
   
    if(N%2==1) {
        printf("0\n");
        return 0;
    }
    N = (N-2)/2;
  
    MATRIX *mat = (MATRIX*)malloc(sizeof(MATRIX));
    mat->x[0][0] = 4;
    mat->x[0][1] = -1;
    mat->x[1][0] = 1;
    mat->x[1][1] = 0;

    MATRIX *ans = (MATRIX*)malloc(sizeof(MATRIX));
    ans->x[0][0] = 1;
    ans->x[0][1] = 0;
    ans->x[1][0] = 0;
    ans->x[1][1] = 1;
    
    while(N){
        
        if(N%2==1) mult(ans, mat);
        mult(mat, mat);
        N /= 2;
    }
    
    long long answer = (ans->x[0][0]*3 + ans->x[0][1]) %MOD;
    printf("%lld\n", answer);
}