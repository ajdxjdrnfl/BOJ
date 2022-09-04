#include <stdio.h>

int min(int a, int b){
    if(a>b) return b;
    return a;
}
int main(void){

    int test;
    scanf("%d", &test);
    for(int i=0; i<test; i++){
        int N;
        scanf("%d", &N);
        int arr[N];
        int ans[N][N];
        for(int j=0; j<N; j++){
            scanf("%d", &arr[j]);
            ans[j][j] = 0;
        }
        
        for(int j=1; j<N; j++){
            for(int k=0; k<N-j; k++){
                int temp =0;
                for(int m=k; m<=k+j; m++) temp+=arr[m];
                for(int m=0; m<j; m++){
                if(m==0) ans[k][k+j] = ans[k][k+m]+ans[k+m+1][k+j]+temp;
                else ans[k][k+j]=min(ans[k][k+j], ans[k][k+m]+ans[k+m+1][k+j]+temp);
                }
            }
        }

        printf("%d\n", ans[0][N-1]);
    }
}