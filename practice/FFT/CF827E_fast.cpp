#pragma GCC optimize("Ofast")
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
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
int N , T;
char s[maxn];

// for a period k , bad pair (i , j)  means exist i and j such that 
// s[i] != s[j] , s[i] != ? , s[j] != ?
// eg. V ? K
// ->    V ? K
// note that, if period k is bad, then for all k' where k' is a divisor of k are bad

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
        c[i] = (int)(C[i].x + 0.5);
    }
    return c;
}

int main(){
    scanf("%d" , &T);
    while(T--){
        scanf("%d" , &N);
        scanf("%s" , s);
        vector<int> period(N + 1);
        vector<int> A(N) , B(N);
        for(int i = 0; i < N; ++i){
            if(s[i] == 'V')A[N - 1 - i] = 1;
            if(s[i] == 'K')B[i] = 1;
        }
        vector<int> C = multiply(A , B);
        for(int d = 1; d <= N; ++d){
            if(C[N - 1 + d] == 0)period[d] = 1;
        }
        for(int i = 0; i < N; ++i)A[i] = B[i] = 0;
        for(int i = 0; i < N; ++i){
            if(s[i] == 'K')A[N - 1 - i] = 1;
            if(s[i] == 'V')B[i] = 1;
        }
        C = multiply(A , B);
        for(int d = 1; d <= N; ++d){
            if(C[N - 1 + d] != 0)period[d] = 0;
        }
        for(int d = 1; d <= N; ++d){
            if(period[d]){
                for(int nd = 2 * d; nd <= N; nd += d){
                    if(period[nd] == 0){
                        period[d] = 0;
                        break;
                    }
                }
            }
        }
        vector<int> ans;
        for(int d = 1; d <= N; ++d){
            if(period[d])ans.push_back(d);
        }
        printf("%d\n" , (int)ans.size());
        for(int d : ans){
            printf("%d " , d);
        }
        printf("\n");
    }
}
