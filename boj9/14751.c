#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct _line{
    double upperX, lowX;
    double hX;
    double inter;
    double incl;
    int num;
}line;

typedef struct _QUERY{
    double num;
    int index;
}query;

line l[100001];
query q[100001];

int coml(const void*a, const void*b){
    line pa = *(line*)a;
    line pb = *(line*)b;

    if(pa.incl > pb.incl) return -1;
    else if(pa.incl < pb.incl) return 1;
    else {
        if(pa.inter < pb.inter) return -1;
        else return 1;
    }
}
int comq(const void*a , const void*b){
    query pa = *(query*)a;
    query pb =  *(query*)b;
    if(pa.num < pb.num) return -1;
    else return 1;
}
double cross(line a, line b){
    return (a.inter-b.inter)/(b.incl-a.incl);
}

int solve(query q, line *stack, int top){
    int index;
    int low,high,mid;
    low = 0;
    int ans = 0;
    high = top-1;
    while(low<=high){
        mid = (low+high)/2;
      
        if(stack[mid].hX < q.num + __FLT_EPSILON__) {
           
            ans = mid;
            low = mid+1;
        }
        else{
         
            high = mid-1;
        }
    }
    return stack[ans].num;
}
int main(void){
    double maxY, minY;
    int n,m;
    int ans[100001];
    scanf("%lf %lf", &maxY, &minY);
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%lf %lf", &l[i].upperX, &l[i].lowX);
        l[i].incl = (double)(l[i].upperX-l[i].lowX)/(double)(maxY-minY);
        l[i].num = i+1;
        l[i].inter =  l[i].upperX - l[i].incl*maxY;
    }   

    scanf("%d", &m);
    for(int i=0; i<m; i++){
        scanf("%lf", &q[i].num);
        q[i].index = i;
    }
    qsort(l, n, sizeof(line), coml);
    qsort(q, m, sizeof(query), comq);

    line stack[100001];
    int top=0;
    for(int i=0; i<n; i++){
        line temp = l[i];
        temp.hX = minY;
        while(top>0){
            if(fabs(temp.incl-stack[top-1].incl)<=__FLT_EPSILON__){
                if(temp.inter > stack[top-1].inter){
                    temp = stack[top-1]; 
                    top--;
                    break;
                }
                else{
                    top--;
                }
            }
            else{
                temp.hX = cross(temp, stack[top-1]);
                if(stack[top-1].hX <temp.hX) break;
                top--;
            }
        }
        stack[top++] = temp;
    }
   
    for(int i=0; i<m; i++){
        ans[q[i].index] = solve(q[i], stack, top);
    }
    for(int i=0; i<m; i++){
        printf("%d\n", ans[i]);
    }
}