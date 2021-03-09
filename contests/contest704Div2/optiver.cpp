#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c){
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2){
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

vector<int> g[maxn];
set<int> tree[maxn];
int dfn[maxn] , low[maxn] , sccid[maxn] , cnt = 0 , cpn = 0;
int instack[maxn];
int DP[maxn];
int vis[maxn];
int best[maxn];
vector<int> st;
map<string , int> mp;

void tarjan(int v){
    st.push_back(v);
    instack[v] = 1;
    dfn[v] = low[v] = ++cnt;
    for(int nv : g[v]){
        if(dfn[nv] == -1){
            tarjan(nv);
            low[v] = min(low[v] , low[nv]);
        }
        else if(instack[nv]){
            low[v] = min(low[v] , dfn[nv]);
        }
    }
    if(low[v] == dfn[v]){
        ++cpn;
        for(;;){
            int c = st.back();
            instack[c] = 0;
            sccid[c] = cpn;
            st.pop_back();
            if(c == v)break;
        }
    }
}

void DFS(int v){
    vis[v] = 1;
    for(int nv : tree[v]){
        DFS(nv);
        //DP[v] = min(DP[v] , DP[nv]);
        if(DP[v] > DP[nv]){
            DP[v] = DP[nv];
            best[v] = best[nv];
        }
    }
}

string solve(string line , vector<string> words , int N , vector<int> from , vector<int> to){
    for(int i = 0; i < from.size(); ++i){
        g[from[i]].push_back(to[i]);
    }
    for(int i = 0; i < N; ++i){
        mp[words[i]] = i;
        dfn[i] = -1;
        DP[i] = 200;
    }
    // run tarjan to get scc
    for(int i = 0; i < N; ++i){
        if(~dfn[i])continue;
        tarjan(i);
    }
    // construct SCC forest + init DP
    for(int i = 0; i < N; ++i){
        int id = sccid[i];
        //DP[id] = min(DP[id] , (int)words[i].size());
        if(DP[id] > (int)words[i].size()){
            DP[id] = (int)words[i].size();
            best[id] = i;
        }
        for(int j : g[i]){
            int nid = sccid[j];
            if(id == nid)continue;
            tree[id].insert(nid);
        }
    }
    for(int i = 1; i <= cpn; ++i){
        if(vis[i])continue;
        DFS(i);
    }
    vector<string> rr;
    SplitString(line , rr , " ");
    for(auto& s : rr){
        int id = sscid[mp[s]];
        s = words[best[id]];
    }
    string ans = "";
    for(int i = 0; i < rr.size(); ++i){
        if(i){
            ans += " ";
        }
        ans += rr[i];
    }
    return ans;
}

int main(){
    string line = "toward inhabit either never toward inhabit";
    vector<string> words = {"toward", "inhabit", "either", "never", "toward", "inhabit"};

}