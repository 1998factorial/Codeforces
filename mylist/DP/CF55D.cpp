/*
    Dynamic programming
    Digit DP, if a number divides all it's digit then it divides their LCM
    observe that LCM(1...9) = 2520 , and number of all possible LCMs is no more than 50
    DP[i][j][k] = # of prefixs (from most significant digit) of length i , where it modules 2520 = j ,
    have kth LCM (the first one is 1 , the last one is 2520)
    note that we do not care about leading zeros
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[30];
int N;
ll DP[30][2520][50];
map<int , int> mp , imp;

ll gcd(ll n , ll m){
    return n == 0 ? m : gcd(m % n , n);
}

ll lcm(ll n , ll m){
    return n * m / gcd(n , m);
}

ll solve(int pos , int sum , int cur_lcm , int flag){
    if(pos <= 0){
        return sum % cur_lcm == 0;
    }
    if(~DP[pos][sum][mp[cur_lcm]] && !flag){
        return DP[pos][sum][mp[cur_lcm]];
    }
    ll ret = 0;
    int up = flag ? a[pos] : 9;
    for(int i = 0; i <= up; ++i){
        int nsum = (sum * 10 + i) % 2520;
        int nlcm = cur_lcm;
        if(i != 0)nlcm = lcm(nlcm , i);
        ret += solve(pos - 1 , nsum , nlcm , flag && (i == up));
    }
    if(!flag)DP[pos][sum][mp[cur_lcm]] = ret;
    return ret;
}

ll cal(ll num){
    N = 0;
    if(!num)a[++N] = 0;
    while(num){
        a[++N] = num % 10;
        num /= 10;
    }
    ll ret = solve(N , 0 , 1 , 1);
    return ret;
}

void init(){
    set<int> l;
    for(int i = 0; i < (1 << 10); ++i){
        vector<int> v;
        for(int j = 1; j < 10; ++j){
            if(i & (1 << j)){
                v.push_back(j);
            }
        }
        if(v.size()){
            ll ret = v[0];
            for(int j = 0; j < v.size(); ++j){
                ret = lcm(ret , v[j]);
            }
            l.insert(ret);
        }
    }
    int cnt = 1;
    for(int i : l){
        mp[i] = cnt;
        imp[cnt] = i;
        ++cnt;
    }
}


int main(){
    init();
    memset(DP , -1 , sizeof(DP));
    int t; cin >> t;
    while(t--){
        ll l , r; cin >> l >> r;
        cout << cal(r) - cal(l - 1) << endl;
    }
}
