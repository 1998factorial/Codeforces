#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
int N , cnt[26];
ll g[2][405][405][3][3];

void add(ll& x , ll y){
    x += y;
    if(x >= mod)x -= mod;
}

void sub(ll& x , ll y){
    x -= y;
    if(x < 0)x += mod;
}

void mul(ll& x , ll y){
    x *= y;
    x %= mod;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < 26; ++i){
        cin >> cnt[i];
    }
    // avoid making palindrome of length 3
    // we are going to run out of at most 2 kinds of characters
    ll total = 26 * 26;
    for(int i = 1; i <= N - 2; ++i){
        mul(total , 25ll);
    }
    for(int i = 0; i < 26; ++i){
        for(int j = 0; j < 26; ++j){
            for(int k = 0; k < 26; ++k){
                if(i != k){
                    multiset<int> v;
                    v.insert(i);
                    v.insert(j);
                    v.insert(k);
                    int x = 0 , y = 0;
                    if(j == 0)x = 1;
                    if(j == 1)x = 2;
                    if(k == 0)y = 1;
                    if(k == 1)y = 2;
                    ++g[3 & 1][v.count(0)][v.count(1)][x][y];
                }    
            }
        }
    }
    // 1 -> a , 2 -> b , 0 -> else 
    for(int i = 3; i < N; ++i){
        for(int j = 0; j <= i + 1; ++j){
            for(int k = 0; k + j <= i + 1; ++k){
                for(int x = 0; x < 3; ++x){
                    for(int y = 0; y < 3; ++y){
                        g[(i + 1) & 1][j][k][x][y] = 0;
                    }
                }
            }
        }
        for(int j = 0; j <= i; ++j){
            for(int k = 0; k + j <= i; ++k){
                for(int x = 0; x < 3; ++x){
                    for(int y = 0; y < 3; ++y){
                        if(x == 0){
                            // put non a non b
                            add(g[(i + 1) & 1][j][k][y][0] , g[i & 1][j][k][x][y] * 23 % mod);
                            // put a
                            add(g[(i + 1) & 1][j + 1][k][y][1] , g[i & 1][j][k][x][y]);
                            // put b
                            add(g[(i + 1) & 1][j][k + 1][y][2] , g[i & 1][j][k][x][y]);
                        }
                        if(x == 1){
                            // put non a non b
                            add(g[(i + 1) & 1][j][k][y][0] , g[i & 1][j][k][x][y] * 24 % mod);
                            // put b
                            add(g[(i + 1) & 1][j][k + 1][y][2] , g[i & 1][j][k][x][y]);
                        }
                        if(x == 2){
                            // put non a non b
                            add(g[(i + 1) & 1][j][k][y][0] , g[i & 1][j][k][x][y] * 24 % mod);
                            // put a
                            add(g[(i + 1) & 1][j + 1][k][y][1] , g[i & 1][j][k][x][y]);
                        }
                    }
                }
            }
        }
    }
    // run out of at least 1 type
    for(int i = 0; i < 26; ++i){
        for(int j = cnt[i] + 1; j <= N; ++j){
            for(int k = 0; k + j <= N; ++k){
                for(int x = 0; x < 3; ++x){
                    for(int y = 0; y < 3; ++y){
                        sub(total , g[N & 1][j][k][x][y]);
                    }
                }
            }
        }
    }
    // run out of exactly 2 types
    for(int i = 0; i < 26; ++i){
        for(int j = i + 1; j < 26; ++j){
            for(int l = cnt[i] + 1; l <= N; ++l){
                for(int k = cnt[j] + 1; k + l <= N; ++k){
                    for(int x = 0; x < 3; ++x){
                        for(int y = 0; y < 3; ++y){
                            add(total , g[N & 1][l][k][x][y]);
                        }
                    }
                }
            }
        }
    }
    cout << total << endl;
}