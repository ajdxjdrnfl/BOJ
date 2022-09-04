#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef struct _POINT{
    long long x;
    long long y;
    long long rel_x;
    long long rel_y;
}POINT;

long long ccw(POINT a, POINT b, POINT c){
    long long ans = ((a.x*b.y+b.x*c.y+c.x*a.y) - (b.x*a.y+c.x*b.y+a.x*c.y));
    if(ans<0) return -1;
    else if(ans>0) return 1;
    else return 0;
}

int comp1(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(pa.y<pb.y) return -1;
    if(pa.y>pb.y) return 1;
    else{
        if(pa.x<pb.x) return -1;
        if(pa.x>pb.x) return 1;
        return 0;
    }
}

int comp2(const void*a , const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    
    if(pa.rel_y*pb.rel_x<pb.rel_y*pa.rel_x) return -1;
    if(pa.rel_y*pb.rel_x>pb.rel_y*pa.rel_x) return 1;
    else{
        if(pa.y<pb.y) return -1;
        if(pa.y>pb.y) return 1;
        else{
            if(pa.x<pb.x) return -1;
            if(pa.x>pb.x) return 1;
            return 0;
        }
    }
}

void swap(POINT *a, POINT *b){
    POINT temp = *a;
    *a = *b;
    *b = temp;
}


int small(POINT a, POINT b){
    if(a.x<b.x) return 1;
    else if(a.x==b.x && a.y<b.y) return 1;
    else if(a.x==b.x && a.y==b.y) return 1;
    else return 0;
}
long long isCross(POINT p1, POINT p2, POINT p3, POINT p4){
   long long abc = ccw(p1, p2, p3);
   long long abd = ccw(p1, p2, p4);
   long long cda = ccw(p3,p4,p1);
   long long cdb = ccw(p3,p4,p2);

    if((abc*abd==0) && (cda*cdb==0)) {
        if(small(p2,p1)==1) swap(&p1,&p2);
        if(small(p4,p3)==1) swap(&p3,&p4);
        return (small(p1,p4)==1 && small(p3, p2)==1);
    }  
    
    return ( (abc*abd<=0) && (cda*cdb<=0) );
}
int main(void){

    int T;
    scanf("%d", &T);
    while(T--){
        int n,m;
        POINT black[101], white[101];
        scanf("%d %d", &n, &m); 
        
        int b_stack[101];
        int b_top=-1;

        int w_stack[101];
        int w_top=-1;

        for(int i=0; i<n; i++){
            scanf("%lld %lld", &black[i].x, &black[i].y);
        }
        for(int i=0; i<m; i++){
            scanf("%lld %lld", &white[i].x, &white[i].y);
        }
        
        qsort(black, n, sizeof(POINT), comp1);
        qsort(white, m, sizeof(POINT), comp1);

        for(int i=0; i<n; i++){
            black[i].rel_x = black[i].x - black[0].x;
            black[i].rel_y = black[i].y - black[0].y;
        }
        for(int i=0; i<m; i++){
            white[i].rel_x = white[i].x - white[0].x;
            white[i].rel_y = white[i].y - white[0].y;
           
        }
        
        if(n==1 && m==1){
            printf("YES\n");
            continue;
        }
        qsort(&black[1], n-1, sizeof(POINT), comp2);
        qsort(&white[1], m-1, sizeof(POINT), comp2);
        
        for(int i=0; i<n; i++){
            while(b_top>=1 && ccw(black[b_stack[b_top-1]], black[b_stack[b_top]], black[i])<=0) b_top--;
            b_stack[++b_top] = i;
        }
        
        for(int i=0; i<m; i++){
            while(w_top>=1 && ccw(white[w_stack[w_top-1]], white[w_stack[w_top]], white[i])<=0) w_top--;
            w_stack[++w_top] = i;
        }

        int w_size = w_top+1;
        int b_size = b_top+1;

        
        int is = TRUE;
        for(int i=0; i<b_size; i++){
            for(int j=0; j<w_size; j++){
                if(isCross(black[b_stack[i]], black[b_stack[(i+1)%b_size]], white[w_stack[j]], white[w_stack[(j+1)%w_size]])){
                    is = FALSE;
                    break; 
                }
            }
            if(is==FALSE) break;
        }
        int white_in_black = TRUE;
        if(b_size>2){
            for(int i=0; i<w_size; i++){
                for(int j=0; j<b_size; j++){
                    if(ccw(black[b_stack[j]], black[b_stack[(j+1)%b_size]], white[w_stack[i]])<=0){
                        white_in_black = FALSE;
                        break;
                    }
                }
                if(!white_in_black) break;
            }
              if(white_in_black) is = FALSE;
        }
      

        int black_in_white=TRUE;
        if(w_size>2){
            for(int i=0; i<b_size; i++){
                for(int j=0; j<w_size; j++){
                    if(ccw(white[w_stack[j]], white[w_stack[(j+1)%w_size]], black[b_stack[i]])<=0) {
                        black_in_white = FALSE;
                        break;
                    }
    
                }
                if(!black_in_white) break;
            }
            if(black_in_white) is = FALSE;
        }

       
        if(is==TRUE) printf("YES\n");
        else if(is==FALSE) printf("NO\n");
    }
}