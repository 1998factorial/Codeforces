#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a  , b) for(int i = a; i >= b; --i)
using namespace std;

char s[55];
int DP[55];

int main(){
    cin >> (s + 1);
    int N = strlen(s + 1) , ans = 0;
    rep(i , 1 , N){
        DP[i] = 1;
        rep(j , 1 , i - 1){
            if(s[i] > s[j])DP[i] = max(DP[i] , DP[j] + 1);
        }
        ans = max(ans , DP[i]);
    }
    printf("%d\n" , 26 - ans);
}