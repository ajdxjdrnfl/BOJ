#include <stdio.h>
#include <string.h>

int visited[10000];
int que[10000];
int re[10000];
int rear=-1, front=-1;
int D(int n){
    return (n*2)%10000;
}

int S(int n){
    if(n==0) return 9999;
    else return n-1;

}

int L(int n){
    int a, b, c, d;
    a = n/1000;
    b = (n%1000)/100;
    c = ((n%1000)%100)/10;
    d = (((n%1000)%100)%10);

    return b*1000 + c*100 + d*10 + a;
}

int R(int n){
    int a, b, c, d;
    a = n/1000;
    b = (n%1000)/100;
    c = ((n%1000)%100)/10;
    d = (((n%1000)%100)%10);

    return d*1000 + a*100 + b*10 +  c;
}
void DSLR(int N, int K){

    memset(visited, -1, sizeof(visited));
    rear=-1, front=-1;
    visited[N] = N;
    que[++front] = N;
    re[N] = 0;
    while(rear<front){
        int temp = que[++rear];
        if(temp==K) break;
        int a,b,c,d;
        a = D(temp);
        b = S(temp);
        c = L(temp);
        d = R(temp);
        if(visited[a]==-1){
            que[++front] = a;
            visited[a] = temp;
            re[a] = 1;
        }
        if(visited[b]==-1){
            que[++front] = b;
            visited[b] = temp;
            re[b] = 2;
        }
        if(visited[c]==-1){
            que[++front] = c;
            visited[c] = temp;
            re[c] = 3;
        }
        if(visited[d]==-1){
            que[++front] = d;
            visited[d] = temp;
            re[d] = 4;
        }
    }
}
void printDSLR(int K){
    if(re[K]!=0){
        printDSLR(visited[K]);
        if(re[K]==1) printf("D");
        else if(re[K]==2) printf("S");
        else if(re[K]==3) printf("L");
        else if(re[K]==4) printf("R");
    }

}
int main(void){

    int test;
    scanf("%d", &test);
    while(test--){
        int a,b;
        scanf("%d %d", &a, &b);
        DSLR(a,b);
        printDSLR(b);
        printf("\n");
    }
    
}