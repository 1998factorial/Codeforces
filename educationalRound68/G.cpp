/*
    Dynamic programming (digit DP) rating 2700
    for a good base fraction, x / y , where both x and y are in [1,9]
    we can count the number of X / Y that can be reduced to x / y.
    Notice that X / Y = z * (x / y) , and max(X , Y) <= N
    so we need to find the number good z without iterating on all possible z.
    Here we can use digit DP. we need to keep track with the next digit of
    z * x and z * y. So we need to store the carry on both numerator and denominator.
    we also need to check if x * z's decimal representation contains any k * x, and if
    y * z contains any k * y. We also need a flag that tells us if the current prefix is
    smaller/greater than prefix of N.
    Details in code
*/
#include <bits/stdc++.h>
//#define ID true
using namespace std;
typedef long long ll;

const ll mod = 998244353;
string S;
int N , up[10] , down[10];
ll DP[105][10][10][32][32][2][2];

int gcd(int n , int m){
    return n == 0 ? m : gcd(m % n , n);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> S; N = S.size();
    ll ret = 0; // we start with N as ret, as all X / X are good fractions
    for(int i = 0; i < N; ++i){
        ret = (ret * 10 % mod + S[i] - '0') % mod;
    }
    reverse(S.begin() , S.end());
    for(int x = 1; x <= 9; ++x){
        for(int y = x + 1; y <= 9; ++y){
            if(gcd(x , y) != 1)continue;
            memset(DP , 0 , sizeof(DP));
            memset(up , -1 , sizeof(up));
            memset(down , -1 , sizeof(down));
            int tot = 0;
            for(int k = 1; k * y <= 9; ++k){
                up[k * x] = tot;
                down[k * y] = tot;
                ++tot;
            }
            DP[0][0][0][0][0][1][1] = 1;
            for(int i = 0; i < N; ++i){
                for(int d = 0; d <= 9; ++d){ // say we put d on z[i + 1]
                    for(int c1 = 0; c1 < 10; ++c1){
                        int nd1 = x * d + c1 , nc1 = nd1 / 10; // get the new carry on numerator
                        nd1 %= 10; // get the next digit on numerator
                        for(int c2 = 0; c2 < 10; ++c2){
                            int nd2 = y * d + c2 , nc2 = nd2 / 10; // get the new carry on denominator
                            nd2 %= 10; // get the next digit on denominator
                            for(int s1 = 0; s1 < (1 << tot); ++s1){
                                int ns1 = s1 | (up[nd1] != -1 ? 1 << up[nd1] : 0);
                                for(int s2 = 0; s2 < (1 << tot); ++s2){
                                    int ns2 = s2 | (down[nd2] != -1 ? 1 << down[nd2] : 0);
                                    for(int f1 = 0; f1 < 2; ++f1){
                                        int nf1 = nd1 == S[i] - '0' ? f1 : nd1 < S[i] - '0'; // comp on prefix on numerator
                                        for(int f2 = 0; f2 < 2; ++f2){
                                            int nf2 = nd2 == S[i] - '0' ? f2 : nd2 < S[i] - '0';
                                            DP[i + 1][nc1][nc2][ns1][ns2][nf1][nf2] += DP[i][c1][c2][s1][s2][f1][f2];
                                            DP[i + 1][nc1][nc2][ns1][ns2][nf1][nf2] %= mod;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            ll cnt = 0;
            for(int s1 = 0; s1 < (1 << tot); ++s1){ // as long as they have k * x and k * y
                for(int s2 = 0; s2 < (1 << tot); ++s2){
                    if(s1 & s2){
                        cnt += DP[N][0][0][s1][s2][1][1];
                        cnt %= mod;
                    }
                }
            }
            ret = (ret + cnt * 2 % mod) % mod;
        }
    }
    cout << ret << endl;
}
