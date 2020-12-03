#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 9;
int N , M;
int dir[8][2] = {{1 , 2} , {1 , -2} , {-1 , 2} , {-1 , -2} , {2 , 1} , {2 , -1} , {-2 , 1} , {-2 , -1}};
ll col[256];

int id(int i , int j){
    return j * M + i;
}

struct Matrix {
    ll mat[256][256];
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
                    ret.mat[i][j] += mat[i][k] * a.mat[k][j] % MOD;
                    if(ret.mat[i][j] >= MOD)ret.mat[i][j] -= MOD;
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
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%d %d" , &M , &N);
        if(N == 1){
            printf("%d\n" , (1 << M));
            continue;
        }
        int total = (1 << (2 * M));
        Matrix A(total);
        for(int mask = 0; mask < total; ++mask){
            int ok = 1;
            for(int i = 0; i < 2 * M && ok; ++i){
                if(mask & (1 << i)){
                    for(int j = 0; j < 2 * M && ok; ++j){
                        if( mask & (1 << j)){
                            // check if i and j can attack each other
                            int r1 = i % M , c1 = i / M , r2 = j % M , c2 = j / M;
                            for(int k = 0; k < 8 && ok; ++k){
                                 int nr = r1 + dir[k][0] , nc = c1 + dir[k][1];
                                if(nr == r2 && nc == c2){
                                    ok = 0;
                                }
                            }
                        }
                    }
                }
            }
            col[mask] = ok;
        }
        // now we need to compute the good states transition
        for(int mask = 0; mask < total; ++mask){
            if(!col[mask])continue;
            for(int nmask = 0; nmask < total; ++nmask){
                if(!col[nmask])continue;
                int ok = 1;
                for(int i = 0; i < M; ++i){
                    if(((mask >> (i + M)) & 1) != ((nmask >> i) & 1))ok = 0;
                }
                for(int i = 0; i < 2 * M; ++i){
                    if(mask & (1 << i)){
                        for(int j = 0; j < 2 * M; ++j){
                            if(nmask & (1 << j)){
                                int r1 = i % M , c1 = i / M , r2 = j % M , c2 = j / M + 1;
                                for(int k = 0; k < 8; ++k){
                                    int nr = r1 + dir[k][0] , nc = c1 + dir[k][1];
                                    if(nr == r2 && nc == c2){
                                        ok = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                A.mat[nmask][mask] = ok;
            }
        }
        A = A ^ (N - 2);
        ll ret = 0;
        for(int i = 0; i < total; ++i){
            for(int j = 0; j < total; ++j){
                ret += A.mat[i][j] * col[j] % MOD;
                if(ret >= MOD)ret -= MOD;
            }
        }
        printf("%lld\n" , ret);
    }
}

