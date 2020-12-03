#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll c , f1 , f2 , f3 , N , vec[3];
// f[x] = c^(2x-6) * f[x-1] * f[x-2]  * f[x-3]
// c^xf[x] = c^(x-1)f[x-1] * c^(x-2)f[x-2] * c^(x-3)f[x-3]
// compute power of c , f1 , f2 , f3 for f[N]

inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

struct Matrix {
    ll mat[10][10];
    int N;
    Matrix(){}

    Matrix(int N_): N(N_){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                mat[i][j] = 0;
            }
        }
    }

    Matrix operator * (const Matrix& a) const {
        Matrix ret(N);
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                for(int k = 0; k < N; ++k){
                    ret.mat[i][j] += mat[i][k] * a.mat[k][j] % (MOD - 1);
                    if(ret.mat[i][j] >= MOD - 1)ret.mat[i][j] -= (MOD - 1);
                }
            }
        }
        return ret;
    }

    static Matrix identity(int N){
        Matrix ret(N);
        for(int i = 0; i < N; ++i){ 
            ret.mat[i][i] = 1;
        }
        return ret;
    }

    Matrix operator ^ (ll k) const {
        Matrix ret = identity(N);
        Matrix a = *this;
        while(k){
            if(k & 1)ret = ret * a;
            a = a * a;
            k /= 2;
        }
        return ret;
    }

};

int main(){
    scanf("%lld %lld %lld %lld %lld" , &N , &f1 , &f2 , &f3 , &c);
    ll ret = 1;
    Matrix A(3);
    A.mat[0][0] = A.mat[0][1] = A.mat[0][2] = A.mat[1][0] = A.mat[2][1] = 1;
    A = A ^ (N - 3);
    ll power = 0;
    // get power of c
    vec[0] = 3 , vec[1] = 2 , vec[2] = 1;
    for(int i = 0; i < 3; ++i){
        power += A.mat[0][i] * vec[i] % (MOD - 1);
        if(power >= MOD - 1)power -= (MOD - 1);
    }
    ret *= qpow(c , power);
    ret %= MOD;
    // divide by c^x
    ret *= qpow(qpow(c , N % (MOD - 1)) , MOD - 2);
    ret %= MOD;
    // get power of f1
    vec[0] = 0 , vec[1] = 0 , vec[2] = 1;
    power = 0;
    for(int i = 0; i < 3; ++i){
        power += A.mat[0][i] * vec[i] % (MOD - 1);
        if(power >= MOD - 1)power -= (MOD - 1);
    }
    ret *= qpow(f1 , power);
    ret %= MOD;
    // get power of f2
    vec[0] = 0 , vec[1] = 1 , vec[2] = 0;
    power = 0;
    for(int i = 0; i < 3; ++i){
        power += A.mat[0][i] * vec[i] % (MOD - 1);
        if(power >= MOD - 1)power -= (MOD - 1);
    }
    ret *= qpow(f2 , power);
    ret %= MOD;
    // get power of f3
    vec[0] = 1 , vec[1] = 0 , vec[2] = 0;
    power = 0;
    for(int i = 0; i < 3; ++i){
        power += A.mat[0][i] * vec[i] % (MOD - 1);
        if(power >= MOD - 1)power -= (MOD - 1);
    }
    ret *= qpow(f3 , power);
    ret %= MOD;
    printf("%lld\n" , ret);
}