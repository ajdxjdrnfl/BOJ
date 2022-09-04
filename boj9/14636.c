#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct _request{
    ll x;
    ll y;    
}request;

request producer[50001];
request consumer[50001];
ll dp[500001];

int pcnt=0, ccnt=0;
int comp(const void*a, const void*b){
    request pa = *(request*)a;
    request pb = *(request*)b;

    if(pa.x< pb.x) return -1;
    else if(pa.x>pb.x) return 1;
    else{
        if(pa.y < pb.y) return -1;
        else return 1;
    }
}

int comc(const void*a, const void*b){
    request pa = *(request*)a;
    request pb = *(request*)b;

    if(pa.x< pb.x) return 1;
    else if(pa.x>pb.x) return -1;
    else{
        if(pa.y < pb.y) return 1;
        else return -1;
    }
}

ll value(int p_index, int c_index){
    if(consumer[c_index].x < producer[p_index].x && consumer[c_index].y < producer[p_index].y ) return 0;
    else return (consumer[c_index].x-producer[p_index].x)*(consumer[c_index].y-producer[p_index].y);
}

void dnc(int left, int right, int low, int high){

    if(left>right) return;
    int mid = (left+right)/2;
    int index = high;
    dp[mid]= -4e18;
    for(int i=high; i>=low; i--){
        if(dp[mid] <= value(mid, i)){
            index = i;
            dp[mid] = value(mid, i);
        }
    }

    dnc(left, mid-1, index, high);
    dnc(mid+1, right, low, index);
}

ll max(ll a, ll b){
    return a>b?a:b;
}
int main(void){

    int m,n;
    request arr[50001];
    request brr[50001];
    
    scanf("%d %d", &m,&n);
    for(int i=0; i<m; i++){
        scanf("%lld %lld", &arr[i].x, &arr[i].y);
    }   
    for(int i=0; i<n; i++){
        scanf("%lld %lld", &brr[i].x, &brr[i].y);
    }

    qsort(arr, m, sizeof(request), comp);
    ll temp = arr[0].y;
    producer[pcnt++] = arr[0];
    for(int i=1; i<m; i++){
        if(temp > arr[i].y) {
            producer[pcnt++] = arr[i];
            temp = arr[i].y;
        }
    }

    qsort(brr, n , sizeof(request), comc);
    temp = brr[0].y;
    consumer[ccnt++] = brr[0];
    for(int i=1; i<n; i++){
        if(temp < brr[i].y){
            consumer[ccnt++] = brr[i];
            temp = brr[i].y;
        }
    }

    dnc(0, pcnt-1, 0, ccnt-1);
    ll ans=0;
    for(int i=0; i<pcnt; i++){
        ans = max(ans, dp[i]);
    }
    printf("%lld\n", ans);
}