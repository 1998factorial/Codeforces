#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for(int kase = 1; kase <= t; ++kase){
        cout << "Case #" << kase << ": ";
        int N;
        cin >> N;
        vector<int> a(N + 1);
        for(int i = 1; i <= N; ++i)cin >> a[i];
        int ans = 0;
        for(int i = 1; i < N; ++i){
            int mn = a[i] , mb = i;
            for(int j = i + 1; j <= N; ++j){
                if(a[j] < mn){
                    mn = a[j];
                    mb = j;
                }
            }
            ans += mb - i + 1;
            reverse(a.begin() + i , a.begin() + mb + 1);
        }
        cout << ans << endl;
    }
}