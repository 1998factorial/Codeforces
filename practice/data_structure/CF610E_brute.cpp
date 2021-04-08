#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int N , M , K;
char a[maxn];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> K;
    cin >> (a + 1);
    for(int i = 1; i <= M; ++i){
        int t;
        cin >> t;
        if(t == 1){
            int l , r;
            char c;
            cin >> l >> r >> c;
            for(int i = l; i <= r; ++i){
                a[i] = c;
            }
        }
        else if(t == 2){
            char p[15];
            cin >> (p + 1);
            int L = strlen(p + 1);
            map<char , int> pos;
            for(int i = 1; i <= L; ++i){
                pos[p[i]] = i;
            }
            /*
            vector<int> f(N + 1 , 1);
            for(int i = 1; i <= N; ++i){
                int mx = 1;
                for(int j = 1; j <= L && i - j >= 1; ++j){
                    int p1 = pos[a[i]];
                    int p2 = pos[a[i - j]];
                    mx = max(mx , f[i - j] + (int)(p1 <= p2));
                }
                f[i] = mx;
            }
            int ans = 0;
            for(int i = 1; i <= N; ++i)ans = max(f[i] , ans);
            cout << ans << endl;
            */
           // count the number of adjcent inversion pairs
           int ans = 0;
           for(int i = 1; i < N; ++i){
               if(pos[a[i]] >= pos[a[i + 1]]){
                   ++ans;
               }
           }
           cout << ans + 1 << endl;
        }
    }
}