#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int N;
string L , R;

// write a brute force solution and look for patterns
// if L[0] != R[0] , we can have N ones
// if L == R we just print R
// if L + 1 < R and lowest bit of R is 0 , answer is R + 1 (pattern)
// else, answer is R

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    cin >> L;
    cin >> R;
    auto addone = [&](string s){
        int sz = s.size() - 1;
        while(sz >= 0 && s[sz] == '1'){
            s[sz] = '0';
            --sz;
        }
        if(sz >= 0)s[sz] = '1';
        return s;
    };
    if(L == R){
        cout << R << endl;
        exit(0);
    }
    if(L[0] != R[0]){
        for(int i = 0; i < N; ++i)cout << 1;
        cout << endl;
        exit(0);
    }
    //cout << "L + 1 = " << addone(L) << endl;
    if(addone(L) != R && R[N - 1] == '0'){
        cout << addone(R) << endl;
        exit(0);
    }
    cout << R << endl;
}