#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int maxn = 200005;
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
char S[maxn] , T[maxn];
int Ssum[4][maxn];
vector<int> a[4] , b[4] , c[4];
int N , M , K;

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

void init(){
    int i , j;  
    for(i = 0; i < N; ++i){
        if(S[i] == 'A')S[i] = '0';
        if(S[i] == 'T')S[i] = '1';
        if(S[i] == 'G')S[i] = '2';
        if(S[i] == 'C')S[i] = '3';
        for(j = 0; j <= 3; ++j){
            Ssum[j][i + 1] = Ssum[j][i];
        }
        ++Ssum[S[i] - '0'][i + 1];
    }
    for(i = 0; i < M; ++i){
        if(T[i] == 'A')T[i] = '0';
        if(T[i] == 'T')T[i] = '1';
        if(T[i] == 'G')T[i] = '2';
        if(T[i] == 'C')T[i] = '3';
    }
}

int main(){
    int i , j;
    scanf("%d %d %d" , &N , &M , &K);
    scanf("%s" , S);
    scanf("%s" , T);
    reverse(T , T + M);
    init();
    for(j = 0; j <= 3; ++j)a[j].clear() , b[j].clear() , c[j].clear();
    for(j = 0; j <= 3; ++j)a[j].resize(N) , b[j].resize(M);
    for(j = 0; j <= 3; ++j){
        for(i = 0; i < N; ++i){
            int l = max(0 , i - K) , r = min(N - 1 , i + K);
            a[j][i] = (Ssum[j][r + 1] > Ssum[j][l]);
        }
        for(i = 0; i < M; ++i){
            b[j][i] = (T[i] == '0' + j);
        }
    }
    for(j = 0; j <= 3; ++j){
        c[j] = multiply(a[j] , b[j]);
    }
    int ans = 0;
    for(i = 0; i <= N - M; ++i){
        int acc = 0;
        for(j = 0; j <= 3; ++j)acc += c[j][M + i - 1];
        ans += acc >= M;
    }
    printf("%d\n" , ans);
}