#include <stdio.h>
#define MOD 1000000007
int main(void){
    long long n;
    scanf("%lld", &n);
    long long temp[2][2];
    long long result[2][2];
    long long a[2][2];
    a[0][0] = 1;
    a[0][1] = 1;
    a[1][0] = 1;
    a[1][1] = 0;
    result[0][0] = 1;
    result[0][1] = 0;
    result[1][0] = 0;
    result[1][1] = 1;
    
    while(n>0){
        if(n%2==1){
            for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    for(int k=0; k<2; k++){
                        if(k==0) temp[i][j] = 0;
                        temp[i][j] = (temp[i][j] + result[i][k] * a[k][j])%MOD; 
                    }
                }
            }
            for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    result[i][j] = temp[i][j];
                }
            }
        }
        n/=2;
        for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    for(int k=0; k<2; k++){
                        if(k==0) temp[i][j] = 0;
                        temp[i][j] = (temp[i][j] + a[i][k] * a[k][j])%MOD; 
                    }
                }
            }
            for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    a[i][j] = temp[i][j];
                }
            }  
    }
    printf("%lld\n", result[0][1]);
}