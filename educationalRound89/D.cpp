#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
int N;
int a[maxn];

int gcd(int a , int b){
    return a == 0 ? b : gcd(b % a , a);
}

int main(){
    /*N = 200;
    for(int i = 1; i <= N; ++i){
        a[i] = i;
    }*/
    N = 1;
    a[1] = 7817670;
    vector<pair<int , int>> ans;
    for(int i = 1; i <= N; ++i){
        bool found = 0;
        for(int d1 = 2; d1 <= a[i] && found == 0; ++d1){
            if(a[i] % d1 == 0)
            for(int d2 = 2; d2 <= a[i] && found == 0; ++d2){
                if(a[i] % d2 == 0){
                    if(gcd(d1 + d2 , a[i]) == 1){
                        ans.emplace_back(d1 , d2);
                        found = 1;
                    }
                }
            }
        }
        if(!found){
            ans.emplace_back(-1 , -1);
        }
    }
    int i = 1;
    for(auto& e : ans){
        cout << i << " = " << e.first << " " << e.second << endl;
        ++i;
    }
}
