#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stableMerge(int *age_a, char name_a[][101], int a_len, int *age_b, char name_b[][101], int b_len){

    int a_start=0, b_start=0;

    char tempname_a[a_len][101], tempname_b[b_len][101];
    int tempage_a[a_len+1], tempage_b[b_len+1];
    tempage_a[a_len] = 201;
    tempage_b[b_len] = 201;

    for(int i=0; i<a_len; i++){

        tempage_a[i] = age_a[i];
        strcpy(tempname_a[i],name_a[i]);
    }

    for(int i=0; i<b_len; i++){
        tempage_b[i] = age_b[i];
        strcpy(tempname_b[i], name_b[i]);
    }

    for(int i=0; i<a_len+b_len; i++){

        if(tempage_a[a_start]<=tempage_b[b_start]){
            age_a[i] = tempage_a[a_start];
            strcpy(name_a[i], tempname_a[a_start++]);
        }

        else{
            age_a[i] = tempage_b[b_start];
            strcpy(name_a[i], tempname_b[b_start++]);
        }
    }
}

void stableMergeSort(int *age, char name[][101], int N){

    if(N==1) return;

    if(N%2==0){
        stableMergeSort(&age[0], &name[0], N/2);
        stableMergeSort(&age[N/2], &name[N/2], N/2);
        stableMerge(&age[0], &name[0], N/2,&age[N/2], &name[N/2], N/2);
    }

    else{
        stableMergeSort(&age[0], &name[0], N/2);
        stableMergeSort(&age[N/2], &name[N/2], N/2+1);
        stableMerge(&age[0], &name[0], N/2,&age[N/2], &name[N/2], N/2+1);
    }
}

void stableSort(int *age, char name[][101], int N){
    
    for(int i=1; i<N; i++){
        int temp = age[i];
        char c[101];
        strcpy(c, name[i]);
        for(int j=i-1; j>=0; j--){

            if(temp>=age[j]){
                age[j+1] = temp;
                strcpy(name[j+1],c);
                break;
            }


            else{
                age[j+1] = age[j];
                strcpy(name[j+1], name[j]);
            }

            if(j==0){
                age[j] = temp;
                strcpy(name[j], c);
            }
        }
    }

}


int main(void){

    
    int *age;
    int N;
    
    scanf("%d", &N);
    char name[N][101]; 
    age = (int *)malloc(sizeof(int)*N);

    for(int i=0; i<N; i++){

        scanf("%d %s", &age[i], name[i]);
    }
    stableMergeSort(age, name, N);
    for(int i=0; i<N; i++){

        printf("%d %s\n", age[i],name[i]);
    }
}