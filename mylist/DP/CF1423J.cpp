#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

/*int main(){
    int t , i , j , x , l , r , sum;
    scanf("%d" , &t);
    getchar();
    while(t--){
        long long M = 0;
        char c;
        while(c = getchar() , c >= '0' && c <= '9')M = M * 10 + c - '0';
        vector<int> DP(10);
        int len = 60; while(len >= 0 && (M >> len & 1) == 0)--len;
        DP[0] = 1;
        for(i = len; i >= 0; --i){
            vector<int> a(10);
            for(j = 0; j < 8; ++j){
                x = 2 * j + (M >> i & 1);
                l = x - 7 < 0 ? 0 : x - 7, r = x > 7 ? 7 : x;
                a[l] += DP[j];
                if(a[l] >= mod) a[l] -= mod;
                a[r + 1] -= DP[j];
                if(a[r + 1] < 0) a[r + 1] += mod;
            }
            sum = 0;
            for(j = 0; j < 8; ++j){
                sum += a[j];
                if(sum >= mod) sum -= mod;
                DP[j] = sum;
                //printf("DP[%d][%d] = %d\n" , i , j , DP[j]);
            }
        }
        printf("%d\n" , DP[0]);
    }
}*/

int main(){
    int t; 
    scanf("%d" , &t);
    while(t--){
        ll M;
        scanf("%lld" , &M);
        /*ll N = M / 2 , ans = 0;
        for(ll j = 0; j <= N; ++j){
            ans += (N - j) / 2 + 1;
            ans %= mod;
        }*/
        printf("%lld\n" , (M / 4 + 1) % mod * (((M / 2 + 1) / 2 + 1) % mod) % mod);
    }
}