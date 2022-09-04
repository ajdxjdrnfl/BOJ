#include <stdio.h>

#define MAX 1000000001
#define MIN -1

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


int initMin(int *min, int *arr, int node, int start, int end){
    if(start == end) {
        min[node] = arr[start];
        return min[node];
    }
    int mid = (start+end)/2;
    int left = initMin(min, arr, node*2, start, mid);
    int right = initMin(min, arr, node*2+1, mid+1, end);
    if(left < right) min[node] = left;
    else min[node] = right;
    return min[node];
}

int initMax(int *max, int *arr, int node, int start, int end){
    if(start == end) {
        max[node] = arr[start];
        return max[node];
    }
    int mid = (start+end)/2;
    int left = initMax(max, arr,node*2, start, mid);
    int right = initMax(max, arr, node*2+1, mid+1, end);
    if(left < right) max[node] = right;
    else max[node] = left;
    return max[node];
}

int findmax(int *max , int node, int rear, int front, int start, int end){
    if(rear>end || front <start) return MIN;
    if(rear <= start && end<=front) return max[node];

    int mid = (start+end)/2;
    int left = findmax(max, node*2, rear, front, start, mid);
    int right = findmax(max, node*2+1, rear, front, mid+1, end);
    return left>right?left:right;

}
int findmin(int *min , int node, int rear, int front, int start, int end){
    if(rear>end || front <start) return MAX;
    if(rear <= start && end<=front) return min[node];

    int mid = (start+end)/2;
    int left = findmin(min, node*2, rear, front, start, mid);
    int right = findmin(min, node*2+1, rear, front, mid+1, end);
    return left<right?left:right;

}
int updatemin(int *min, int node, int index, int value, int start, int end){
    if(index>end || index < start) return min[node];
    
    if(start==end){
        min[node] = value;
        return min[node];    
    }

    int mid = (start+end)/2;
    int left = updatemin(min, node*2, index, value, start, mid);
    int right = updatemin(min, node*2+1, index, value, mid+1, end);
    min[node] = left<right?left:right;
    return min[node];
    
}

int updatemax(int *max, int node, int index, int value, int start, int end){
    if(index>end || index < start) return max[node];
    
    if(start==end){
        max[node] = value;
        return max[node];    
    }

    int mid = (start+end)/2;
    int left = updatemax(max, node*2, index, value, start, mid);
    int right = updatemax(max, node*2+1, index, value, mid+1, end);
    max[node] = left>right?left:right;
    return max[node];
}
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
    int N,K;
        
    scanf("%d %d" ,&N, &K);
    int min[400001];
    int max[400001];
    int arr[100001];
    for(int i=0; i<N; i++){
        arr[i] = i;        
    }
    initMin(min, arr, 1, 0, N-1);
    initMax(max, arr, 1, 0, N-1);
    for(int i=0; i<K; i++){
        int Q,A,B;
        scanf("%d %d %d", &Q, &A, &B);
        if(Q==1){
            int large = findmax(max, 1, A, B, 0, N-1);
            int small = findmin(min, 1, A, B, 0, N-1);
            
            if(large == B && small == A) printf("YES\n");
            else printf("NO\n");
        }
        if(Q==0){
            swap(&arr[A], &arr[B]);
            updatemin(min, 1, A, arr[A], 0, N-1);
            updatemin(min, 1, B, arr[B], 0, N-1);
            updatemax(max, 1, A, arr[A], 0, N-1);
            updatemax(max, 1, B, arr[B], 0, N-1);
        }
    }
    }
}