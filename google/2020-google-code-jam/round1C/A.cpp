#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int N , T;
string s;
int X , Y;
int sum[1005][2];

int dis(int a , int b , int c , int d){
    return abs(a - c) + abs(b - d);
}

bool check(int mid){
    return dis(0 , 0 , X + sum[mid][1] , Y + sum[mid][0]) <= mid;
}

void solve(){
    cin >> X >> Y;
    cin >> s;
    int l = 1 , r = s.size();
    int ans = -1;
    memset(sum , 0 , sizeof(sum));
    for(int i = 0; i < s.size(); ++i){
        sum[i + 1][0] = sum[i][0];
        sum[i + 1][1] = sum[i][1];
        if(s[i] == 'S'){
            --sum[i + 1][0];
        }
        if(s[i] == 'N'){
            ++sum[i + 1][0];
        }
        if(s[i] == 'E'){
            ++sum[i + 1][1];
        }
        if(s[i] == 'W'){
            --sum[i + 1][1];
        }
    }
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    if(ans == -1){
        cout << "IMPOSSIBLE" << endl;
    }
    else{
        cout << ans << endl;
    }
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
