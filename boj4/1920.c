#include <stdio.h>
#include <stdlib.h>

int com(const void *a, const void *b){
    long long A = *(long long*)a;
    long long B = *(long long*)b;
    if(A<B) return -1;
    else if(A>B) return 1;

    return 0;
}
int main(void){
    int num1,num2;
    scanf("%d", &num1);
    long long N[num1];
    for(int i=0; i<num1; i++){
        scanf("%lld", &N[i]);
        
    }
    scanf("%d", &num2);
    long long M[num2];
    for(int i=0; i<num2; i++){
        scanf("%lld", &M[i]);
    }
    qsort(N, num1, sizeof(long long), com);
    for(int i=0; i<num2; i++){
        int flag=0;
        int low = 0;
        int high = num1-1;
        while(low<=high){
            int mid = (low+high)/2;
        
            if(N[mid]==M[i]) {

                flag=1;
                break;
            }
            else if(N[mid]<M[i]){
                low = mid+1;
            }
            else if(N[mid]>M[i]) high = mid-1;
            
            
        }
        if(flag==1) printf("1\n");
        else printf("0\n");
    }
}