#include <bits/stdc++.h>
//#include "messy.h"
using namespace std;

/*
    constructive algorithm

    N = 4
    add 1000 , 0100 , 1110 , 1011
    place extra ones on the bits that we do not care.

    check 1000 , 0100 , 0010 , 0001 in [0 , 3]
    2 will work
    get bit position for first 2 bits
    then split into 2 sub problems
    check 1011 , 0111 in [0 , 1] , one will work
    check 1110 , 1101 in [2 , 3] , one will work
*/

vector<string> data;
set<string> vis;
vector<int> perm = {3 , 2 , 0 , 1};

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
        cout << "inserting " << ns << endl;
    }
}


vector<int> ret;
int N;

void add(int l , int r){
    if(l == r)return;
    int mid = (l + r) >> 1;
    string s = "";
    for(int i = 0; i < N; ++i)s += '1';
    for(int i = l; i <= r; ++i)s[i] = '0';
    // s[l ... r] = '0..0' , '1' else where
    for(int i = l; i <= mid; ++i){
        s[i] = '1';
        add_element(s);
        cout << "adding " << s << endl;
        s[i] = '0';
    }
    add(l , mid);
    add(mid + 1 , r);
}

void solve(int l , int r , string banned){ // banned[i] = '1' means ith bit is banned in this subproblem
    cout << l << " " << r << " " << banned << endl;
    if(l == r){
        // find only zero
        for(int i = 0; i < N; ++i){
            if(banned[i] == '0'){
                cout << "let " << i << " -> " << l << endl;
                ret[i] = l;
                break;
            }
        }
    }
    else{
        int mid = (l + r) >> 1;
        string x = banned , y = "";
        for(int i = 0; i < N; ++i)y += '1';
        for(int i = 0; i < N; ++i){
            if(banned[i] == '0'){
                banned[i] = '1';
                if(check_element(banned)){
                    x[i] = '1';
                    y[i] = '0';
                }
                banned[i] = '0';
            }
        }
        solve(l , mid , y); // y has mid - l + 1 0s that are the candidate for bits in [l , mid]
        solve(mid + 1 , r , x); // x has r - mid 0s that are the candidate for bits in [mid + 1 , r]
    }
}

vector<int> restore_permutation(int n , int w , int r){
    N = n;
    add(0 , N - 1);
    compile_set();
    ret.resize(N);
    string s = "";
    for(int i = 0; i < N; ++i)s += '0';
    solve(0 , N - 1 , s);
    return ret;
}


int main(){
    cin >> N;
    int w = 896 , r = 896;
    vector<int> rr = restore_permutation(N , w , r);
    for(int i : rr)cout << i << " ";
    cout << endl;
}
