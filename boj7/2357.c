#include <stdio.h>

#define MAX 1000000001
#define MIN 0

int arr[100001];

int initMin(int *min, int node, int start, int end){
    if(start == end) {
        min[node] = arr[start];
        return min[node];
    }
    int mid = (start+end)/2;
    int left = initMin(min, node*2, start, mid);
    int right = initMin(min, node*2+1, mid+1, end);
    if(left < right) min[node] = left;
    else min[node] = right;
    return min[node];
}

int initMax(int *max, int node, int start, int end){
    if(start == end) {
        max[node] = arr[start];
        return max[node];
    }
    int mid = (start+end)/2;
    int left = initMax(max, node*2, start, mid);
    int right = initMax(max, node*2+1, mid+1, end);
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
int main(void){

    int N,M;
    scanf("%d %d", &N, &M);
    int min[400001];
    int max[400001];

    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);        
    }
    initMin(min, 1, 1, N);
    initMax(max, 1, 1, N);
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        printf("%d %d\n", findmin(min, 1, a,b, 1, N), findmax(max, 1,a,b,1,N));
    }
}