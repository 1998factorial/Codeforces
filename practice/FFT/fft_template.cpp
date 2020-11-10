#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef pair<int , int> ii;
const int maxn = 4e5 + 20;
const double PI = acos(-1.0);
int N , X , Y , Q , base;
int a[maxn / 2];
int ans[1000005];

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
        ID printf("L = %d\n" , L);
        // init polynomial A and B   
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
        FFT(A , len , 1);
        FFT(B , len , 1);
        for(int i = 0; i < len; ++i){
            C[i] = A[i] * B[i];
        }
        FFT(C , len , -1);
    }

    void get_C(set<int>& ret){
        for(int i = 0; i < L; ++i){
            if((int)(C[i].x + 0.5) > 0 && i - 2 * base > 0){
                ret.insert(2 * (i - 2 * base + Y));
            }
        }
    }

} DO_FFT;

int aa[maxn * 4] , bb[maxn * 4];

int main(){
    scanf("%d %d %d" , &N , &X , &Y);
    for(int i = 0; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    DO_FFT.init(a[N] * 2 + 1 , a[N] * 2 + 1);
    base = a[N];
    for(int i = 0; i <= N; ++i){
        ++aa[base + a[i]];
    }
    for(int i = 0; i <= N; ++i){
        ++bb[base - a[i]];
    }
    DO_FFT.multiply(aa , bb);
    set<int> C;
    DO_FFT.get_C(C);
    memset(ans , -1 , sizeof(ans));
    for(int i = 2; i <= 1000000; ++i){ // O(NlogN)
        if(C.find(i) != C.end()){
            for(int j = i; j <= 1000000; j += i){
                ans[j] = max(ans[j] , i);
            }
        }
    }
    scanf("%d" , &Q);
    while(Q--){
        int l; 
        scanf("%d" , &l);
        printf("%d " , ans[l]);
    }
    printf("\n");
}   