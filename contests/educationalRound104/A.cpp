#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int N;
        cin >> N;
        vector<int> a(N);
        for(int i = 0; i < N; ++i)cin >> a[i];
        int ans = 0;
        for(int i = 0; i < N; ++i){
            int cnt = 0;
            for(int j = 0; j < N; ++j){ 
                if(a[i] > a[j])++cnt;
            }
            ans += cnt > 0;
        }
        cout << ans << endl;
    }
}