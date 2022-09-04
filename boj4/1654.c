#include <stdio.h>
#include <stdlib.h>

int main(void){
    long long largest=-1;
    int smallest;
    int K, N;
    
    scanf("%d %d", &K, &N);
    int length[K];
    for(int i=0; i<K; i++){
        scanf("%d", &length[i]);
        
        if(i==0) smallest = length[i];
        else if(smallest<length[i]) smallest = length[i];
    }
    
    long long low = 1;
    long long high = smallest;
    while(low<=high){
        long long mid = (low+high)/2;
        int temp=0;
        for(int i=0; i<K; i++){
            temp = temp + (length[i]/mid);
        }
        if(temp<N) high = mid-1;
        else if(temp>=N) {
            low = mid+1;
            if(largest < mid) largest = mid;
        }

    }
    printf("%lld\n", largest);
}