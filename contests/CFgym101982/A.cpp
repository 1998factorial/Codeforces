#include <bits/stdc++.h>
using namespace std;

string s , t;
int K , N , same = 0 , diff = 0;

int main(){
    cin >> K;
    cin >> s;
    cin >> t;
    N = s.size();
    for(int i = 0; i < N; ++i){
        if(s[i] == t[i])++same;
        else ++diff;
    }
    int ret = 0;
    for(int x = 0; x <= min(K , diff); ++x){
        if(K - x > same)continue;
        ret = max(ret , diff - x + K - x);
    }
    cout << ret << endl;
}   