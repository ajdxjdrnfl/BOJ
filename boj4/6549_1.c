#include <stdio.h>

long long square(long long *h, int start, int finish){
    if(start==finish) return h[start];
    int index;
    long long result=-1;
    long long largest=-1;

    long long left = square(h, start, (start+finish)/2);
    long long right = square(h, (start+finish)/2+1,finish);
    if(h[(start+finish)/2] < h[(start+finish)/2+1]) index = (start+finish)/2;
    else index = (start+finish)/2+1;
    

    if(largest<left) largest = left;
    if(largest<right) largest = right;
    
    int low = (start+finish)/2;
    int high = (start+finish)/2+1;
    result = h[index] * 2;
    while( start < low || high<finish ){
        
        if(high<finish && (low==start || h[low-1] < h[high+1])){
            high++;
            if(h[high] < h[index]) index = high;
        }
        else{
            low--;
            if(h[low] < h[index]) index = low;
        }
        if(result<h[index] * (high-low+1)) result = h[index]*(high-low+1);
    }
    if(result>largest) largest = result;
    return largest;
}
int main(void){


    int n;
    scanf("%d", &n);
    while(n!=0){
        long long h[n];
        for(int i=0; i<n; i++){
            scanf("%lld", &h[i]);
        }
        long long result = square(h, 0, n-1);
        printf("%lld\n", result);
        scanf("%d", &n);
    }
}