#include <stdio.h>
#include <string.h>

typedef long long ll;

typedef struct _line{
    ll coe, inter;
    double s;
}line;

ll x[1000001];
ll dp[1000001];
ll s[1000001];
line stack[1000001];

double cross(line x, line y){
    return ((double)(x.inter - y.inter))/((double)(y.coe - x.coe));
}

int main(void){
    int n;
    scanf("%d", &n);
    ll a,b,c;
    scanf("%lld %lld %lld", &a, &b, &c);
    for(int i=1; i<=n; i++){
        scanf("%lld", &x[i]);
    }

    memset(dp, 0 , sizeof(dp));
    memset(s, 0 , sizeof(s));


    for(int i=1; i<=n; i++){
        s[i] = s[i-1] +x[i];
    }

    int top = 0;
    dp[0] = 0;
    for(int i=1; i<=n; i++){
        line temp;
        ll con = a*s[i]*s[i] + b*s[i] + c;
        ll intercept = a*s[i-1]*s[i-1] - b*s[i-1] + dp[i-1];
        temp.coe = -2*a*s[i-1];
        temp.inter = intercept;
        temp.s = 0;
        while(top>0){
            temp.s = cross(temp, stack[top-1]);
            if(stack[top-1].s < temp.s) break;
            top--;
        }   
        stack[top++] = temp;

        int low =0, high = top-1;
        int mid;
        int ans=0;

        while(low<=high){
            mid = (low+high)/2;
            if(s[i]<stack[mid].s) high = mid-1;
            else{
                ans = mid;
                low = mid+1;
            }
        }
   
        dp[i] = stack[ans].coe*s[i] + stack[ans].inter + con;
    }
    printf("%lld\n", dp[n]);
}