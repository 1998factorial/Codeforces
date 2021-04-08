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
        set<int> v;
        for(int i = 1; i <= N; ++i){
            int x;
            cin >> x;
            v.insert(x);
        }
        if(K == 0){
            cout << (int)v.size() << endl;
            continue;
        }
        int mex = 0;
        for(;;++mex){
            if(v.find(mex) == v.end())break;
        }
        int mx = 0;
        for(int i : v)mx = max(mx , i);
        if(mx < mex){
            cout << (int)v.size() + K << endl;
        }
        else{
            int val = (mex + mx) / 2 + (mex + mx) % 2;
            v.insert(val);
            cout << (int)v.size() << endl;
        }
    }
}