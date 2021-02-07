#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
int trie[maxn * 35][2] , N , tot = 0;
vector<int> indices[maxn * 35];
ll sum[35][2];

void add(int val , int index){
    int v = 0;
    for(int i = 29; i >= 0; --i){
        int b = val >> i & 1;
        if(!trie[v][b]){
            trie[v][b] = ++tot;
        }
        v = trie[v][b];
        indices[v].push_back(index);
    }
}

void solve(int v , int d){
    int l = trie[v][0] , r = trie[v][1];
    if(l)solve(l , d - 1);
    if(r)solve(r , d - 1);
    if(l == 0 && r == 0)return;
    ll inv = 0;
    int i = 0;
    for(int x : indices[l]){
        while(i < indices[r].size() && indices[r][i] < x)++i;
        inv += i;
    }
    sum[d][0] += inv;
    sum[d][1] += (ll)indices[l].size() * indices[r].size() - inv;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        add(x , i);
    }
    solve(0 , 29); // solve at root
    ll ret = 0;
    int x = 0;
    for(int i = 29; i >= 0; --i){
        if(sum[i][0] <= sum[i][1]){
            ret += sum[i][0];
        }
        else{
            ret += sum[i][1];
            x |= (1 << i);
        }
    }
    printf("%lld %d\n" , ret , x);
}