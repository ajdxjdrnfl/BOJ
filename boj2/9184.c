#include <stdio.h>


int dynamic[101][101][101]={0,};
int w(int a, int b, int c){
    
    if(dynamic[50+a][50+b][50+c]!=0) return dynamic[50+a][50+b][50+c];
    
    else if(a<=0 || b<=0 || c<=0){
        return 1;
    }

    else if(a>20 || b>20 || c>20){
        return w(20, 20, 20);
    }

    else if(a<b && b<c){
        
        dynamic[50+a][50+b][50+c] = w(a,b,c-1) + w(a,b-1,c-1) - w(a,b-1,c);
        return dynamic[50+a][50+b][50+c];
    }
    
    else{
        dynamic[50+a][50+b][50+c] =w(a-1,b,c)+w(a-1, b-1, c) + w(a-1, b,c-1) - w(a-1, b-1, c-1);
        return dynamic[50+a][50+b][50+c];
    }
    


}
int main(void){
    int a=0,b=0,c=0;
    
    while(a!=-1 || b!=-1 || c!=-1){

        scanf("%d %d %d", &a,&b,&c);
        if(a==-1 && b==-1 && c==-1) break;
        printf("w(%d, %d, %d) = %d\n", a,b,c,w(a,b,c));
        
    }
}