#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e17;
const int maxn = 2e5 + 10;
int N[5] , a[5][maxn];
vector<int> g[5][maxn];

ll tree[5][maxn << 2];

void init(){
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < maxn << 2; ++j){
            tree[i][j] = INF;
        }
    }
}

void update(int l , int r , int pos , ll val , int id , int lev){
    if(l > r || pos < l || pos > r)return;
    if(pos == l && pos == r){
        tree[lev][id] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid){
        update(l , mid , pos , val , id << 1 , lev);
    }
    else{
        update(mid + 1 , r , pos , val , id << 1 | 1 , lev);
    }
    tree[lev][id] = min(tree[lev][id << 1] , tree[lev][id << 1 | 1]);
}

ll query(int l , int r , int x , int y , int id , int lev){
    if(l > r || x > y)return INF;
    if(l <= x && y <= r){
        return tree[lev][id];
    }
    int mid = (x + y) >> 1;
    if(r <= mid){
        return query(l , r , x , mid , id << 1 , lev);
    }
    if(l > mid){
        return query(l , r , mid + 1 , y , id << 1 | 1 , lev);
    }
    return min(query(l , r , x , mid , id << 1 , lev) , query(l , r , mid + 1 , y , id << 1 | 1 , lev));
}

ll DP[5][maxn];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    for(int i = 1; i <= 4; ++i)cin >> N[i];
    for(int i = 1; i <= 4; ++i){
        for(int j = 1; j <= N[i]; ++j){
            cin >> a[i][j];
        }
    }
    for(int i = 2; i <= 4; ++i){
        int M;
        cin >> M;
        for(int j = 1; j <= M; ++j){
            int x , y;
            cin >> x >> y;
            g[i][y].push_back(x);
        }
        for(int j = 1; j <= N[i]; ++j){
            sort(g[i][j].begin() , g[i][j].end());
        }
    }
    for(int i = 1; i <= 4; ++i){
        for(int j = 1; j <= N[i]; ++j){
            DP[i][j] = INF;
        }
    }
    for(int i = 1; i <= N[1]; ++i){
        DP[1][i] = a[1][i];
        update(1 , N[1] , i , a[1][i] , 1 , 1);
    }
    for(int i = 2; i <= 4; ++i){
        for(int j = 1; j <= N[i]; ++j){
            if(g[i][j].size() == 0){
                ll v = query(1 , N[i - 1] , 1 , N[i - 1] , 1 , i - 1);
                DP[i][j] = min(DP[i][j] , v + a[i][j]);
            }
            for(int k = 0; k < g[i][j].size(); ++k){
                if(k == 0){
                    ll v = query(1 , g[i][j][k] - 1 , 1 , N[i - 1] , 1 , i - 1);
                    DP[i][j] = min(DP[i][j] , v + a[i][j]);
                }
                if(k == g[i][j].size() - 1){
                    ll v = query(g[i][j][k] + 1 , N[i - 1] , 1 , N[i - 1] , 1 , i - 1);
                    DP[i][j] = min(DP[i][j] , v + a[i][j]);
                }
                if(k > 0){
                    ll v = query(g[i][j][k - 1] + 1 , g[i][j][k] - 1 , 1 , N[i - 1] , 1 , i - 1);
                    DP[i][j] = min(DP[i][j] , v + a[i][j]);
                }
            }
            update(1 , N[i] , j , DP[i][j] , 1 , i);
        }
    }
    ll mn = INF;
    for(int i = 1; i <= N[4]; ++i){
        mn = min(mn , DP[4][i]);
    }
    if(mn < INF / 2){
        cout << mn << endl;
    }
    else{
        cout << -1 << endl;
    }
}