#include <bits/stdc++.h>
using namespace std;

int N , K;
int a[105];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        cin >> N >> K;
        set<int> vis;
        for(int i = 1; i <= N; ++i){
            cin >> a[i];
            vis.insert(a[i]);
        }
        if(vis.size() > K){
            cout << -1 << endl;
        }
        else{
            cout << N * K << endl;
            for(int i = 1; i <= N; ++i){
                for(int j : vis){
                    cout << j << " ";
                }
                for(int j = 1; j <= K - vis.size(); ++j){
                    cout << *vis.begin() << " ";
                }
            }
            cout << endl;
        }
    }
}
