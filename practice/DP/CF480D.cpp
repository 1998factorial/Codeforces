#include <bits/stdc++.h>
using namespace std;
// Hard DP problem , rating 2600
// condition 1 :
// if parcel[i] is over parcel[j]
// we must have [in[i] , out[i]] is sub interval of [in[j] , out[j]]
// condition 2 :
// to determind whether we can put (w , s) on top of the parcels
// as long as min{s[i] - sum{w[j] , 1 <= j <= i - 1}} >= w
// so we need to maintain such "minimal value" , update by f = min(f - w , s)
// solve for, given our current base is parcel[i] , with f being the strength left
// what is the maximal amount of score we can get ? note that all parcels stacked
// on ith satisfy both con1 and con2, intervals do not overlap
int N , S;
struct parcel{
    int in , out , w , s , v;
} parcels[505];
vector<int> tout[1010];
int DP[505][1010];

int solve(int i , int f){
    if(f < 0 || i > N)return 0;
    int& ret = DP[i][f];
    if(~ret)return ret;
    ret = 0;
    int l = parcels[i].in , r = parcels[i].out , len = r - l + 1;
    vector<int> DP2(len + 1);
    for(int t = 1; t <= len; ++t){
        DP2[t] = max(DP2[t] , DP2[t - 1]);
        for(int j : tout[t + l - 1]){
            int pl = parcels[j].in;
            int w = parcels[j].w;
            int s = parcels[j].s;
            int v = parcels[j].v;
            if(j == i)continue;
            if(pl < l)continue;
            if(f < w)continue;
            int nf = min(f - w , s);
            DP2[t] = max(DP2[t] , DP2[pl - l + 1] + solve(j , nf));
        }
    }
    ret = DP2[len] + parcels[i].v;
    return ret;
}

int main(){
    scanf("%d %d" , &N , &S);
    parcels[0].in = 0; parcels[0].out = 2 * N - 1;
    parcels[0].w = 0; parcels[0].s = S; parcels[0].v = 0;
    for(int i = 1; i <= N; ++i){
        scanf("%d %d %d %d %d" , &parcels[i].in , &parcels[i].out , &parcels[i].w , &parcels[i].s , &parcels[i].v);
        tout[parcels[i].out].push_back(i);
    }
    memset(DP , -1 , sizeof(DP));
    printf("%d\n" , solve(0 , S));
}
