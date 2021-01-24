#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
const double PI = acos(-1.0);
char s[maxn];
int N , K;

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
    while(len < n + m)len <<= 1;
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
        c[i] = (int)(C[i].x + 0.5);
    }
    return c;
}

int main(){
    scanf("%d %d" , &N , &K);
    scanf("%s" , s);
    vector<int> ans(N + 1 , N);
    vector<int> v(N);
    for(int i = 0; i < N; ++i){
        if(s[i] == 'B')v[i] = 0;
        if(s[i] == 'Y')v[i] = 1;
        if(s[i] == 'R')v[i] = 2;
    }
    for(int i = 0; i < 3; ++i){
        vector<int> a(N);
        vector<int> b(2 * N);
        for(int j = 0; j < N; ++j){
            if(v[j] == i)a[N - j - 1] = b[j] = 1;
        }
        for(int j = N; j < 2 * N; ++j)b[j] = b[j - N];
        vector<int> c = multiply(a , b);
        for(int j = N , k = 1; j <= 2 * N - 2; ++j , ++k){
            ans[k] -= c[j];
        }
    }
    vector<int> id;
    for(int i = 1; i <= N - 1; ++i)id.push_back(i);
    sort(id.begin() , id.end() , [&](int l , int r){
        return ans[l] < ans[r];
    });
    int ret = id[K - 1];
    for(int i = 1; i <= N - 1; ++i){
        if(ans[ret] == ans[i]){
            ret = min(ret , i);
        }
    }
    printf("%d\n" , ret);
}