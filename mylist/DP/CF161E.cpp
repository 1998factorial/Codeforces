/*
    search , DP
    we notice that the maximal depth of our search is 5
    And there are not a lot of primes that share some common prefix
    so we can enumerate our answer use brute force
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
vector<int> to[5][maxn];
bool vis[maxn];
int table[6][6];
int N;
int p;
ll ans;

int length(int x){
    int ret = 0;
    while(x)x /= 10 , ++ret;
    return ret;
}

void fill(int row , int l , int r , int v){
    for(int x = r; x >= l; --x){
        table[row][x] = table[x][row] = v % 10;
        v /= 10;
    }
}

void init(){
    for(int i = 2; i < maxn; ++i){
        if(!vis[i]){
            for(int j = i; j < maxn; j += i){
                vis[j] = 1;
            }
            int val = i;
            val /= 10;
            for(int j = 1; j <= 4; ++j){
                to[j][val].push_back(i); // we have fixed all digits except last j ones and the prefix is val , we can get to i
                val /= 10;
            }
        }
    }
}

void solve(int row){
    int val = 0;
    for(int i = 1; i < row; ++i)val = val * 10 + table[row][i];
    if(row == N){
        ans += to[1][val].size();
    }
    else{
        for(int i : to[N - (row - 1)][val]){ // we have fixed all digits except last N - (row - 1) digits and the prefix is val
            fill(row , row , N , i);
            solve(row + 1);
        }
    }
}

int main(){
    init();
    int t; 
    scanf("%d" , &t);
    while(t--){
        ans = 0;
        scanf("%d" , &p);
        N = length(p);
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= N; ++j){
                table[i][j] = 0;
            }
        }
        fill(1 , 1 , N , p);
        solve(2);
        printf("%lld\n" , ans);
    }
}