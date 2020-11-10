/*
    DP[i] = sum{DP[j] , st F(j + 1 , i) <= K & j < i} where F(l , r) = number of distinct integers in a[l..r] that appear exactly once
    the process of finding DP[i] can be optimzed to O(sqrt(N))
    First, F(i , j) -> F(i , j + 1) can be updated similar to one occurence
    F(i , j) is just the prefix sum S[j] - S[i - 1]
    divide array a into sqrt(N) buckets, for each bucket, maintain 
        (1) F(L .. R)
        (2) dpsum[-sqrt(N), ... , sqrt(N)], where dpsum[i] = sum of DP[x] st F(x + 1 , R) <= i
    when rebuild a bucket, we can do in O(sqrt(N))
    when query for DP[i], brute force the j in i's bucket takes O(sqrt(N))
    for each of remaining buckets, we can do it in O(1)

    total time complexity is O(sqrt(N) * N)
*/
#include <bits/stdc++.h>
#define DEBUG if(1)
using namespace std;
typedef long long ll;
const int maxb = 355;
const int maxn = 355 * 355 + 10;
const ll mod = 998244353;
inline ll add(ll x , ll y){
    ll ret = x + y;
    if(ret >= mod)ret -= mod;
    return ret;
}
inline ll sub(ll x , ll y){
    ll ret = x - y;
    if(ret <= 0)ret += mod;
    return ret;
}
inline ll mul(ll x , ll y){
    return x * y % mod;
}

int N , K , a[maxn] , b[maxn] , block_size , block_id[maxn] , block_in_id[maxn];
ll DP[maxn];
vector<int> pos[maxn];

struct block {  // govern [L..R]
    int bsum[maxb]; // bsum[i] = b[i] + .. + b[R]
    ll dpsum[maxb * 2]; // dpsum[i] = sum of all DP[x - 1] where b[x..R] <= i
} B[maxb];

void init(){
    block_size = sqrt(N);
    // DEBUG printf("block_size = %d\n" , block_size);
    for(int i = 0; i < N; ++i){
        block_id[i] = i / block_size;
        block_in_id[i] = i % block_size;
        // DEBUG printf("block_id[%d] = %d\n" , i , block_id[i]);
        // DEBUG printf("block_in_id[%d] = %d\n" , i , block_in_id[i]);
    }
}

void rebuild(int bid){ // rebuild block pos
    // fix bsum array
    int R = block_size - 1;
    for(int i = R; i >= 0; --i){
        B[bid].bsum[i] = b[bid * block_size + i];
        if(i < R)B[bid].bsum[i] += B[bid].bsum[i + 1];
    }
    // fix dpsum array
    for(int i = -block_size; i <= block_size; ++i){
        B[bid].dpsum[i + maxb] = 0;
    }
    for(int i = R; i >= 0; --i){
        int x = B[bid].bsum[i];
        B[bid].dpsum[x + maxb] = add(B[bid].dpsum[x + maxb] , DP[bid * block_size + i]);
    }
    for(int i = -block_size + 1; i <= block_size; ++i){
        B[bid].dpsum[i + maxb] = add(B[bid].dpsum[i + maxb] , B[bid].dpsum[i + maxb - 1]);
    }
}

ll query(int i){ // solve for DP[i + 1] 
    ll ret = 0;
    // first, solve for i's bucket
    int sum = 0;
    for(int j = block_in_id[i]; j >= 0; --j){
        int nj = block_id[i] * block_size + j;
        sum += b[nj];
        if(sum <= K)ret = add(ret , DP[nj]);
    }
    // second, solve for all previous bucket
    for(int bid = block_id[i] - 1; bid >= 0; --bid){
        int ns = K - sum;
        ll val = 0;
        if(ns < -block_size)val = 0;
        else if(ns > block_size)val = B[bid].dpsum[maxb + block_size];
        else val = B[bid].dpsum[maxb + ns];
        ret = add(ret , val);
        sum += B[bid].bsum[0];
    }
    return ret;
}

void show(int bid){
    printf("showing block %d\n" , bid);
    for(int i = 0; i < block_size; ++i){
        printf("bsum[%d] = %d\n" , i , B[bid].bsum[i]);
    }
    for(int i = -block_size; i <= block_size; ++i){
        printf("dpsum[%d] = %lld\n" , i , B[bid].dpsum[i + maxb]);
    }
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 0; i < N; ++i)scanf("%d" , &a[i]);
    init();
    DP[0] = 1;
    for(int i = 0; i < N; ++i){
        int x = a[i] , sz;
        pos[x].push_back(i);
        sz = pos[x].size();
        // set b[i] to 1
        b[i] = 1; 
        if(sz >= 2){
            b[pos[x][sz - 2]] = -1;
            rebuild(block_id[pos[x][sz - 2]]);
            //DEBUG show(block_id[pos[x][sz - 2]]);
        } 
        if(sz >= 3){
            b[pos[x][sz - 3]] = 0;
            rebuild(block_id[pos[x][sz - 3]]);
            //DEBUG show(block_id[pos[x][sz - 3]]);
        }
        // solve for DP[i + 1]
        DP[i + 1] = query(i);
        rebuild(block_id[i]);
        //DEBUG show(block_id[i]);
    }
    printf("%lld\n" , DP[N]);
}