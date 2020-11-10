#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
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
inline int qpow(int x , int n){
    int ret = 1;
    while(n){
        if(n & 1)ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }
    return ret;
}
const int mod = 1009;
const int maxn = 2e5 + 10;
const double PI = acos(-1.0);
int N , M , K;
int cnt[maxn];
vector<vector<int>> poly;


void change(vector<Complex>& y , int len) {
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

void FFT(vector<Complex>& y , int len , int on) {
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

vector<int> multiply(vector<int> a , vector<int> b){
    int n = a.size() , m = b.size() , len = 1 , i;
    while(len < 2 * n || len < 2 * m)len <<= 1;
    vector<Complex> A(len) , B(len) , C(len);
    for(i = 0; i < n; ++i)A[i] = Complex(a[i] , 0);
    for(i = n; i < len; ++i)A[i] = Complex(0 , 0);
    for(i = 0; i < m; ++i)B[i] = Complex(b[i] , 0);
    for(i = m; i < len; ++i)B[i] = Complex(0 , 0);
    FFT(A , len , 1);
    FFT(B , len , 1);
    for(i = 0; i < len; ++i)C[i] = A[i] * B[i];
    FFT(C , len , -1);
    vector<int> c(len);
    for(i = 0; i < len; ++i){
        long long v = (long long)(C[i].x + 0.5);
        v %= mod;
        c[i] = v;
    }
    return c;
}

vector<int> solve(int l , int r){
    if(l == r){
        vector<int> ret;
        for(int i : poly[l])ret.push_back(i);
        return ret;
    }
    int mid = (l + r) >> 1;
    return multiply(solve(l , mid) , solve(mid + 1 , r));
}

int main(){
    int i , x , j;
    scanf("%d %d %d" , &N , &M , &K);
    for(i = 1; i <= N; ++i){
        int x; scanf("%d" , &x); ++cnt[x];
    }
    for(i = 1; i <= M; ++i){
        if(cnt[i] == 0)continue;
        vector<int> pi(cnt[i] + 1 , 1);
        poly.push_back(pi);
    }
    vector<int> ret = solve(0 , poly.size() - 1);
    printf("%d\n" , ret[K] % mod);
}