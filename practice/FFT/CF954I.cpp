#include <bits/stdc++.h>
#define ID if(1)
using namespace std;

const int maxn = 125005;
const double PI = acos(-1.0);

struct fast_fourier{
    struct Complex{
        double x , y;
        Complex(){}
        Complex(double x_ , double y_) : x(x_) , y(y_) {}
        Complex operator - (const Complex& rhs) const {
            return Complex(x - rhs.x , y - rhs.y);
        }
        Complex operator + (const Complex& rhs) const {
            return Complex(x + rhs.x , y + rhs.y);
        }
        Complex operator * (const Complex& rhs) const {
            return Complex(x * rhs.x - y * rhs.y , x * rhs.y + y * rhs.x);
        }
    };
    Complex A[maxn * 4] , B[maxn * 4] , C[maxn * 4];
    int N , M , L;
    void init(int n , int m){
        N = n; M = m;
    }
    void change(Complex y[] , int len) {
        int i, j, k;
        for (i = 1, j = len / 2; i < len - 1; i++) {
            if (i < j) swap(y[i], y[j]);
            k = len / 2;
            while (j >= k) {
                j = j - k;
                k = k / 2;
            }
            if (j < k) j += k;
        }
    }
    void FFT(Complex y[] , int len , int on) {
        change(y, len);
        for (int h = 2; h <= len; h <<= 1) {
            Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
            for (int j = 0; j < len; j += h) {
                Complex w(1, 0);
                for (int k = j; k < j + h / 2; k++) {
                    Complex u = y[k];
                    Complex t = w * y[k + h / 2];
                    y[k] = u + t;
                    y[k + h / 2] = u - t;
                    w = w * wn;
                }
            }
        }
        if (on == -1) {
            for (int i = 0; i < len; i++) {
                y[i].x /= len;
            }
        }
    }
    void multiply(int a[] , int b[]){ // multiply A and B
        int len = 1;
        // init length of C
        while(len < 2 * N || len < 2 * M) len <<= 1;
        L = len;
        // init polynomial A and B   
        for(int i = 0; i < L; ++i)A[i] = B[i] = Complex(0 , 0);
        for(int i = 0; i < N; ++i){
            if(a[i]){
                A[i] = Complex(1 , 0);
            }
        }
        for(int i = 0; i < M; ++i){
            if(b[i]){
                B[i] = Complex(1 , 0);
            }
        }
        // DO FFT on A and B
        FFT(A , len , 1);
        FFT(B , len , 1);
        // Convolute A and B to C
        for(int i = 0; i < len; ++i){
            C[i] = A[i] * B[i];
        }
        FFT(C , len , -1);
        // take the inverse of C
        // DONE
    }
} DO_FFT;

char S[maxn] , T[maxn];
int pa[6][maxn] , pb[6][maxn];
int neq[maxn * 4][6][6];
int fa[6];
int N , M;

inline int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){
    x = find(x); y = find(y); fa[x] = y;
}

int main(){
    scanf("%s" , S);
    scanf("%s" , T);
    N = strlen(S);
    M = strlen(T);
    reverse(T , T + M);
    for(int j = 0; j < N; ++j){
        pa[S[j] - 'a'][j] = 1;
    }
    for(int j = 0; j < M; ++j){
        pb[T[j] - 'a'][j] = 1;
    }
    DO_FFT.init(N , M);
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 6; ++j){
            if(i != j){
                DO_FFT.multiply(pa[i] , pb[j]);
                for(int k = 0; k < DO_FFT.L; ++k){
                    neq[k][i][j] = (int)(DO_FFT.C[k].x + 0.5);
                }
            }
        }
    }
    for(int k = M - 1; k <= N - 1; ++k){
        int ans = 0;
        for(int i = 0; i < 6; ++i)fa[i] = i;
        for(int i = 0; i < 6; ++i){
            for(int j = 0; j < 6; ++j){
                if(neq[k][i][j]){
                    if(find(i) != find(j)){
                        merge(i , j); ++ans;
                    }
                }
            }
        }
        printf("%d " , ans);
    }
}