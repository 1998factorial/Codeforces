/*
    Constructive
    the goal is to find number if pairs (x , y) , such that x < y <= N and x + y have the longest trailing 9s
    note that we can firstly get all the possible length of trailing 9s for number not greater than 10 ^ 10
    then, we check if N + N - 1 , which is the largest possible pair sum , can be greater than some length j
    of trailing 9s. Once we find such maximal j, we know that all pairs we want must sum to some number that has
    this number of 9s at the end. we can then count them.
    for each u = x99..9 , such u can be formed by using u - 1 + 1 , u - 2 + 2 , ...
    if u - 1 > N , we can use N + u - N , N - 1 + u - N + 1 ...
    which is (min(N , i - 1) - max(i - N , 1) + 1) / 2
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> g[11];
int N;

int main(){
    cin >> N;
    for(int i = 0; i < 9; ++i){
        g[0].push_back(i);
    }
    for(int i = 0; i < 10; ++i){
        for(ll j : g[i]){
            g[i + 1].push_back(j * 10 + 9);
        }
    }
    int start = -1;
    for(int i = 10; i >= 0 && start == -1; --i){
        if((ll)N + N - 1 >= g[i].front()){ // find longest trailing 9s that can be done
            start = i;
        }
    }
    ll ret = 0;
    for(ll i : g[start]){
        if((ll)N + N - 1 >= i){
            if(i <= N + 1){
                ret += (i - 1) / 2;
            }
            else{
                ret += ((ll)N + N + 1 - i) / 2;
            }
        }
    }
    cout << ret << endl;
}
