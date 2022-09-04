#include <stdio.h>
#include <stdlib.h>

int arr[30];
int left[33000];
int l_now=1;
int r_now=1;
int right[33000];

int com(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
}
int calc(int *temp, int *index, int low, int high,int sum, int C){

    if(sum>C) return 0;
    if(low>high) return 0;

    temp[(*index)++] = sum+arr[low];
    calc(temp, index,low+1, high, sum+arr[low], C);
    calc(temp, index ,low+1, high, sum, C); 

}

int binarySearch(int *temp, int n,int N){
    if(N<0) return 0;
    int low, high;
    low =0; high = n-1;
    
    int mid;
    int result=0;
    while(low<=high){
       
        mid = (low+high)/2;
       
        if(temp[mid]<N) {low = mid+1; result = mid;}  
        else if(temp[mid]>N) high = mid-1;
        else if(temp[mid]==N){
            for(int i=mid+1; i<n;i++){
                if(temp[i]==N) mid = i;
            }
            return mid+1;
        }
    }
    return result+1;
}
int knapsack(int N, int C){


    left[0] = 0;
    right[0] = 0;
    int result=0;
    calc(left, &l_now, 0, N/2-1, 0, C);
    calc(right, &r_now, N/2, N-1, 0,C);

    qsort(left, l_now, sizeof(int), com);
    qsort(right, r_now, sizeof(int), com);
    
    
    for(int i=0; i<r_now; i++){
        if(right[i]>C) break;
        
        result+=binarySearch(left, l_now, C-right[i]);
    }
    return result;
    
}


int comp(const void*a , const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;

    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
}

int main(void){

    int N,C;
    scanf("%d %d", &N, &C);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
   
    int result= knapsack(N, C);
    printf("%d\n", result);
}