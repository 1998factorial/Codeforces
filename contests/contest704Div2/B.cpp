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
        vector<int> p(N + 1) , ans , id(N + 1);
        for(int i = 1; i <= N; ++i){
            cin >> p[i];
            id[p[i]] = i;
        }
        int pre = N + 1;
        for(int i = N; i >= 1; --i){
            if(id[i] > 0){
                int x = id[i];
                for(int j = id[i]; j < pre; ++j){
                    ans.push_back(p[j]);
                    id[p[j]] = 0;
                }
                pre = x;
            }
        }
        for(int i : ans)cout << i << " ";
        cout << endl;
    }
}
