#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5 + 10;
int DP[maxn][3];
int x , y , z , N;
ll a[maxn];
int period;
int scale = 125;

int mex(vector<int> b){
    int ret = -1;
    set<int> s;
    for(int i : b)s.insert(i);
    for(int i = 0; i <= s.size(); ++i){
        if(s.find(i) == s.end()){
            ret = i;
            break;
        }
    }
    return ret;
}

int get(int which , ll at){
    if(at < scale){
        return DP[at][which];
    }
    return DP[(at - scale) % period + scale][which];
}

int solve(){
    period = -1;
    memset(DP , 0 , sizeof(DP));
    for(int i = 1; i <= 1000 && period == -1; ++i){
        int nx = max(0 , i - x);
        int ny = max(0 , i - y);
        int nz = max(0 , i - z);
        DP[i][0] = mex({DP[nx][0] , DP[ny][1] , DP[nz][2]});
        DP[i][1] = mex({DP[nx][0] , DP[nz][2]});
        DP[i][2] = mex({DP[nx][0] , DP[ny][1]});
        if(i > scale){
            bool ok = 1;
            for(int j = 0; j < 5; ++j){
                for(int k = 0; k < 3; ++k){
                    ok &= DP[i - j][k] == DP[scale - j][k];
                }
            }
            if(ok){
                period = i - scale;
            }
        }
    }
    int ret = 0;
    ll S = 0;
    for(int i = 1; i <= N; ++i){
        S ^= get(0 , a[i]);
    }
    for(int i = 1; i <= N; ++i){
        S ^= get(0 , a[i]);
        if((S ^ get(0 , max(0ll , a[i] - x))) == 0)++ret;
        if((S ^ get(1 , max(0ll , a[i] - y))) == 0)++ret;
        if((S ^ get(2 , max(0ll , a[i] - z))) == 0)++ret;
        S ^= get(0 , a[i]);
    }
    return ret;
}


int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d %d %d %d" , &N , &x , &y , &z);
        for(int i = 1; i <= N; ++i){
            scanf("%lld" , &a[i]);
        }
        printf("%d\n" , solve());
    }
}
