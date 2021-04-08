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
        vector<int> p(N);
        for(int i = 0; i < N; ++i)p[i] = i;
        int f = 0;
        do{
            vector<int> a = p;
            int ans = 0;
            for(int i = 0; i < N - 1; ++i){
                int mn = a[i] , mb = i;
                for(int j = i + 1; j < N; ++j){
                    if(a[j] < mn){
                        mn = a[j];
                        mb = j;
                    }
                }
                ans += mb - i + 1;
                reverse(a.begin() + i , a.begin() + mb + 1);
            }
            if(ans == C){
                f = 1;
                for(int j : p)cout << j + 1 << " ";
                cout << endl;
                break;
            }
        }while(next_permutation(p.begin() , p.end()));
        if(!f)cout << "IMPOSSIBLE" << endl;
    }
}