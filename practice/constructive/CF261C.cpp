#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N , T , ans = 0;
int M;
ll C[41][41];

ll solve(ll pos , ll len , int level , int L){
    // current position, len of current level , which level , desired num
    if(L < 0 || level < L)return 0;
    if(len == 1)return 1;
    if(pos > len / 2){
        return (level - 1 >= 0 && L >= 0 ? C[level - 1][L] : 0) + solve(pos - len / 2 , len / 2 , level - 1 , L - 1);
    }
    return solve(pos , len / 2 , level - 1 , L);
}

int main(){
    cin >> N >> T;
    /*
    1 2 , #(1) = 1 = C(1 , 0) , #(2) = 1 = C(1 , 1)
    1 2 2 4 , #(1) = 1 = C(2 , 0) , #(2) = 2 = C(2 , 1) , #(4) = 1 = C(2 , 2)
    1 2 2 4 2 4 4 8 , #(1) = 1 , #(2) = 3 , #(4) = 3 , #(8) = 1
    1 2 2 4 2 4 4 8 2 4 4 8 4 8 8 16 , #(1) = 1 , #(2) = 4 , #(4) = 6 , #(8) = 4 , #(16) = 1
    start with a <- (1 , 2)
    each time we append a * 2 to a 
    say we do this x times, so we have 2^1 + 2^2 + 2^3 + ... 2^x >= N
    x must be bounded by logN
    compute C(i , j) , up to i = 40
    */
    C[0][0] = 1;
    for(int i = 1; i <= 40; ++i){
        for(int j = 0; j <= i; ++j){
            if(j == 0 || j == i){
                C[i][j] = 1;
            }
            else{
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }
    int L = log2(T);
    if(1ll << L != T){
        cout << 0 << endl;
    }
    else{
        ll ans = 0;
        int level = 1;
        ll total = 0;
        for(;;){
            total += 1ll << level;
            if(total >= N)break;
            ++level;
        }
        for(int i = 1; i <= level - 1; ++i){
            ans += C[i][L];
        }
        //cout << "preans = " << ans << endl;
        //cout << "total = " << total << endl;
        //cout << N - total + (1ll << level) <<  " " << (1ll << level) << " " << level << " " << L << endl;
        ans += solve(N - total + (1ll << level) , 1ll << level , level , L);
        cout << ans << endl;
    }
}