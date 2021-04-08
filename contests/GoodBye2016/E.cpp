#include <bits/stdc++.h>
using namespace std;
const int inf = 1e8;
const int maxn = 2e5 + 10;
char a[maxn];
int N , Q;

/*
    0 -> empty
    1 -> 2
    2 -> 20
    3 -> 201
    4 -> 2017
*/

struct node{
    int dp[5][5]; // min cost to transform from i to j
    node operator + (const node& rhs) const {
        node ret;
        for(int i = 0; i < 5; ++i){
            for(int j = 0; j < 5; ++j){
                ret.dp[i][j] = inf;
                for(int k = 0; k < 5; ++k){
                    ret.dp[i][j] = min(ret.dp[i][j] , dp[i][k] + rhs.dp[k][j]);
                }
            }
        }
        return ret;
    }
} tree[maxn * 4];

void build(int l , int r , int id){
    if(l == r){
        for(int i = 0; i < 5; ++i){
            for(int j = 0; j < 5; ++j){
                tree[id].dp[i][j] = (i == j) ? 0 : inf;
            }
        }
        if(a[l] == '2'){
            tree[id].dp[0][0] = 1;
            tree[id].dp[0][1] = 0;
        }
        else if(a[l] == '0'){
            tree[id].dp[1][2] = 0;
            tree[id].dp[1][1] = 1;
        }
        else if(a[l] == '1'){
            tree[id].dp[2][3] = 0;
            tree[id].dp[2][2] = 1;
        }
        else if(a[l] == '7'){
            tree[id].dp[3][4] = 0;
            tree[id].dp[3][3] = 1;
        }
        else if(a[l] == '6'){
            tree[id].dp[4][4] = 1;
            tree[id].dp[3][3] = 1;
        }
    }
    else{
        int mid = (l + r) >> 1;
        build(l , mid , id << 1);
        build(mid + 1 , r , id << 1 | 1);
        tree[id] = tree[id << 1] + tree[id << 1 | 1];
    }
}

node query(int l , int r , int x , int y , int id){
    if(l <= x && y <= r){
        return tree[id];
    }
    int mid = (x + y) >> 1;
    if(r <= mid){
        return query(l , r , x , mid , id << 1);
    }
    if(l > mid){
        return query(l , r , mid + 1 , y , id << 1 | 1);
    }
    return query(l , r , x , mid , id << 1) + query(l , r , mid + 1 , y , id << 1 | 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> Q;
    cin >> (a + 1);
    build(1 , N , 1);
    for(int q = 1; q <= Q; ++q){
        int l , r;
        cin >> l >> r;
        node ret = query(l , r , 1 , N , 1);
        int v = (ret.dp[0][4] >= inf) ? -1 : ret.dp[0][4];
        cout << v << endl;
    }
}