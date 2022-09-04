#include <stdio.h>
#include <stdlib.h>

typedef struct _SHORTEST{
    int **LENGTH;
}SHORTEST;

typedef struct _PATHS{
    int size;
    SHORTEST *shortest;
}PATH;

PATH * CreateShortest(int size){
    PATH * path = (PATH *)malloc(sizeof(PATH));
    path->size = size;
    path->shortest = (SHORTEST *)malloc(size*sizeof(SHORTEST));

    

    for(int i=0; i<size; i++){
        path->shortest[i].LENGTH = (int **)malloc(sizeof(int*)*size);
        
        for(int j=0; j<size; j++){
            path->shortest[i].LENGTH[j] = (int *)malloc(sizeof(int)*size);
            for(int k=0; k<size; k++){ 
            if(j==k) path->shortest[0].LENGTH[j][k]=0;
            else path->shortest[0].LENGTH[j][k]=10000;
            }
        }        
    }
    
    return path;
}

int min(PATH *path, int i, int j, int k, int m, int result){

    if(path->shortest[i-1].LENGTH[j][k]+path->shortest[0].LENGTH[k][m]<result) result = path->shortest[i-1].LENGTH[j][k]+path->shortest[0].LENGTH[k][m];
    return result;
}
void extend_shortest(PATH * path){
    int result=10000;
    
    for(int i=1; i<path->size; i++){
        
        for(int j=0; j<path->size; j++){
            for(int m=0; m<path->size; m++){
                for(int k=0; k<path->size; k++){
                    if(path->shortest[i-1].LENGTH[j][k]==10000||path->shortest[0].LENGTH[k][m]==10000) continue;
                    else if(k==0) result = path->shortest[i-1].LENGTH[j][k]+path->shortest[0].LENGTH[k][m];
                    else result = min(path, i, j, k, m, result);
                }
                path->shortest[i].LENGTH[j][m] = result;
                result = 10000;
                
            }
        }
    }

}

void addEdge(PATH *path, int to, int from, int weight){

    path->shortest[0].LENGTH[to][from]=weight;
}

void printMatrix(int **mat, int rowNum, int colNum){

    for(int i=0; i<rowNum; i++){

        for(int j=0; j< colNum; j++){
            
            printf("%d ",mat[i][j]);
        }
        printf("\n");

    }

}
int main(void){

    PATH * path = CreateShortest(5); 
    
    addEdge(path, 0,1,3);
    addEdge(path, 0,4,-4);
    addEdge(path, 0,2,8);
    addEdge(path, 1,3,1);
    addEdge(path, 1,4,7);
    addEdge(path, 2,1,4);
    addEdge(path, 3,2,-5);
    addEdge(path, 3,0,2);
    addEdge(path, 4,3,6);
    extend_shortest(path);
    printMatrix(path->shortest[4].LENGTH, path->size, path->size);
}
