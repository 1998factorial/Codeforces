#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9 + 10;
int a[5005];
int N;
ll solve(int l , int r , ll h){
    if(l > r)return 0;
    int mn = INF , pos = -1 , i;
    for(i = l; i <= r; ++i){
        if(mn > a[i]){
            mn = a[i];
            pos = i;
        }
    }
    ll remove_all = r - l + 1;
    ll remove_base = solve(l , pos - 1 , mn) + solve(pos + 1 , r , mn) + mn - h;
    return min(remove_all , remove_base);
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    printf("%lld\n" , solve(1 , N , 0));
}