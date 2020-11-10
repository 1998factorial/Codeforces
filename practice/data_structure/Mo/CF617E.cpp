#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int N , M , K , L = 0 , R = 0 , block_size = 0;
ll val = 0;
int a[maxn];
ll ans[maxn];
ll cnt[maxn * 20];
int prefix[maxn];
vector<array<int , 3>> qs;
void update(int pos , int sign){
    int v = prefix[pos];
    if(sign == 1){
        val += cnt[v ^ K];
        cnt[v] += sign;
    }
    else{
        cnt[v] += sign; 
        val -= cnt[v ^ K];
    }
}
void cal(int l , int r){
    while(l > L)update(L , -1) , ++L;
    while(r < R)update(R , -1) , --R;
    while(l < L)--L , update(L , 1);
    while(r > R)++R , update(R , 1);
}
int main(){
    scanf("%d %d %d" , &N , &M , &K);
    block_size = sqrt(M);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]) , prefix[i] = prefix[i - 1] ^ a[i];
    for(int i = 1; i <= M; ++i){
        int l , r; 
        scanf("%d %d" , &l , &r);
        qs.push_back({l - 1 , r , i});
    }
    sort(qs.begin() , qs.end() , [&](array<int , 3> lhs , array<int , 3> rhs){
        if(lhs[0] / block_size != rhs[0] / block_size)return lhs[0] < rhs[0];
        return lhs[1] < rhs[1];
    });
    cnt[0] = 1;
    for(auto& q : qs){
        int l = q[0] , r = q[1] , id = q[2];
        cal(l , r);
        ans[id] = val;
    }
    for(int i = 1; i <= M; ++i){
        printf("%lld\n" , ans[i]);
    }
}
