/*
    Case work
*/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

int main(){
    int t; cin >> t;
    while(t--){
        int N; cin >> N;
        vector<ii> ret;
        for(int i = 1; i <= N; ++i){
            int x , y; cin >> x >> y; ret.emplace_back(x , y);
        }
        bool ok = 1;
        int s1 = 0 , s2 = 0;
        for(int i = 0; i < N; ++i){
            if(ret[i].first < ret[i].second){
                ok = 0;
            }
            if(i){
                if(ret[i].first < ret[i - 1].first)ok = 0;
                if(ret[i].second < ret[i - 1].second)ok = 0;
            }
            if(i && ret[i].first - ret[i - 1].first < ret[i].second - ret[i - 1].second){
                ok = 0;
            }
            s1 += ret[i].first;
            s2 += ret[i].second;
        }
        if(ok){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}
