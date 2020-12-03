#include <bits/stdc++.h>
using namespace std;
// Hard DP , 2800
// S(k) = number that represents k, but digits are sorted
// eg. S(5) = 5 , S(50394) = 3459 , S(353535) = 333555
// compute sum{S(k) | 1 <= k <= X} % MOD
// X <= 1e700
typedef long long ll;
const ll MOD = 1e9 + 7;
char X[705];
int N;

int main(){
    scanf("%s" , X);
    N = strlen(X);
    // TODO
}