#include <stdio.h>
#include <string.h>

int dp[14][1<<14];

int bitcheck(int bitmask , int index){
    if((bitmask&(1<<index)) == (1<<index)) return 0;
    else return 1;
}

int bitNest(int bitmask,  int index){
    return bitmask | (1<<index);
}

int judge(int bitmask, int M ){
    
    int zero=0;
    
    for(int i=0; i<M; i++){
        
        if(bitcheck(bitmask, i)) zero++;
        else {
            if(zero!=0 && zero%2==1) return 0;
            else zero=0;
        }
    }
    if(zero!=0 && zero%2==1) return 0;
    return 1;
}
int tears(int row, int bitmask, int N, int M){
    
    int sum = 0;
    if(row==N-1) return judge(bitmask, M);
    if(dp[row][bitmask]!=-1) return dp[row][bitmask];
    
    int que_bit[1<<18];
    int que_index[1<<18];
    int rear = 0, front = 0;
    que_bit[front] = 0;
    que_index[front++] = 0;
    while(rear<front){
        
        int bit = que_bit[rear];
        int index = que_index[rear++];

        if(index>=M) sum =  (sum + tears(row+1, bit, N, M))%9901;
        else if(bitcheck(bitmask, index)){
            que_bit[front] = bitNest(bit, index);
            que_index[front++] = index+1;
            if(index<M-1 && bitcheck(bitmask, index+1)){
                que_bit[front] = bit;
                que_index[front++] = index+2;
            }
        }
        else{
            que_bit[front] = bit;

            que_index[front++] = index+1;
        }
    }
    dp[row][bitmask] = sum;
    return dp[row][bitmask];
}

int main(void){

    int N,M;
    scanf("%d %d", &N, &M);
    memset(dp, -1, sizeof(dp));
    if((N*M)%2==1) {
        printf("0\n");
    }
    else{
        printf("%d\n",tears(0, 0, N, M));
    }
    
   
}