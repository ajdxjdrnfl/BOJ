#include <stdio.h>
#include <string.h>

#define MAX 1000001
typedef struct _POINT{
    long long x;
    long long y;
}POINT;

POINT corner[1001];
POINT hole[51];
POINT mice[301];

int arr[601][610];
int size[601];
int cap[601][601];
int flow[601][601];
int visited[601];
int ccw(POINT a, POINT b, POINT c){
    long long temp = (a.x*b.y+b.x*c.y+c.x*a.y)-(b.x*a.y+c.x*b.y+a.x*c.y);
    if(temp>0) return 1;
    if(temp==0) return 0;
    if(temp<0) return -1;
}
void swap(POINT *a, POINT *b){
    POINT temp = *a;
    *a = *b;
    *b = temp;
}
int small(POINT a, POINT b){
    if(a.x<b.x) return 1;
    if(a.x==b.x && a.y<=b.y) return 1;
    return 0; 
}
int equal(POINT a, POINT b){
    if(a.x==b.x && a.y == b.y) return 1;
    return 0;
}
int linesect(POINT a, POINT b, POINT c, POINT d){
    int abc = ccw(a,b,c);
    int abd = ccw(a,b,d);
    int cda = ccw(c,d,a);
    int cdb = ccw(c,d,b);

    int ab = abc*abd;
    int cd = cda*cdb;
    if(ab==0 && cd ==0){
       if(small(b,a)) swap(&a,&b);
       if(small(d,c)) swap(&c,&d);

        if(equal(a,d) || equal(a,c) || equal(b,c) || equal(b,d)) return 0;
        else return small(a,d)&&small(c,b);
    }
    return (ab<=0 && cd<0);
}

int intersect(int m_index, int h_index, int n){
    for(int i=0; i<n; i++){
        if(linesect(mice[m_index], hole[h_index], corner[i], corner[(i+1)%n])) return 1;
    }
    return 0;
}

int min(int a, int b){
    return a<b?a:b;
}
void JerryAndTom(int start, int end, int m){
    
    int ans = 0;
    while(1){
        int que[100001];
        int rear=0, front=0;
        que[front++] = start;
        int c = MAX;
        memset(visited, 0 ,sizeof(visited));
        while(rear<front){
            int index = que[rear++];
            for(int i=0; i<size[index]; i++){
                int next = arr[index][i];
                if(!visited[next] && cap[index][next] - flow[index][next]>0){
                    que[front++] = next;
                    visited[next] = index;
                    if(next==end) break;
                }
            }
        }
        if(!visited[end]) break;

        for(int i=end; i!=start; i=visited[i]){
            c = min(c, cap[visited[i]][i] - flow[visited[i]][i]);
        }
        for(int i=end; i!=start; i=visited[i]){
            flow[visited[i]][i] += c;
            flow[i][visited[i]] -= c;
        }

        ans += c;
    }
    if(ans==m) printf("Possible");
    else printf("Impossible");
}
int main(void){

    int n,k,h,m;
    scanf("%d %d %d %d", &n, &k, &h, &m);
    int start = 501, end = 502;
    memset(arr, 0 , sizeof(arr));
    memset(size, 0 , sizeof(size));
    memset(flow, 0 , sizeof(flow));
    memset(cap, 0 ,sizeof(cap));

    for(int i=0; i<n; i++){
        scanf("%lld %lld", &corner[i].x ,&corner[i].y);
    }
    for(int i=1; i<=h; i++){
        scanf("%lld %lld", &hole[i].x, &hole[i].y);
    }
    for(int i=1; i<=m; i++){
        scanf("%lld %lld", &mice[i].x, &mice[i].y);
    }
    for(int i=1; i<=m; i++){
        for(int j=1; j<=h; j++){
            if(!intersect(i, j, n)) {
                arr[i][size[i]++] = j+250;
                arr[j+250][size[j+250]++] = i;
                cap[i][j+250] = 1;
            }
        }
    }
    for(int i=1; i<=m; i++){
        arr[start][size[start]++] = i;
        arr[i][size[i]++] = start;
        cap[start][i] = 1;  
    }
    for(int i=1; i<=h; i++){
        arr[i+250][size[i+250]++] = end;
        arr[end][size[end]++] = i+250;
        cap[i+250][end] = k;
    }
    
    JerryAndTom(start, end, m);
}