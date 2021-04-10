#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
int N;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> N;
    vector<pair<ll , ll>> a;
    ll ans = 0;
    for(int i = 1; i <= N; ++i){
        ll x , y;
        cin >> x >> y;
        a.push_back({x , y});
        ans += y;
    }
    sort(a.begin() , a.end());
    ll mx = -1;
    for(int i = 0; i < N; ++i){
        if(mx == -1){
            mx = a[i].x + a[i].y;
        }
        else{
            ans += max(0ll , a[i].x - mx);
            mx = max(mx , a[i].x + a[i].y);
        }
    }
    cout << ans << endl;
}