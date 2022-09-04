#include <stdio.h>
#include <string.h>
typedef struct _POINT{
    int x;
    int y;
}POINT;


int main(void){
    int test;
    scanf("%d", &test);
    while(test--){
        int size;
        int que[90001];
        int rear=0, front=0;
        int visited[300][300];
        memset(visited, 0, sizeof(visited));
        memset(que, 0, sizeof(que));
        scanf("%d", &size);
        POINT knight;
        POINT object;
        scanf("%d %d", &knight.x, &knight.y);
        scanf("%d %d", &object.x, &object.y);

        que[front++] = knight.x*size + knight.y;

        while(rear<front){
            int temp = que[rear++];
            int i = temp/size;
            int j = temp%size;
            
            if(object.x == i && object.y == j){
                printf("%d\n", visited[i][j]);
                break;
            }
            if(i+2<size && j+1<size && visited[i+2][j+1]==0){
                que[front++] = (i+2)*size + j+1;
                visited[i+2][j+1]  = visited[i][j] +1;
            }
            if(i+1<size && j+2<size && visited[i+1][j+2]==0){
                que[front++] = (i+1)*size + j+2;
                visited[i+1][j+2] = visited[i][j]+1;
            }
            if(i+2<size && j-1>=0 && visited[i+2][j-1]==0){
                que[front++] = (i+2)*size + j-1;
                visited[i+2][j-1] = visited[i][j]+1;
            }
            if(i+1<size && j-2>=0 && visited[i+1][j-2]==0){
                que[front++] = (i+1)*size + j-2;
                visited[i+1][j-2] = visited[i][j]+1;
            }
            if(i-1>=0 && j-2>=0 && visited[i-1][j-2]==0){
                que[front++] = (i-1)*size + j-2;
                visited[i-1][j-2] = visited[i][j] +1;
            }
            if(i-2>=0 && j-1>=0 && visited[i-2][j-1]==0){
                que[front++] = (i-2)*size + j-1;
                visited[i-2][j-1] = visited[i][j]+1;
            }
            if(i-2>=0 && j+1<size && visited[i-2][j+1]==0){
                que[front++] = (i-2)*size + j+1;
                visited[i-2][j+1] = visited[i][j]+1;
            }
            if(i-1>=0 && j+2<size && visited[i-1][j+2]==0){
                que[front++] = (i-1)*size + j+2;
                visited[i-1][j+2] = visited[i][j]+1;
            }
            
        }
    }
    return 0;
}