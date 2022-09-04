#include <stdio.h>
#include <string.h>

void merge(char a[][51], int *a_count, int a_len, char b[][51], int *b_count, int b_len){

    int a_start=0, b_start=0;
    int temp_a[a_len+1];
    int temp_b[b_len+1];
    char tempword_a[a_len][51];
    char tempword_b[b_len][51];
    temp_a[a_len] = 51;
    temp_b[b_len] = 51;

    for(int i=0; i<a_len; i++){
        temp_a[i] = a_count[i];
        strcpy(tempword_a[i], a[i]);
    }
   
    for(int i=0; i<b_len; i++){
        temp_b[i] = b_count[i];
        strcpy(tempword_b[i], b[i]);
    }
    
    for(int i=0; i<a_len+b_len; i++){

        if(temp_a[a_start]<temp_b[b_start]){
            a_count[i] = temp_a[a_start];
            strcpy(a[i], tempword_a[a_start++]);
            
        }
    
        else if(temp_a[a_start]==temp_b[b_start]){
            int index = strcmp(tempword_a[a_start], tempword_b[b_start]);
            if(index>=0){
                a_count[i] = temp_b[b_start];
                strcpy(a[i], tempword_b[b_start++]);
            }

            else if(index<0){
                a_count[i] = temp_a[a_start];
                strcpy(a[i], tempword_a[a_start++]);
            }

            

        }

        else{
            a_count[i] = temp_b[b_start];
            strcpy(a[i], tempword_b[b_start++]);
        }
    }
    
}

void mergeSort(char arr[][51], int *count, int N){

    if(N==1) return;
    
    if(N%2==0){
    mergeSort(&arr[0], &count[0], N/2);
    mergeSort(&arr[N/2], &count[N/2], N/2 );
    merge(&arr[0], &count[0], N/2, &arr[N/2], &count[N/2], N/2);
    }

    else{
    mergeSort(&arr[0], &count[0], N/2);
    mergeSort(&arr[N/2], &count[N/2], N/2+1 );
    merge(&arr[0], &count[0], N/2, &arr[N/2], &count[N/2], N/2+1);
    }
}
void insertSort(char arr[][51], int *count, int N){
    for(int i=1; i<N; i++){
        int temp=count[i];
        char c[51];
        strcpy(c, arr[i]);
        for(int j=i-1; j>=0; j--){

            if(count[j]<temp){
                count[j+1] = temp;
                strcpy(arr[j+1],c);
                break;
            }

            else if(count[j]==temp){
               int index = strcmp(arr[j], c);
                if(index < 0){
                    
                    count[j+1] = temp;
                    strcpy(arr[j+1], c);
                    break;
                }

                 else if(index>=0){
                    
                    count[j+1] = count[j];
                    strcpy(arr[j+1], arr[j]);
                }
                
            }

            else{
                count[j+1] = count[j];
                strcpy(arr[j+1],arr[j]);
            }

            if(j==0){
                count[j]= temp;
                strcpy(arr[j], c);
            }
        }
    }
}

int main(void){
    
    int N;
    
    scanf("%d", &N);
    char arr[N][51];

    int count[N];
    
    for(int i=0; i<N; i++){
        scanf("%s", arr[i]);
        count[i] = strlen(arr[i]);
        
    }
    
    mergeSort(arr, count, N);
    for(int i=0; i<N; i++){
        if(i!=0){
            if(strcmp(arr[i],arr[i-1])==0) continue;
        }
        printf("%s\n", arr[i]);
    }

}