#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
ll a[maxn] , table[maxn][25];
int N , Q , LOG[maxn];

ll query(int l , int r){
    int j = LOG[r - l + 1];
    return min(table[l][j] , table[r - (1 << j) + 1][j]);
}

int main(){
    scanf("%d %d" , &N , &Q);
    LOG[1] = 0;
    for(int i = 2; i < maxn; ++i)LOG[i] = LOG[i / 2] + 1;
    for(int i = 0; i < N; ++i)scanf("%lld" , &a[i]) , table[i][0] = a[i];
    for(int j = 1; j <= LOG[N] + 1; ++j){
        for(int i = 0; i + (1 << j) <= N; ++i){
            table[i][j] = min(table[i][j - 1] , table[i + (1 << (j - 1))][j - 1]);
        }
    }
    while(Q--){
        ll v;
        int L , R;
        scanf("%lld %d %d" , &v , &L , &R);
        --L , --R;
        int pos = L - 1;
        while(pos <= R){
            int l = pos + 1 , r = R , npos = -1;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(query(l , mid) <= v){
                    npos = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }
            if(npos == -1)break;
            else v %= a[npos];
            pos = npos;
        }
        printf("%lld\n" , v);
    }   
}