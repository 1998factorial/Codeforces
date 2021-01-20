#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9;

struct Matrix{
    ll mat[(1 << 8) + 5][(1 << 8) + 5];
    int N;

    Matrix(int N_){
        N = N_;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                mat[i][j] = 0;
            }
        }
    }

    Matrix operator * (const Matrix& o) const {
        Matrix ret(N);
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                for(int k = 0; k < N; ++k){
                    ret.mat[i][j] += (mat[i][k] * o.mat[k][j]) % MOD;
                    ret.mat[i][j] %= MOD;
                }
            }
        }
        return ret;
    }

    static Matrix identity(int N_){
        Matrix ret(N_);
        for(int i = 0; i < N_; ++i){
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

ll N , M;

void DFS(int pos , int from , int to , Matrix& A){
    if(pos >= N){
        ++A.mat[from][to];
    }
    else{
        if(from & (1 << pos)){
            DFS(pos + 1 , from , to , A);
            DFS(pos + 1 , from , to | (1 << pos) , A);
            if(pos + 1 < N && from & (1 << (pos + 1))){
                DFS(pos + 2 , from , to | (1 << pos) | (1 << (pos + 1)) , A);
            }
        }
        else{
            DFS(pos + 1 , from , to | (1 << pos) , A);
        }
    }
}

int main(){
    cin >> N;
    cin >> M;
    Matrix A(1 << N) , ans(1 << N);
    for(int mask = 0; mask < 1 << N; ++mask){
        DFS(0 , mask , 0 , A);
    }
    for(int mask = 0; mask < 1 << N; ++mask){
        ans.mat[0][mask] = A.mat[(1 << N) - 1][mask];
    }
    A = A ^ (M - 1);
    ans = ans * A;
    cout << ans.mat[0][(1 << N) - 1] << endl;
}