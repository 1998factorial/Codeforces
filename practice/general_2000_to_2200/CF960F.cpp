#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int N , M;
map<int , int> bits[maxn];
// LIS on graph
// bits[v][i] = maximal length of good path ending at v , weight <= i
// memory amortized to NlogN
// query time is QlogN
void update(int v , int pos , int val){
    while(pos < maxn){
        bits[v][pos] = max(bits[v][pos] , val);
        pos += pos & (-pos);
    }
}

int query(int v , int pos){
    int ret = 0;
    while(pos){
        ret = max(ret , bits[v][pos]);
        pos -= pos & (-pos);
    }
    return ret;
}

int main(){
    scanf("%d %d" , &N , &M);
    int ans = 0;
    for(int i = 1; i <= M; ++i){
        int u , v , w;
        scanf("%d %d %d" , &u , &v , &w);
        ++w;
        int r = query(u , w - 1) + 1;
        ans = max(ans , r);
        update(v , w , r);
    }    
    printf("%d\n" , ans);
}   