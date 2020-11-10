#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> a;
        for(int i = 1; i <= n; ++i){
            int x; cin >> x;
            a.push_back(x);
        }
        sort(a.begin() , a.end());
        reverse(a.begin() , a.end());
        for(int i : a)cout << i << " ";
        cout << endl;
    }
}
