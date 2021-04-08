#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int N , T , t[maxn];

// note that all optimal solutions can be altered to
// we wait only at spot 0, and keep going unless we reach the 
// end or time is up
// say we reach ith spot in the end of this process
// how long should we wait?
// the answer is T - 1 - i

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> N >> T;
    for(int i = 1; i <= N; ++i)cin >> t[i];
    int ans = 0;
    priority_queue<int> q;
    for(int i = 1; i <= min(N , T - 1); ++i){
        int wait = T - 1 - i;
        q.push(t[i] - i);
        while(!q.empty() && q.top() > wait)q.pop();
        ans = max(ans , (int)q.size());
    }
    cout << ans << endl;
}