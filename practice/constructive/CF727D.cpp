#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int cnt[6];
map<string , int> mp;
vector<int> g[6];
int N;

void init(){
    mp["S"] = 0;
    mp["M"] = 1;
    mp["L"] = 2;
    mp["XL"] = 3;
    mp["XXL"] = 4;
    mp["XXXL"] = 5;
}

vector<string> split(const string& str, const string& delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do{
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }while (pos < str.length() && prev < str.length());
    return tokens;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    for(int i = 0; i < 6; ++i)cin >> cnt[i];
    cin >> N;
    for(int i = 1; i <= N; ++i){
        string s; cin >> s;
        vector<string> r = split(s , ",");
        for(string j : r){
            g[mp[j]].push_back(i);
        }
    }
    for(int i = 0; i < 6; ++i){
        cout << i << " :";
        for(int j : g[i])cout << j << " ";
        cout << endl;
    }
}
