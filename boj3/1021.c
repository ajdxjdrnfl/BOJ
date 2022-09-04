#include <stdio.h>
#define MAX_SIZE 51
int count=0;
int que[MAX_SIZE];
int back=-1, front=-1;
int N;
int empty(){
    if(count==0) return 1;
    else return 0;

}
int pop(){
    if(empty()==1) return -1;
    else {
        count--;
        back = (back+1)%N;
        int temp = que[back];
        que[back]=0;
        if(count!=0){
        while(que[(back+1)%N]==0){
            back = (back+1)%N;
        }
        }
        return temp;
    }
}

void push(int num){
    count++;
    front = (front+1)%N;
    que[front] = num;
}

int main(void){
    int M;
    int result=0;
    scanf("%d %d", &N, &M);
    back=N-1, front=N-1;
    for(int i=1;i<=N; i++){
        push(i);
    }
    int arr[M];
    for(int i=0; i<M; i++){
        scanf("%d", &arr[i]);
    }

    for(int i=0; i<M; i++){

        int temp_left=back;
        int temp_right=back;
        int left=0, right=0;
        while(arr[i]!=que[(temp_left+1)%N]){
            if(que[(temp_left+1)%N]!=0) left++;
            temp_left=(temp_left-1+N)%N;
        }
        right = N-i-left;
        if(left<right) {
            back = temp_left;
            pop();
            result+=left;
        }
        else {
            back = temp_left;
            pop();
            result+=right;
        }

        /*
        int temp_left, temp_right;
        int left=0, right=0;
        int left_cnt=0, right_cnt=0;
        int zero_left=0, zero_right=0;
        
        temp_left =back;
        temp_right = back;
        if(que[(back+1)%N]==0) {
            zero_left=-1;
            zero_right=-1;
        }
    
        while(arr[i]!=que[(temp_left+1)%N]){
            if(que[(temp_left+1)%N]!=0) left++;
            left++;
            temp_left = (temp_left-1+N)%N;
            
        }
        while(arr[i]!=que[(temp_right+1)%N]){
            if(que[(temp_right+1)%N]==0) zero_right++;
            right++;
            temp_right = (temp_right+1)%N;
        }
        printf("back : %d  \n", back);
        printf("left : %d  right : %d \n", left, right);
        printf("left_zero : %d  right_zero : %d \n", zero_left, zero_right);    
        if(left-zero_left<right-zero_right) {
            front = (front - left +N)%N;
            back = (back - left+N)%N;
            pop();
            result += (left-zero_left);
        }
        else {
            front = (front + right)%N;
            back = (back + right )%N;
            pop();
            result +=(right-zero_right);
        }
        */
    }
    printf("%d", result);
    
}