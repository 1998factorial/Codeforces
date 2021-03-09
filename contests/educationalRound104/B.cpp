#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int N , K;
        cin >> N >> K;
        // will only meet for N is odd
        /*int meet = 0;
        int a = N , b = 1;
        for(int k = 1; k < K; ++k){
            int na = (a > 1) ? a - 1 : N;
            int nb = (b < N) ? b + 1 : 1;
            if(na == nb){
                ++meet;
                if(nb < N)++nb;
                else nb = 1;
            }
            a = na;
            b = nb;
        }*/
        //cout << a << " " << b << endl;
        //cout << "meet = " << meet << " v = " << (K - 1) / (N / 2) << endl;
        // odd will be shifted by (K - 1) / (N / 2)
        int ans = 1 + (K - 1);
        if(N & 1)ans += (K - 1) / (N / 2);
        ans = (ans - 1) % N + 1;
        cout << ans << endl;
        //assert(ans == b);
    }

}