#include <stdio.h>
#include <string.h>

int main(void){

    char arr[50];
    int temp=0, sum=0;
    int index=1;
    scanf("%s", arr);
    int len = strlen(arr);
    for(int i=0; i<=len; i++){
        if(arr[i]=='-' || i==len){
            if(index == 1) sum += temp;
            else if(index == 0) sum -= temp;
            index =0;
            temp =0;
        }
        else if(arr[i]=='+'){
            if(index == 1) {
                sum +=temp;
                index = 1;
            }
            else if(index ==0) {
                sum -=temp;
                index = 0;
            }
            temp=0;

        }
        else{
            temp = temp*10;
           
            temp += (arr[i]-'0');
           
        }
    }

    printf("%d\n", sum);
    
}

