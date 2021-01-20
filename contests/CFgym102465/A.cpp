#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int a[maxn];
int N , K;
int main(){
    cin >> N;
    cin >> K;
    vector<int> op;
    int ans = 0 , on = N , off = 0;
    for(int i = 1; i <= K; ++i){
        int x; 
        cin >> x;
        for(int y = x; y <= N; y += x){
            if(a[y])--off , ++on;
            else ++off , --on;
            a[y] = 1 - a[y];
        }
        ans = max(ans , off);
    }
    cout << ans << endl;
}