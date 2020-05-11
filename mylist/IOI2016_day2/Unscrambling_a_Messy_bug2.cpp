#include <bits/stdc++.h>
//#include "messy.h"

using namespace std;

int N;

vector<int> ret;

set<string> vis;
vector<int> perm = {3 , 2 , 0 , 1};
vector<string> data;

bool check_element(string s){
    return vis.find(s) != vis.end();
}

void add_element(string s){
    data.push_back(s);
}

void compile_set(){
    for(string s : data){
        string ns = s;
        for(int i = 0; i < s.size(); ++i){
            ns[i] = s[perm[i]];
        }
        vis.insert(ns);
        //cout << "inserting " << ns << endl;
    }
}

void add(int l , int r){
    if(l == r)return;
    int mid = (l + r) >> 1;
    string s = "";
    for(int i = 0; i < N; ++i){
        s += '1';
    }
    for(int i = l; i <= r; ++i){
        s[i] = '0';
    }
    for(int i = l; i <= mid; ++i){
        s[i] = '1';
        //cout << "adding " << s << endl;
        add_element(s);
        s[i] = '0';
    }
    add(l , mid);
    add(mid + 1 , r);
}


void solve(int l , int r , string ban){
    if(l == r){
        for(int i = 0; i < N; ++i){
            if(ban[i] == '0'){
                ret[i] = l;
                break;
            }
        }
    }
    else{
        string x = ban , y = "";
        int mid = (l + r) >> 1;
        for(int i = 0; i < N; ++i){
            y += '1';
        }
        for(int i = 0; i < N; ++i){
            if(ban[i] == '0'){
                ban[i] = '1';
                if(check_element(ban)){
                    x[i] = '1';
                    y[i] = '0';
                }
                ban[i] = '0';
            }
        }
        solve(l , mid , y);
        solve(mid + 1 , r , x);
    }
}

vector<int> restore_permutation(int n , int r , int w){
    N = n;
    ret.resize(N);
    add(0 , N - 1);
    compile_set();
    string s = "";
    for(int i = 0; i < N; ++i)s += '0';
    solve(0 , N - 1 , s);
    return ret;
}

int main(){
    cin >> N;
    int w = 896;
    ret = restore_permutation(N , w , w);
    for(int i : ret)cout << i << " ";
    cout << endl;
}
