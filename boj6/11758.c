#include <stdio.h>

int x[3], y[3];
int ccw(int x1, int y1, int x2, int y2, int x3, int y3){
    int sum = (x1*y2 + x2*y3 + x3*y1) - (y1*x2 + y2*x3 + y3*x1);
    if(sum<0) return -1;
    else if(sum>0) return 1;
    else return 0;
}
int main(void){

    for(int i=0; i<3; i++){
    scanf("%d %d", &x[i], &y[i]);
    }
    printf("%d\n", ccw(x[0], y[0], x[1], y[1], x[2], y[2]));
}