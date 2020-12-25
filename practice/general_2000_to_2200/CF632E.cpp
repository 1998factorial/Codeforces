#include <bits/stdc++.h>
using namespace std;

int N , K;
int a[1005];
const int maxn = 1e6;
const double PI = acos(-1.0);
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

vector<int> multiply(vector<int> a , vector<int> b){ // multiply polynomial a and b 
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
        if((int)(C[i].x + 0.5))c[i] = 1; // we only keep the sequence of zero and one
        else c[i] = 0;
    }
    return c;
}

vector<int> solve(vector<vector<int>>& poly , int l , int r){
    if(l == r){
        vector<int> ret;
        for(int i : poly[l])ret.push_back(i);
        return ret;
    }
    int mid = (l + r) >> 1;
    return multiply(solve(poly , l , mid) , solve(poly , mid + 1 , r));
}

int main(){
    scanf("%d %d" , &N , &K);
    int mx = 0;
    for(int i = 1; i <= N; ++i){
        int x;
        scanf("%d" , &x);
        a[x] = 1;
        mx = max(mx , x);
    }
    // answer is just the terms with non-zero coefficient in (x^a[1] + x^a[2] + ... + x^a[N]) ^ K
    vector<vector<int>> poly;
    for(int i = 1; i <= K; ++i){
        vector<int> vec;
        for(int j = 0; j <= mx; ++j){
            if(a[j]) vec.push_back(1);
            else vec.push_back(0);
        }
        poly.push_back(vec);
    } 
    vector<int> ans = solve(poly , 0 , K - 1);
    for(int i = 0; i < ans.size(); ++i){
        if(ans[i])printf("%d " , i);
    }
    printf("\n");
}