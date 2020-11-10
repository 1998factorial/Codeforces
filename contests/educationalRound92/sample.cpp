#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

int DP[50000];
int n;

int main(){
    n = 5000;
    map<int , int> cnt;
    for(int i = 0; i <= n; ++i)DP[i] = i;
    DP[0] = 0;
    DP[1] = 1;
    DP[2] = 2;
    DP[3] = 2;
    for(int i = 4; i <= n; ++i){
        DP[i] = min(DP[i] , DP[i - 1] + 1);
        if(i % 2 == 0)DP[i] = min(DP[i] , DP[i / 2] + 1);
        if(i % 3 == 0)DP[i] = min(DP[i] , DP[i / 3] + 1);
        printf("DP[%d] = %d\n" , i , DP[i]);
    }
    for(int i = 0; i <= n; ++i){
        ++cnt[DP[i]];
    }
    for(auto& e : cnt){
        cout << e.first << " " << e.second << endl;
    }
    /*vector<long long> a;
    for(long long i = 4; i <= 2e9; i *= 3){
        a.push_back(i);
    }
    for(long long i : a){
        printf("%lld\n" , i);
    }*/
}

