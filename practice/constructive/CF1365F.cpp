/*
    constructive , rating 2100
    key : no matter how we swap , unordered pair (a[i] , a[N - i + 1]) will not change
    so we can get all pairs (a[i] , a[N - i + 1]) and (b[i] , b[N - i + 1]) for i in [1 , N / 2]
    and we sort both of the pairs and check if they are the same (positions of pairs relative to other pairs
    can be changed to any order , also , for each pair , we are free to choose their order)
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
int a[505] , b[505];

int main(){
    int t; cin >> t;
    while(t--){
        int N; cin >> N;
        for(int i = 1; i <= N; ++i){
            cin >> a[i];
        }
        for(int i = 1; i <= N; ++i){
            cin >> b[i];
        }
        if(N % 2 && a[(N + 1) / 2] != b[(N + 1) / 2]){
            cout << "No" << endl;
            continue;
        }
        vector<ii> pos1 , pos2;
        for(int i = 1; i <= N / 2; ++i){
            pos1.emplace_back(a[i] , a[N - i + 1]);
            if(pos1.back().first > pos1.back().second)swap(pos1.back().first , pos1.back().second);
            pos2.emplace_back(b[i] , b[N - i + 1]);
            if(pos2.back().first > pos2.back().second)swap(pos2.back().first , pos2.back().second);
        }
        int ok = 1;
        sort(pos1.begin() , pos1.end());
        sort(pos2.begin() , pos2.end());
        for(int i = 0; i < pos1.size(); ++i){
            if(pos1[i] != pos2[i])ok = 0;
        }
        string ret = ok ? "Yes" : "No";
        cout << ret << endl;
    }
}
