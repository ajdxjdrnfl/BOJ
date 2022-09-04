#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int testNum;
    
    scanf("%d", &testNum);

    for(int i=0; i<testNum; i++){
        int N;
        long long result=1;
        char cloth[31][21];
        char type[31][21];
        int type_sum[31]={0,};
        int type_num =0;
        scanf("%d", &N);
        for(int j=0; j<N; j++){
            char temp[20];
            scanf("%s %s", cloth[j], temp);
            
            if(j==0){
               
                strcpy(type[type_num], temp);
                type_sum[type_num]=1;
                type_num++;
                
            }
            else{
            for(int k=0; k<type_num; k++){
                if(strcmp(type[k], temp)==0){
                    type_sum[k]++;
                    break;
                }
                if(k==type_num-1){
                    strcpy(type[type_num], temp);
                    type_sum[type_num]=1;
                    type_num++;
                    break;
                }   
            }
            }
        }
        for(int j=0; j<type_num; j++){
            
            result =(long long)result*(type_sum[j]+1);
    }
    printf("%lld\n", result-1);
    }
    

}