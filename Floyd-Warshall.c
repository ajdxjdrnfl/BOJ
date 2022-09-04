#include <stdio.h>
#include <stdlib.h>

typedef struct _SHORTEST{
    int **LENGTH;
}SHORTEST;

typedef struct _PATH{
    int size;
    SHORTEST *arr;
}PATH;

int w[5][5];

PATH * createPath(int size){

    PATH * path = (PATH *)malloc(sizeof(PATH));
    path->size = size;

    path->arr = (SHORTEST *)malloc(sizeof(SHORTEST)*size);

    for(int i=0; i<size; i++){
        path->arr[i].LENGTH =(int **)malloc(sizeof(int *)*size);
        for(int j=0; j<size; j++){
            path->arr[i].LENGTH[j] =(int *)malloc(sizeof(int)*size);
            for(int k=0; k<size; k++){
                if(j==k)w[j][k] =0;
                else w[j][k] = 10000; 
            }
        }

    }

    return path;
}

void addEdge(PATH * path, int to, int from, int weight){

    w[to][from] = weight;
}

void min(PATH *path, int i, int j, int k){
    
    if(k==0){
        if(w[i][j]<w[i][k]+w[k][j]) path->arr[k].LENGTH[i][j] = w[i][j];
        else path->arr[k].LENGTH[i][j] = w[i][k]+w[k][j];
        return;
    }
    if(path->arr[k-1].LENGTH[i][j]<path->arr[k-1].LENGTH[i][k]+path->arr[k-1].LENGTH[k][j]) path->arr[k].LENGTH[i][j] = path->arr[k-1].LENGTH[i][j];
    else path->arr[k].LENGTH[i][j] = path->arr[k-1].LENGTH[i][k] + path->arr[k-1].LENGTH[k][j];

}

void floyd_warshall(PATH * path){

    for(int k=0; k<path->size; k++){
        
        for(int i=0; i<path->size; i++){
            for(int j=0; j<path->size; j++){
                
                min(path, i, j, k);
                
            }
        }

    }
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
    PATH * path = createPath(5);
    addEdge(path, 0,1,3);
    addEdge(path, 0,4,-4);
    addEdge(path, 0,2,8);
    addEdge(path, 1,3,1);
    addEdge(path, 1,4,7);
    addEdge(path, 2,1,4);
    addEdge(path, 3,2,-5);
    addEdge(path, 3,0,2);
    addEdge(path, 4,3,6);
    
    floyd_warshall(path);
    printMatrix(path->arr[4].LENGTH, path->size, path->size);
}