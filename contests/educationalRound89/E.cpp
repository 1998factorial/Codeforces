#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int maxn = 2e5 + 10;
int a[maxn] , b[maxn];
map<int , int> pos;
int N , M;

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int j = 1; j <= M; ++j){
        scanf("%d" , &b[j]);
    }
    for(int i = 1; i <= N; ++i){
        pos[a[i]] = i;
    }
    for(int j = 1; j < M; ++j){
        if(pos[b[j]] == 0){
            printf("0\n");
            return 0;
        }
        if(pos[b[j]] > pos[b[j + 1]]){
            printf("0\n");
            return 0;
        }
    }
    if(pos[b[M]] == 0){
        printf("0\n");
        return 0;
    }
    ll ret = 1;
    // find largest i st a[i] < b[j]
    for(int i = 1; i < pos[b[1]]; ++i){
        if(a[i] < b[1]){
            printf("0\n");
            return 0;
        }
    }
    // b[i] .. b[i + 1]
    for(int i = 1; i < M; ++i){
        int j = pos[b[i]];
        int id = -1;
        int right = pos[b[i + 1]];
        for(; j < right; ++j){
            if(a[j] < b[i]){
                printf("0\n");
                return 0;
            }
            if(a[j] < b[i + 1]){
                id = j;
            }
        }
        if(id != -1)ret = ret * (pos[b[i + 1]] - id) % mod;
    }
    for(int i = pos[b[M]]; i <= N; ++i){
        if(a[i] < b[M]){
            printf("0\n");
            return 0;
        }
    }
    printf("%lld\n" , ret);
}
