#include <stdio.h>
#include <string.h>

typedef struct _SHARK{
    long long size;
    long long speed;
    long long intelli;
    int eaten;
}SHARK;

SHARK jaws[51];
int visited[51];
int match[51];

int bigger(SHARK a, SHARK b){
    return (a.size>=b.size && a.speed>= b.speed && a.intelli>=b.intelli);
}

int same(SHARK a, SHARK b){
    return (a.size==b.size && a.speed== b.speed && a.intelli==b.intelli);
}

int parent(int index, int p){
    while(p!=jaws[index].eaten) {
        if(index!=jaws[index].eaten) index = jaws[index].eaten;
        else return 0;
    }
    return 1;
}
int bipartie(int index, int N){

    if(visited[index]) return 0;
    visited[index] = 1;
    for(int i=1; i<=N; i++){
        
        if(i != index && bigger(jaws[index], jaws[i])){

            if(same(jaws[index], jaws[i]) && parent(index, i) ) continue;

            if(!match[i]){
                match[i] = index;
                if(same(jaws[index], jaws[i])) jaws[i].eaten = index;
                return 1;
            }
            
            else if(bipartie(match[i], N)){
                if(same(jaws[match[i]], jaws[i])) jaws[i].eaten = i;
                match[i]=index;
                if(same(jaws[index], jaws[i])) jaws[i].eaten = index;
                return 1;
            }
            
        }
    }
    return 0;
}  
int main(void){
    int N;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%lld %lld %lld", &jaws[i].size, &jaws[i].speed, &jaws[i].intelli);
        jaws[i].eaten = i;
    }
    
    memset(match, 0 , sizeof(match));
    for(int i=1; i<=N; i++){
        memset(visited, 0, sizeof(visited));
        bipartie(i, N);
        memset(visited, 0, sizeof(visited));
        bipartie(i, N);
    }
    int ans=0;
    
    for(int i=1; i<=N; i++){
        if(!match[i]) ans++;
    }
    
    printf("%d\n", ans);


    
}