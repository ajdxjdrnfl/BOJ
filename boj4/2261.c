#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct POINT{
    int x;
    int y;
}Point;

int compare1(const void *a, const void *b){
    Point ap = *(Point *)a;
    Point bp = *(Point *)b;

    if(ap.x < bp.x) return -1;

    if(ap.x > bp.x) return 1;  
    

    return 0;
}
int compare2(const void*a, const void*b){
    Point ap = *(Point*)a;
    Point bp = *(Point*)b;
    if(ap.y<bp.y) return -1;
    if(ap.y>bp.y) return 1;
    return 0;
}
int distant(Point a, Point b){
    return pow(a.x-b.x,2)+pow(a.y-b.y,2);
}

int divide(Point *arr, int left, int right){
    
    int left_value, right_value;
    int band_right=(left+right)/2, band_left=(left+right)/2;
    int smallest=800000000;
    
    if(right-left<=2){
        for(int i=left; i<right; i++){
            for(int j=i+1; j<=right; j++){
                if(smallest>distant(arr[i], arr[j])) smallest = distant(arr[i], arr[j]);
            }
        }
        return smallest;
    }
    
    left_value = divide(arr, left, (left+right)/2);
    right_value = divide(arr, (left+right)/2+1, right);

    if(smallest>left_value) smallest = left_value;
    if(smallest>right_value) smallest = right_value;

    for(int i=(left+right)/2+1; i<=right; i++){
        if(pow(arr[i].x-arr[(left+right)/2].x,2)<=smallest) band_right=i;
        else{
            band_right = i-1;
            break;
        }
    }
    for(int i=(left+right)/2-1; i>=left; i--){
        if(pow(arr[i].x-arr[(left+right)/2].x,2)<=smallest) band_left=i;
        else{
            band_left = i+1;
            break;
        }
    }
    
    int N = band_right-band_left+1;
    Point temp[N];
    for(int i=0; i<N; i++){
        temp[i].x = arr[i+band_left].x;
        temp[i].y = arr[i+band_left].y;
    }
    if(N!=1){
    qsort(temp, N, sizeof(Point), compare2);
    
    for(int i=0; i<N-1; i++){
        for(int j=i+1; j<=N-1; j++){
            if(pow(temp[i].y-temp[j].y,2)>=smallest) break;
            else if(distant(temp[j], temp[i])<smallest) smallest = distant(temp[j], temp[i]);
        }
    }
    }
    
    return smallest;


}

int main(void){
    int n;
    scanf("%d", &n);
    Point arr[n];
    for(int i=0; i<n; i++){
        scanf("%d %d",&arr[i].x, &arr[i].y);
    }
    qsort(arr, n, sizeof(Point), compare1);
    printf("%d\n",divide(arr, 0, n-1));

}