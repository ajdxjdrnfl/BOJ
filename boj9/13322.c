#include <stdio.h>
#include <string.h>

int main(void){
    char str[100010];
    scanf("%s", str);
    int n = strlen(str);
    for(int i=0; i<n; i++){
        printf("%d\n",i);
    }
}