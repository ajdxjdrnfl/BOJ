#include <stdio.h>

double Dsqrt(double n){
     double s=0;
    double t=0;
 
    s = n / 2;
    for (;s != t;)
    {
        t = s;
        s = ( (n / t) + t) / 2;
    }
    return s;
    
}
double min (double a , double b){
    return a>b?b:a;
}
double toHome(double X, double Y, double r, double T){
    
    double  R = Dsqrt(X*X + Y*Y);
    int jump = R/r;
    double rest  = R - r * jump;
    double result = min(jump*T + rest, (jump+1)*T + (r-rest));
    result = min(result, R);
    if(jump>0) result = min(result, (jump+1)*T);
    if(R<2*r) result = min(result, 2*T);
    return result;
}
int main(void){

    double X,Y,D,T;
    scanf("%lf %lf %lf %lf", &X, &Y, &D, &T);
    printf("%.13lf\n", toHome(X,Y,D,T));
    
}