#include <stdio.h>

typedef struct _POINT{
    long long x;
    long long y;
}POINT;

typedef struct _LINE{
    POINT left;
    POINT right;
}LINE;

LINE line[3001];
int parent[3001];
int rank[3001];
int  ccw(POINT a, POINT b, POINT c){
    long long x1 = a.x, y1 = a.y , x2=b.x, y2 =b.y, x3 = c.x, y3 =c.y;
    long long sum =  x1*y2 + x2*y3 + x3*y1 - (y1*x2 + y2*x3 + y3*x1);
    if(sum > 0) return 1;
    else if(sum ==0) return 0;
    else return -1;
}

void swap(POINT *a, POINT *b){
    long long temp_x, temp_y;
    temp_x = a->x;
    temp_y = a->y;
    a->x = b->x;
    a->y = b->y;
    b->x = temp_x;
    b->y = temp_y;
}

int small(POINT a, POINT b){
    if(a.x < b.x) return 1;
    else if(a.x == b.x && a.y < b.y) return 1;
    else return 0;
}

int findP(int index){
    while(index!=parent[index]) index = parent[index];
    return index;
}
void checkParent(int i, int j){
  
    int pa = findP(i);
    int pb = findP(j);
    
    if(pa!=pb){
        if(rank[pa] < rank[pb]){
            parent[pa] = pb;
            rank[pb] += rank[pa];
        }
        else{
            parent[pb] = pa;
            rank[pa] +=rank[pb];
        }
    }

}

int fourLine(POINT a, POINT b, POINT c, POINT d){
    
    if(small(b, a)==1) swap(&a,&b);
    if(small(d,c)==1) swap(&c,&d);

    if(small(d,a)==1 || small(b,c)==1) return 1;
    else return 0;
}
int main(void){
    int N;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%lld %lld %lld %lld", &line[i].left.x, &line[i].left.y, &line[i].right.x, &line[i].right.y);    
        if(small(line[i].right, line[i].left)==1) swap(&line[i].left, &line[i].right);
        parent[i] = i;
        rank[i] = 1;
    }

    for(int i=1; i<=N-1; i++){
        for(int j=i+1; j<=N; j++){
    
            int a = ccw(line[i].left, line[i].right, line[j].left) * ccw(line[i].left, line[i].right, line[j].right);
            int b = ccw(line[j].left, line[j].right, line[i].left) * ccw(line[j].left, line[j].right, line[i].right);

            if(a==0 && b==0 && fourLine(line[i].left, line[i].right, line[j].left, line[j].right) == 1);
            else if(a<=0 && b<=0) checkParent(i, j);  
        }
    }
    int largest=findP(1);
    int group=0;
    for(int i=1; i<=N; i++){
        if(i==findP(i)) group++;
        if(rank[findP(i)] > rank[largest]) largest = findP(i); 
    }
    printf("%d\n", group);
    printf("%d\n", rank[largest]);

}