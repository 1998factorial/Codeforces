#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll N , M , a , b;
    cin >> N >> M >> a >> b;
    ll r = N % M;
    cout << min(r * b , (M - r) * a) << endl;
}
