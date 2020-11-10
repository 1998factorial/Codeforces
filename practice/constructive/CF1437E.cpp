#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
const int INF = 1e9 + 10;
int a[maxn] , K , N;
vector<int> b;
int DP[maxn];
// minimal number of changes to make array increasing 
// is the same as N - longest increasing sequence

// max range tree
int query(vector<int>& tree , int l , int r , int x , int y , int id){
    if(l > r || x > y || l > y || r < x)return 0;
    if(l <= x && y <= r){
        return tree[id];
    }
    int mid = (x + y) >> 1;
    if(mid < l)return query(tree , l , r , mid + 1 , y , id << 1 | 1);
    if(mid >= r)return query(tree , l , r , x , mid , id << 1);
    return max(query(tree , l , r , x , mid , id << 1) , query(tree , l , r , mid + 1 , y , id << 1 | 1));
}

void update(vector<int>& tree , int l , int r , int pos , int val , int id){
    if(l > pos || r < pos || l > r)return;
    if(pos == l && r == pos){
        tree[id] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid)update(tree , l , mid , pos , val , id << 1);
    else update(tree , mid + 1 , r , pos , val , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
}

int solve(int l , int r){
    // return the longest non decreasing sequence st
    // min >= a[l] , max <= a[r]
    int tot = 0;
    vector<int> tmp;
    map<int , int> mp , imp;
    for(int i = l; i <= r; ++i)tmp.push_back(a[i]);
    sort(tmp.begin() , tmp.end());
    for(int i : tmp)if(!mp[i])mp[i] = ++tot , imp[tot] = i;
    vector<int> tree(tot << 2 , 0);
    for(int i = l + 1; i < r; ++i){
        if(a[i] >= a[l] && a[i] <= a[r]){
            // [a[l] , a[i]]
            int v = query(tree , mp[a[l]] , mp[a[i]] , 0 , tot , 1) + 1;
            update(tree , 0 , tot , mp[a[i]] , v , 1);
        }
    }
    return tree[1];
}

int main(){
    scanf("%d%d" , &N , &K);
    vector<int> tmp;
    a[0] = -INF;
    a[N + 1] = INF;
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]) , a[i] -= i;
    b.push_back(0);
    for(int i = 1; i <= K; ++i){
        int x;
        scanf("%d" , &x);
        b.push_back(x);
    }
    b.push_back(N + 1);
    for(int i = 1; i < b.size(); ++i){
        if(a[b[i]] < a[b[i - 1]]){
            printf("-1\n");
            return 0;
        }
    }
    int ans = 0;
    for(int i = 1; i < b.size(); ++i){
        // solve for b[i - 1] to b[i]
        /*int v = 0;
        for(int j = b[i - 1] + 1; j < b[i]; ++j){
            if(a[j] >= a[b[i - 1]] && a[j] <= a[b[i]]){
                DP[j] = 1;
                for(int k = b[i - 1] + 1; k < j; ++k){
                    if(a[k] <= a[j] && a[k] >= a[b[i - 1]]){
                        DP[j] = max(DP[j] , DP[k] + 1);
                    }
                }
                v = max(v , DP[j]);
            }
        }   
        ans += v;
        */
        ans += solve(b[i - 1] , b[i]);
    }
    printf("%d\n" , N - K - ans);
}