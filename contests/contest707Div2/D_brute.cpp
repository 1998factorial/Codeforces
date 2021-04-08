#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 10;
int N , M , a[maxn] , b[maxn];
ll K;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> K;
    for(int i = 1; i <= N; ++i)cin >> a[i];
    for(int i = 1; i <= M; ++i)cin >> b[i];
    ll cnt = 0;
    for(ll i = 1; ; ++i){
        cnt += a[(i - 1) % N + 1] != b[(i - 1) % M + 1];
        if(cnt >= K){
            cout << i << endl;
            exit(0);
        }
    }
}