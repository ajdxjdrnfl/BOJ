#include <stdio.h>
#include <math.h>

double pi = 3.14159265358979f;

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

double Dabs(double n){
    return n>=0?n:-n;
}
double circle_volume(double x1, double y1, double r1, double x2, double y2, double r2){
    
    double R = Dsqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

    if(R>=r1+r2) return 0.000;
    else if(R<=Dabs(r1-r2)){
        if(r1>r2) return r2*r2*pi;
        else return r1*r1*pi;
    }
    double cosA = (r1*r1 + R*R - r2*r2)/(2*r1*R);
    double cosB = (r2*r2 + R*R - r1*r1)/(2*r2*R);
    double sinA = Dsqrt(1-cosA*cosA);
    
    double h = sinA*r1;

    double theta1 = acos(cosA);
    double theta2 = acos(cosB);
    double result = (r1*r1*theta1/2 - r1*h/2) + (r2*r2*theta2/2 - r2*h/2) + ((r1+r2-R)*h/2); 
    return result*2;
}
int main(void){

    double x1, y1, r1, x2, y2, r2;
    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r1, &x2, &y2, &r2);

    printf("%.3lf\n", circle_volume(x1, y1, r1, x2, y2, r2));
}