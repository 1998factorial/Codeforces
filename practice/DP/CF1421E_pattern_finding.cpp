#include <bits/stdc++.h>
using namespace std;
// Hard DP problem , rating 2700
// this is a brute force to find good patterns in problem CF1421E
const int maxn = 22;
int DP[1 << maxn][maxn];
bool vis[1 << maxn][maxn];

int check(int mask , int N){
    if(N == 1)return mask == 0;
    if(N == 2)return mask == 3;
    int& ret = DP[mask][N];
    if(vis[mask][N])return ret;
    vis[mask][N] = 1;
    for(int m = 0; m < N - 1; ++m){
        int mask1 = 0 , mask2 = 0 , n1 = m + 1 , n2 = N - m - 1;
        for(int i = 0; i <= m; ++i){
            if(mask >> i & 1)continue;
            mask1 |= (1 << i);
        }
        for(int i = m + 1; i < N; ++i){
            if(mask >> i & 1)continue;
            mask2 |= (1 << (i - n1));
        }
        ret |= check(mask1 , n1) && check(mask2 , n2);
    }
    return ret;
}

vector<string> v[22];

int main(){
    int N;
    cin >> N;
    set<int> nneg;
    for(int mask = 0; mask < 1 << N; ++mask){   
        if(check(mask , N)){
            string a = "";
            for(int i = 0; i < N; ++i){
                if(mask >> i & 1)a += '-';
                else a += '+';
            }
            cout << a << endl;
            v[__builtin_popcount(mask)].push_back(a);
            nneg.insert(__builtin_popcount(mask) % 3);
            //cout << "number of -1 = " << __builtin_popcount(mask) << endl;
        }
    }
    cout << "show number of negative ones : ";
    for(int i : nneg)cout << i << " ";
    cout << endl;
    /*for(int i = 0; i <= N; ++i){
        if(v[i].empty())continue;
        cout << "show # of -1 = " << i << endl;
        for(auto& x : v[i]){
            cout << x << endl;
        }
    }*/
}