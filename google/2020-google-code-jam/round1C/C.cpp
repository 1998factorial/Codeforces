#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;


const int maxn = 1e4 + 10;
int N , T , D;
ll A[maxn];

void solve(){
    cin >> N >> D;
    for(int i = 1; i <= N; ++i){
        cin >> A[i];
    }
    sort(A + 1 , A + N + 1);
    ll cnt = 0;
    for(int i = 1; i <= N; ++i){
        cnt += A[i] / A[1];
    }
    if(cnt < D){
        cout << D - 1 << endl;
        return;
    }
    ll ret = D - 1;
    for(int i = 1; i <= N; ++i){ // cut everything to A[i]
        for(int k = 1; k <= D; ++k){
            ll val = 0;
            ll num = 0;
            ll target = A[i] / k;
            for(int j = i; j <= N && num < D; ++j){
                if(A[j] / target <= (ll)D - num){
                    num += A[j] / target;
                    val += A[j] / target - (A[j] % target == 0);
                }
                else{
                    val += (ll)D - num;
                    num = D;
                }
                //cout << num << " " << val << endl;
            }
            if(num >= D){
                ret = min(ret , val);
            }
        }
    }
    cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": ";
    solve();
  }
}
