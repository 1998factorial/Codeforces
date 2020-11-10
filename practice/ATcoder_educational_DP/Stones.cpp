#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
int a[maxn];
int N;
int K;
int DP[100005];
// DP[i] = 1 if there are i stones in pile and first player wins
// DP[i] = 0 if there are i stones in pile and first player loses

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
    }
    for(int i = 1; i <= K; ++i){
        for(int j = 1; j <= N && DP[i] == 0; ++j){
            if(i - a[j] >= 0){
                DP[i] |= !DP[i - a[j]];
            }
        }
    }
    if(DP[K]){
        cout << "First\n";
    }
    else{
        cout << "Second\n";
    }
}
