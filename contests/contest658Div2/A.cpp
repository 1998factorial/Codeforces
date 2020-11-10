#include <bits/stdc++.h>
using namespace std;

int N , M;
int a[1005] , b[1005];

int main(){
    int t; cin >> t;
    while(t--){
        cin >> N >> M;
        for(int i = 1; i <= N; ++i)cin >> a[i];
        for(int i = 1; i <= M; ++i)cin >> b[i];
        int ok = 0;
        for(int i = 1; i <= N && !ok; ++i){
            for(int j = 1; j <= M && !ok; ++j){
                if(a[i] == b[j]){
                    cout << "YES\n";
                    cout << 1 << " " << a[i] << endl;
                    ok = 1;
                }
            }
        }
        if(!ok){
            cout << "NO\n";
        }
    }
}