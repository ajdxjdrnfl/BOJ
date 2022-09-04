#include<stdio.h>
#include<stdlib.h>

void merge(int *a, int a_len, int *b, int b_len){

    int a_start=0;
    int b_start=0;

    int temp_a[a_len+1];
    int temp_b[b_len+1];
    temp_a[a_len]=99999;
    temp_b[b_len]=99999;

    
    for(int i=0; i<a_len; i++){
        temp_a[i]=a[i];
    }
    for(int i=0; i<b_len; i++){
        temp_b[i]=b[i];
    }

    for(int i=0; i<a_len+b_len; i++){
        if(temp_a[a_start]<temp_b[b_start]){
            a[i]=temp_a[a_start++];
        }
        else{
            a[i]=temp_b[b_start++];
        }
    }


}

void mergeSort(int * arr, int N){

    if(N==1) return;

    if(N%2==0){
    mergeSort(arr, N/2);
    mergeSort(arr+N/2, N/2);
    merge(arr, N/2, arr+N/2, N/2);
    }

    else{

        mergeSort(arr, N/2);
        mergeSort(arr+N/2, N/2+1);
        merge(arr, N/2, arr+N/2, N/2+1);
    }
    

}

int average(int *arr, int N){
    double sum=0.0f;

    for(int i=0; i<N; i++){
        sum+=(double)arr[i];
    }
    return (int)(sum/N+0.5);

}
int arith(int *list, int n)
{
	double sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += (list[i]);
	}
	sum /= n;
	if (sum < 0)
		sum -= 0.5;
	else
		sum += 0.5;

	return (int)sum;
}

int sansool(int *arr, int N){
    double sum=0;
    double avg;
    for(int i=0; i<N; i++){
        sum+=(double)arr[i];
    }
    avg = (double)sum/N;
    int  check = ((int)(avg*10.0))%10;
    if(check == 0 ||check == 1 ||check == 2 ||check == 3 ||check == 4 ) return (int)avg;

    else {
        if(sum>=0) return ((int)avg)+1;
        else return ((int)avg)-1;
    }
   
}

int main(void){

    int N,avg,mid,mode,range;
    int save=0, index=0;
    int *arr;
    int *count;
    int countNum=0;
    int largest=-1;  
    int mod[8001]={0,};  
    int max=0, maxI=0;
    scanf("%d",&N);

    arr = (int *)malloc(sizeof(int)*N);
    count = (int *)malloc(sizeof(int)*N);
    for(int i=0;i<N; i++){
        scanf("%d",&arr[i]);
    }

    avg = arith(arr, N);
    mergeSort(arr, N);
    mid =  arr[(N+1)/2-1];
    range = arr[N-1] - arr[0];
    
    for(int i=0; i<N; i++){
        if(i==0){
            save = arr[i];
            count[i]=0;
            countNum++;
        }
        else if(save != arr[i]){
            count[i-1] = countNum;
            count[i]=0;
            save = arr[i];
            index = i;
            countNum = 1;

        }
        else if(save == arr[i]){
            count[i]=0;
            countNum++;
        }

        if(i==N-1){
            count[i]=countNum;
        }
    }

    for(int i=0; i<N; i++){
        if(count[i] == 0){
            continue;           
        }
        else if(largest<count[i]){
            largest = count[i];
            mode = arr[i];
            index=1;
        }
        else if(largest==count[i]){
            if(index!=2){
            index++;
            mode = arr[i];
            }
            else{
                continue;
            }
        }
        
    }
    
   /*
    for(int i=0; i<N; i++){
        mod[4000+arr[i]]++;
    }

    for(int i=0; i<8001; i++){
        if(max<mod[i]) max = mod[i];
    }

    for(int i=0; i<8001; i++){
        if(mod[i]==max) {
            mode = i-4000;
            maxI++;}

        if(maxI == 2){
            break;
        }
    }
    */
    printf("%d\n", avg);
    printf("%d\n", mid);
    printf("%d\n", mode);
    printf("%d\n", range);

    
}