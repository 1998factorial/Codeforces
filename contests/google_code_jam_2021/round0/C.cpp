#include <bits/stdc++.h>
using namespace std;
const int inf = 1e8;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for(int kase = 1; kase <= t; ++kase){
        cout << "Case #" << kase << ": ";
        int N , C;
        cin >> N >> C;
        if(C < N - 1 || C >= N * (N + 1) / 2){
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        vector<int> a(N);
        for(int i = 0; i < N; ++i)a[i] = i + 1;
        for(int i = N - 2; i >= 0; --i){
            int remain = i;
            int c = min(N - i , C - remain);
            C -= c;
            reverse(a.begin() + i , a.begin() + i + c);
        }
        for(int i = 0; i < N; ++i)cout << a[i] << " ";
        cout << endl;
    }
}