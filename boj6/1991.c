#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N;

typedef struct _NODE{
    struct _NODE *left;
    struct _NODE *right;
    char name;
}NODE;

typedef struct _TREE{
    NODE *node;
}TREE;

TREE * makeTree(int V){
    TREE * tree = (TREE*)malloc(sizeof(TREE)*(V+1));
    for(int i=1; i<=V; i++){
        tree[i].node = (NODE *)malloc(sizeof(NODE));
        tree[i].node->left = NULL;
        tree[i].node->right = NULL;
        tree[i].node->name = 'A'+(i-1);
    }
    return tree;
}

void preOrder(TREE *tree, char index){
    printf("%c", tree[index-'A'+1].node->name);
    if(tree[index-'A'+1].node->left!=NULL)preOrder(tree, tree[index-'A'+1].node->left->name);
    if(tree[index-'A'+1].node->right!=NULL)preOrder(tree, tree[index-'A'+1].node->right->name);
}
void inOrder(TREE * tree, int index){
   
    if(tree[index-'A'+1].node->left!=NULL) inOrder(tree, tree[index-'A'+1].node->left->name);
     printf("%c", tree[index-'A'+1].node->name);
    if(tree[index-'A'+1].node->right!=NULL) inOrder(tree, tree[index-'A'+1].node->right->name);
}
void postOrder(TREE *tree, int index){
    if(tree[index-'A'+1].node->left!=NULL) postOrder(tree, tree[index-'A'+1].node->left->name); 
    if(tree[index-'A'+1].node->right!=NULL) postOrder(tree, tree[index-'A'+1].node->right->name);
    printf("%c", tree[index-'A'+1].node->name);
}
int main(void){

    scanf("%d", &N);
    TREE *tree = makeTree(N);
    getchar();
    for(int i=1; i<=N; i++){
        char a, b, c;
        scanf("%c %c %c", &a, &b, &c);
        getchar();
        if(b!='.') tree[a-'A'+1].node->left = tree[b-'A'+1].node;
        if(c!='.') tree[a-'A'+1].node->right = tree[c-'A'+1].node; 
    }
    preOrder(tree, 'A');
    printf("\n");
    inOrder(tree, 'A');
    printf("\n");
    postOrder(tree, 'A');
    printf("\n");
}