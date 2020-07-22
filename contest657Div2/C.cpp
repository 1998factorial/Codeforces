#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
int N , M;

ii a[100005];
ll sum[100005];


ll solve(){
    sort(a + 1 , a + 1 + M);
    reverse(a + 1 , a + 1 + M);
    for(int i = 1; i <= M; ++i){
        sum[i] = sum[i - 1] + a[i].first;
    }
    ll ret = 0;
    for(int i = 1; i <= M; ++i){
        // we have multiple ith flower
        // find largest k , st a[k] > b[i]
        ll val = a[i].first + a[i].second * (N - 1);
        //cout << "val = " << val << endl;
        int l = 1 , r = M , pos = 0;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(a[i].second > a[mid].first){
                r = mid - 1;
            }
            else{
                pos = mid;
                l = mid + 1;
            }
        }
        // a[1 .. pos]
        pos = min(pos , N - 1);
        val -= pos * a[i].second;
        val += sum[pos];
        if(i <= pos)val -= a[i].first , val += a[i].second;
        ret = max(ret , val);
        //cout << "pos = " << pos << " " << val << endl;
    }
    if(N <= M){
        ret = max(ret , sum[N]);
    }
    return ret;
}

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d %d" , &N , &M);
        for(int i = 1; i <= M; ++i){
            scanf("%lld %lld" , &a[i].first , &a[i].second);
        }
        printf("%lld\n" , solve());
    }
}