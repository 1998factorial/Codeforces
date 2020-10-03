#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
const int maxn = 1e6 + 10;
int N;
char op[maxn];
int vis[maxn * 2];

int solve_0(){
    int pos = 0;
    vis[maxn + pos] = 1;
    for(int i = 1; i <= N; ++i){
        if(op[i] == 'R')++pos;
        else --pos;
        ++vis[maxn + pos];
    }
    return vis[maxn + pos] > 1 ? 0 : 1;
}

int check_at_least(int mid){
    DEBUG printf("checking at least %d\n" , mid);
    memset(vis , 0 , sizeof(vis));
    int pos = 0;
    vis[maxn + pos] = 1;
    for(int i = 1; i <= N; ++i){
        if(op[i] == 'R')++pos , ++vis[maxn + pos];
        else{
            if(pos - 1 > mid)--pos , ++vis[maxn + pos];
        }
    }
    DEBUG {
        for(int i = -N; i <= N; ++i)printf("%d (%d) " , vis[maxn + i] , i);
        printf("\n");
    }
    return vis[maxn + pos] > 1 ? 0 : 1;
}

int check_at_most(int mid){
    memset(vis , 0 , sizeof(vis));
    int pos = 0;
    vis[maxn + pos] = 1;
    for(int i = 1; i <= N; ++i){
        if(op[i] == 'R'){
            if(pos + 1 < mid)++pos , ++vis[maxn + pos];
        }
        else{
            --pos , ++vis[maxn + pos];
        }
    }
    DEBUG {
        for(int i = -N; i <= N; ++i)printf("%d (%d) " , vis[maxn + i] , i);
        printf("\n");
    }
    return vis[maxn + pos] > 1 ? 0 : 1;
}

int main(){
    scanf("%s" , op + 1);
    N = strlen(op + 1);
    if(solve_0()){
        printf("1\n");
    }
    else{
        int ret = 0;
        int l = -1 , r = -N , L = 0 , R = 0;
        while(l >= r){
            int mid = (l + r) >> 1;
            if(check_at_least(mid)){
                L = mid;
                l = mid - 1;
            }
            else{
                r = mid + 1;
            }
        }
        l = 1 , r = N;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(check_at_most(mid)){
                R = mid;
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        DEBUG printf("L = %d , R = %d\n" , L , R);
        ret += -L + R;
        printf("%d\n" , ret);
    }
}