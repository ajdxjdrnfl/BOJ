#include <stdio.h>
#include <string.h>

int grade[5][5] ={
    {10, 8, 7, 5, 1},
    {8, 6, 4, 3, 1},
    {7, 4, 3, 2, 1},
    {5, 3, 2, 2, 1},
    {1,1,1,1,0}
};

int tofu[14][14];

int dp[14][1<<14];

int bitcheck(int bitmask, int index){
    if((bitmask&(1<<index)) == (1<<index)) return 0;
    return 1;
}

int bitNest(int bitmask, int index){
    return (bitmask | (1<<index));
}
int max(int a, int b){
    return a>b?a:b;
}
int hongjun(int row, int bitmask, int N, int M){
    
    if(row==N) return 0;
    if(dp[row][bitmask]!=-1) return dp[row][bitmask];

    int answer=-1;
    int que_bit[1<<18];
    int que_index[1<<18];
    int que_cost[1<<18];
    int rear=0, front=0;
    que_bit[front] = 0;
    que_index[front] = 0;
    que_cost[front++] = 0;
    while(rear<front){
        int bit = que_bit[rear];
        int index = que_index[rear];
        int cost = que_cost[rear++];
        if(index>=M) answer = max(answer, cost + hongjun(row+1, bit , N, M)); 
        else if(bitcheck(bitmask, index) ){
            que_bit[front] = bit;
            que_index[front] = index+1;
            que_cost[front++] = cost;

            if(row!=N-1){
                que_bit[front] = bitNest(bit, index);
                que_index[front] = index+1;
                que_cost[front++] = cost + grade[tofu[row][index]][tofu[row+1][index]];
            }
            if(index<M-1 && bitcheck(bitmask, index+1)){
                que_bit[front] = bit;
                que_index[front] = index+2;
                que_cost[front++] = cost + grade[tofu[row][index]][tofu[row][index+1]];
            }
        }
        else{
            que_bit[front] = bit;
            que_index[front] = index+1;
            que_cost[front++] = cost;
        }
    }
    
    dp[row][bitmask] = answer;
    return dp[row][bitmask];
}
int main(void){

    int N,M;
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        char s[100];
        scanf("%s", s);
        for(int j=0; j<M; j++){
            if(s[j]!='F') tofu[i][j] = s[j] - 'A';
            else tofu[i][j] = s[j] - 'A' - 1;
        }
    }
    
    memset(dp, -1, sizeof(dp));
    printf("%d\n", hongjun(0, 0, N, M));
}