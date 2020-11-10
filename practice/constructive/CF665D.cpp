/*
    Constructive
    we can either have {even , odd} where they are greater than 1 and even + odd -> prime
    or we can have {1 ,.., 1 , even} and even + 1 -> prime
    case work and easy result
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int a[1005];
int N;
set<int> prime;
bool vis[maxn * 2];

void sieve(){
    for(int i = 2; i < maxn * 2; ++i){
        if(!vis[i]){
            prime.insert(i);
            for(int j = i; j < maxn * 2; j += i){
                vis[j] = 1;
            }
        }
    }
}

int main(){
    cin >> N; for(int i = 1; i <= N; ++i)cin >> a[i];
    sieve();
    sort(a + 1 , a + 1 + N);
    unordered_map<int , int> cnt;
    for(int i = 1; i <= N; ++i){
        ++cnt[a[i]];
    }
    vector<int> ret;
    if(cnt[1] >= 1){
        // {1 , 1 , .... , x}
        for(int i = 1; i <= N; ++i){
            if(a[i] == 1){
                ret.push_back(a[i]);
            }
            else{
                break;
            }
        }
        for(int i = 1; i <= N; ++i){
            if(a[i] > 1 && prime.find(1 + a[i]) != prime.end()){
                ret.push_back(a[i]);
                break;
            }
        }
        // or {even , odd}
        vector<int> ret2;
        for(int i = 1; i <= N && ret2.empty(); ++i){
            for(int j = 1; j <= N && ret2.empty(); ++j){
                if(i != j && prime.find(a[i] + a[j]) != prime.end()){
                    ret2.push_back(a[i]);
                    ret2.push_back(a[j]);
                }
            }
        }
        if(ret2.size() > ret.size()){
            ret = ret2;
        }
    }
    else{
        // {even , odd}
        for(int i = 1; i <= N && ret.empty(); ++i){
            for(int j = 1; j <= N && ret.empty(); ++j){
                if(i != j && prime.find(a[i] + a[j]) != prime.end()){
                    ret.push_back(a[i]);
                    ret.push_back(a[j]);
                }
            }
        }
    }
    if(ret.empty())ret.push_back(a[1]);
    cout << (int)ret.size() << endl;
    for(int i : ret)cout << i << " ";
    cout << endl;
}
