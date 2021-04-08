#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int N , p[maxn] , L[maxn] , R[maxn];

// L[i] = longest increasing subsequence ending at p[i]
// R[i] = longest decreasing subsequence starting at p[i]

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cin >> p[i];
    }
    for(int i = 1; i <= N; ++i){
        L[i] = 1;
        if(i > 1 && p[i] > p[i - 1])L[i] += L[i - 1];
    }
    for(int i = N; i >= 1; --i){
        R[i] = 1;
        if(i < N && p[i] > p[i + 1])R[i] += R[i + 1];
    }
    int mxL = 0;
    for(int i = 1; i <= N; ++i)mxL = max(mxL , L[i]);
    int cnt = 0;
    for(int i = 1; i <= N; ++i)if(mxL == L[i])++cnt;
    if(cnt > 1){
        cout << 0 << endl;
        exit(0);
    }
    int mxR = 0;
    for(int i = 1; i <= N; ++i)mxR = max(mxR , R[i]);
    cnt = 0;
    for(int i = 1; i <= N; ++i)if(mxR == R[i])++cnt;
    if(cnt > 1){
        cout << 0 << endl;
        exit(0);
    }
    int bl = 0 , br = 0;
    for(int i = 1; i <= N; ++i){
        if(mxL == L[i])bl = i;
        if(mxR == R[i])br = i;
    }
    if(bl != br){
        cout << 0 << endl;
        exit(0);
    }
    int ans = 0;
    for(int x = 2; x <= N - 1; ++x){
        if(p[x + 1] > p[x] && p[x] > p[x - 1])continue;
        if(p[x + 1] < p[x] && p[x] < p[x - 1])continue;
        if(p[x + 1] > p[x] && p[x] < p[x - 1])continue;
        if(x != bl)continue;
        int l = L[x] , r = R[x];
        if(l > r)swap(l , r);
        if(l == r){
            if(l & 1)++ans;
        }   
    }   
    cout << ans << endl;
}