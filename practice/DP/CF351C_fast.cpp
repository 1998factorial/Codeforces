#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
int N , M , a[20] , b[20];
// key : at any moment, #l - #r <= 2N, else we can always swap one l with one r after this range

struct Matrix{
    ll mat[55][55];
    int N;

    Matrix(int N_){
        N = N_;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                mat[i][j] = INF;
            }
        }
    }

    Matrix operator * (const Matrix& o) const {
        Matrix ret(N);
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                for(int k = 0; k < N; ++k){
                    ret.mat[i][j] = min(ret.mat[i][j] , mat[i][k] + o.mat[k][j]);
                }
            }
        }
        return ret;
    }

    static Matrix identity(int N_){
        Matrix ret(N_);
        for(int i = 0; i < N_; ++i){
            ret.mat[i][i] = 0;
        }
        return ret;
    }

    Matrix operator ^ (int k) const {
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
    scanf("%d %d" , &N , &M);
    for(int i = 0; i < N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 0; i < N; ++i){
        scanf("%d" , &b[i]);
    }
    Matrix ans(2 * N + 1) , A(2 * N + 1);
    ans.mat[0][0] = 0;
    for(int i = 0; i <= 2 * N; ++i)A.mat[i][i] = 0;
    for(int i = 0; i < N; ++i){
        Matrix cur(2 * N + 1);
        for(int j = 0; j <= 2 * N; ++j){
            if(j - 1 >= 0)cur.mat[j - 1][j] = a[i];
            if(j < 2 * N)cur.mat[j + 1][j] = b[i];
        }
        A = A * cur;
    }
    /*for(int i = 0; i <= 2 * N; ++i){
        for(int j = 0; j <= 2 * N; ++j){
            printf("A[%d][%d] = %lld\n" , i , j , A.mat[i][j]);
        }
    }*/
    ans = ans * (A ^ M);
    printf("%lld\n" , ans.mat[0][0]);
}