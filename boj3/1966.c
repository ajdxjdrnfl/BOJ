#include <stdio.h>


int que[100];
int front=0, back=0;

int size(){
    return front-back;
}
int empty(){
    if(front==back) return 1;
    else return 0;
}

void push(int num){
    que[front++] = num;

}

int pop(){
    if(empty()==1) return -1;
    else return que[++back];
}

int main(void){

    int caseN;
    int N, M;
    
    scanf("%d", &caseN);
    for(int i=0; i<caseN; i++){
        int cnt=0;
        front=0, back=0;
        scanf("%d %d", &N, &M);
        for(int j=0; j<N; j++){
            int temp;
            scanf("%d", &temp);
            push(temp);
        }
        while(1){
        int max=0;
        for(int j=0; j<N; j++){
            if(max<que[j]) max = que[j];
        }
        while(que[back]!=max){
            back = (back+1)%N;
        }
        if(back == M){
            cnt++;
            printf("%d\n",cnt);
            break;
        }
        que[back] = 0;
        back = (back+1)%N;
        cnt++;
    }
    }

    
}