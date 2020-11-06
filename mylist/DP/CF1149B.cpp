#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int INF = 1e9;
int len[4] , N , Q;
char a[4][255];
char s[100005];
vector<int> pos[26];
int DP[255][255][255] , nex[100005][26];
bool vis[255][255][255];

int solve(int len1 , int len2 , int len3){
    int& ret = DP[len1][len2][len3];
    if(vis[len1][len2][len3])return ret;
    if(len1){
        int v1 = solve(len1 - 1 , len2 , len3);
        if(v1 <= N)ret = min(ret , nex[v1 + 1][a[1][len1] - 'a']);
    }
    if(len2){
        int v2 = solve(len1 , len2 - 1 , len3);
        if(v2 <= N)ret = min(ret , nex[v2 + 1][a[2][len2] - 'a']);
    }
    if(len3){
        int v3 = solve(len1 , len2 , len3 - 1);
        if(v3 <= N)ret = min(ret , nex[v3 + 1][a[3][len3] - 'a']);
    }
    vis[len1][len2][len3] = 1;
    return ret;
}

void init(){
    for(int i = 0; i <= 250; ++i){
        for(int j = 0; j <= 250; ++j){
            for(int k = 0; k <= 250; ++k){
                DP[i][j][k] = INF;
                vis[i][j][k] = 0;
            }
        }
    }
    for(int j = 0; j < 26; ++j){
        for(int i = 0; i <= 100000; ++i){
            nex[i][j] = INF;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    init();
    cin >> N >> Q;
    cin >> (s + 1);
    for(int i = 1; i <= N; ++i){
        int c = s[i] - 'a';
        pos[c].push_back(i);
    }
    for(int j = 0; j < 26; ++j){
        int k = 0;
        for(int i = 0; i <= N; ++i){
            while(k < pos[j].size() && pos[j][k] < i)++k;
            if(k < pos[j].size())nex[i][j] = pos[j][k];
        }
    }
    DP[0][0][0] = 0;
    for(int i = 1; i <= 3; ++i)len[i] = 0;
    while(Q--){
        char op , v;
        int x; 
        cin >> op;
        if(op == '+'){
            cin >> x >> v;
            ++len[x];
            a[x][len[x]] = v;
            solve(len[1] , len[2] , len[3]);
        }
        else{
            cin >> x;
            if(x == 1){
                for(int i = 0; i <= len[2]; ++i){
                    for(int j = 0; j <= len[3]; ++j){
                        DP[len[1]][i][j] = INF;
                        vis[len[1]][i][j] = 0;
                    }
                }
            }   
            if(x == 2){
                for(int i = 0; i <= len[1]; ++i){
                    for(int j = 0; j <= len[3]; ++j){
                        DP[i][len[2]][j] = INF;
                        vis[i][len[2]][j] = 0;
                    }
                }
            }
            if(x == 3){
                for(int i = 0; i <= len[1]; ++i){
                    for(int j = 0; j <= len[2]; ++j){
                        DP[i][j][len[3]] = INF;
                        vis[i][j][len[3]] = 0;
                    }
                }
            }
            --len[x];
        }
        if(DP[len[1]][len[2]][len[3]] <= N)cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}