#include <bits/stdc++.h>
#define fo(i,a,b) for (int i = (a); i < (b); i++)
#define sz(v) int(v.size())
#define MOD 1000000007
using namespace std;
 
typedef long long ll;
 
int ign[4] = {3, 5, 14, 15};
bool bd[16];
 
int m;
int s[3005];
int f[3005][3005];
int r[3005][3005];
 
int main() {
    scanf("%d", &m);
    int i , j , k;
    for(i = 0; i < 4; ++i)bd[ign[i]] = 1;
    for(i = 0; i < m; ++i)scanf("%d" , &s[i]);
    for(i = 0; i < m; ++i){
        for(j = 0; j < i; ++j){
            if(s[i] == s[j]){
                if(j) f[i][j] = 1 + f[i - 1][j - 1];
                else f[i][j] = 1;
            }
        }
    }
    for(i = 0; i <= m; ++i){
        for(j = i; j <= m; ++j){
            if(i == j) r[i][j] = 1;
            else if(j - i <= 3) r[i][j] = 1 << (j - i - 1);
            else{
                ll mr = 0;
                for(k = j - 3; k < j; ++k){
                    mr += r[i][k];
                }
                int v = 0;
                for(k = j - 4; k < j; ++k) v = (v << 1) | s[k];
                if(!bd[v])mr += r[i][j - 4];
                r[i][j] = mr % MOD;
            }
        }
    }
    ll ret = 0;
    for(i = 0; i < m; ++i){
        int mnl = 1;
        for(j = 0; j < i; ++j)mnl = max(mnl, f[i][j] + 1);
        cout << "max_lcs = " << mnl << endl;
        printf("solving for i = %d we start from %d\n" , i , mnl);
        for(j = mnl; j < i + 2; ++j)ret += r[i - j + 1][i + 1];
        printf("%lld\n", ret % MOD);
    }
}