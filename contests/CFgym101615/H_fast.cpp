#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const ll INF = 1e18;
// DP[i] = min{(DP[j] + e[j]^2) - 2 * e[j] * s[i]} + s[i]^2
// mx + b <=> (m = -2 * e[j]) * (x = s[i]) + (b = DP[j] + e[j]^2)
// then use CHT 
struct event{
    int t , id;
    event(){}
    event(int t_ , int id_) : t(t_) , id(id_) {}
    bool operator < (const event& rhs) const {
        return t < rhs.t;
    }
};
struct flight{
    ll from , to , s , e;
    flight(){}
    flight(ll f_ , ll t_ , ll s_ , ll e_) : from(f_) , to(t_) , s(s_) , e(e_)  {}
};
struct line{
    ll m , b;
    line(){}
    line(ll m_ , ll b_) : m(m_) ,  b(b_) {}
    ll f(int x){
        return m * x + b;
    }
};
double intersect(line x , line y){
    return (double)(y.b - x.b) / (x.m - y.m);
}
int N , M;
event eve[maxn * 2];
flight f[maxn];
vector<line> city[maxn];
ll DP[maxn];
void add(int i , line l){ // add a line to city i
    int n = city[i].size();
    while(n >= 2 && intersect(city[i][n - 1] , city[i][n - 2]) >= intersect(city[i][n - 1] , l)){
        city[i].pop_back();
        --n;
    }
    city[i].push_back(l);
}
ll query(int i , int x){ // return the min value of some line at x = x, for city i
    int l = 0 , r = city[i].size() - 2;
    int id = city[i].size() - 1;
    // l[i] is dominating at [intersect(l[i - 1] , l[i]) , intersect(l[i] , l[i + 1])]
    while(l <= r){
        int mid = (l + r) >> 1;
        if(intersect(city[i][mid] , city[i][mid + 1]) >= x)
            id = mid , r = mid - 1;
        else 
            l = mid + 1;
    }
    return id >= 0 ? city[i][id].f(x) : INF;
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        scanf("%lld %lld %lld %lld" , &f[i].from , &f[i].to , &f[i].s , &f[i].e);
        // split flight into 2 events
        // depart & arrive
        eve[2 * i - 1] = event(f[i].s , i);
        eve[2 * i] = event(f[i].e , -i);
    }
    sort(eve + 1 , eve + 1 + 2 * M);
    line l0 = line(0 , 0);
    add(1 , l0);
    // DP[i] = min{(DP[j] + e[j]^2) - 2 * e[j] * s[i]} + s[i]^2
    // mx + b <=> (m = -2 * e[j]) * (x = s[i]) + (b = DP[j] + e[j]^2)
    for(int i = 1; i <= 2 * M; ++i){
        int id = eve[i].id;
        if(id < 0){
            id *= -1;
            // we arrive
            // means we add line
            int cid = f[id].to;
            line l = line(-2ll * f[id].e , DP[id] + f[id].e * f[id].e);
            add(cid , l);
        }
        else{
            // we depart 
            // means we query
            int cid = f[id].from;
            ll x = f[id].s;
            DP[id] = query(cid , x) + x * x;
        }
    }
    ll ret = INF;
    for(int i = 1; i <= M; ++i){
        if(f[i].to == N){
            ret = min(ret , DP[i]);
        }
    }   
    printf("%lld\n" , ret);
}