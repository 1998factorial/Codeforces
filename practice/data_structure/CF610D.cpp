#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int N , total;
vector<array<int , 4>> tv , th;
map<int , int> mp , imp;

ll sum[maxn * 8];

void add(int pos , ll v){
    while(pos <= total){
        sum[pos] += v;
        pos += pos & (-pos);
    }
}

ll ask(int pos){
    ll ans = 0;
    while(pos){
        ans += sum[pos];
        pos -= pos & (-pos);
    }
    return ans;
}

vector<int> addevent[maxn * 4] , delevent[maxn * 4];
vector<array<int , 2>> query[maxn * 4];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> tmp;
    for(int i = 1; i <= N; ++i){
        int x1 , y1 , x2 , y2;
        int ver;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2)swap(x1 , x2);
        if(y1 > y2)swap(y1 , y2);
        tmp.push_back(x1);
        tmp.push_back(x2);
        tmp.push_back(y1);
        tmp.push_back(y2);
        if(y1 == y2)ver = 0;
        else ver = 1;
        if(ver){
            tv.push_back({x1 , y1 , x2 , y2});
        }
        else{
            th.push_back({x1 , y1 , x2 , y2});
        }
    }
    total = 0;
    sort(tmp.begin() , tmp.end());
    for(int i : tmp){
        if(!mp[i]){
            mp[i] = ++total;
            imp[total] = i;
        }
    }
    // merge horizontal lines
    map<int , vector<array<int , 2>>> H , nH;
    for(auto& e : th){
        H[e[1]].push_back({e[0] , e[2]});
    }
    for(auto& e : H){
        auto vec = e.y;
        if(vec.empty())continue;
        sort(vec.begin() , vec.end());
        for(int i = 0; i < vec.size(); ){
            int j = i , val = vec[i][1];
            while(j + 1 < vec.size() && vec[j + 1][0] <= val)val = max(val , vec[j + 1][1]) , ++j;
            nH[e.x].push_back({vec[i][0] , val});
            i = j + 1;
        }       

    }
    // merge vertical lines
    map<int , vector<array<int , 2>>> V , nV;
    for(auto& e : tv){
        V[e[0]].push_back({e[1] , e[3]});
    }
    for(auto& e : V){
        auto vec = e.y;
        if(vec.empty())continue;
        sort(vec.begin() , vec.end());
        for(int i = 0; i < vec.size();){
            int j = i , val = vec[i][1];
            while(j + 1 < vec.size() && vec[j + 1][0] <= val)val = max(val , vec[j + 1][1]) , ++j;
            nV[e.x].push_back({vec[i][0] , val});
            i = j + 1;
        }
    }
    // we need to subtract the number of intersection points
    ll ans = 0;
    for(auto& e : nH){
        auto vec = e.y;
        for(auto& v : vec){
            ans += v[1] - v[0] + 1;
            addevent[mp[v[0]]].push_back(mp[e.x]);
            delevent[mp[v[1]]].push_back(mp[e.x]);
        }
    }
    for(auto& e : nV){
        auto vec = e.y;
        for(auto& v : vec){
            ans += v[1] - v[0] + 1;
            query[mp[e.x]].push_back({mp[v[0]] , mp[v[1]]});
        }
    }

    for(int t = 1; t <= total; ++t){
        // process add first
        for(int p : addevent[t]){
            add(p , 1);
        }
        // then query
        for(auto& e : query[t]){
            ans -= ask(e[1]) - ask(e[0] - 1);
        }
        // last delete
        for(int p : delevent[t]){
            add(p , -1);
        }
    }

    cout << ans << endl;
}