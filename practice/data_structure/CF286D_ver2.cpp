/*
    sweeping line, rating 2600

    A very difficult problem that requires careful counting and significant amount of organizations.
    First, we need to draw the y - t relation diagram, then we should realise that this is a sweeping problem.
    How do we accumulate results?
    we can split y[0 , maxr] into intervals, and we can find the "latest time that we will miss this interval"
    as well as "earliest time that we will cover this interval fully", call them [tl , tr]
    so we will have the following 2 events :
        1. miss event : (t - r , -1)
        2. cover event : (t - r , 1)
    notice that t - r < t - l, so for an interval [yi , yi+1] , we will encounter "miss" before "cover".
    when we encounter miss , our ans -= t - r , and cnt++
    when we encounter cover , our ans += t - l , and cnt--
    each time when we answer a query at time q, for [l , r] , if we have encounter both "miss" and "cover"
    then this interval should contribute -(t - r) + (t - l) = r - l which is correct.
    if we only encounter "miss" , then this interval should contribute q - (t - r), this can be derived by
    -(t - r) + 1 * q , where 1 is included in cnt.

    Overrall time complexity : O((N + M) * log(N + M))
*/
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;

inline int read(){ // fast read
    int x = 0 , f = 1 , c = getchar();
    for(; !isdigit(c); c = getchar()){
        if(c == '-'){
            f = -1;
        }
    }
    for(; isdigit(c); c = getchar()){
        x = x * 10 + c - '0';
    }
    return x * f;
}

struct wall{ // use this to break y[0 , maxr] into intervals by sweeping
    int pos , time , f;
    wall(){}
    wall(int a , int b , int c) : pos(a) , time(b) , f(c) {}
    bool operator < (const wall& rhs) const {
        return pos < rhs.pos;
    }
};

vector<wall> walls;
vector<ii> events;
int N , M;

int main(){
    N = read(); M = read();
    for(int i = 1; i <= M; ++i){
        int l , r , t; l = read(); r = read(); t = read();
        walls.emplace_back(l , t , 1);
        walls.emplace_back(r , t , -1);
    }
    sort(walls.begin() , walls.end());
    multiset<int> s;
    int pre = 0;
    for(auto& wall : walls){
        int cur = wall.pos , t = wall.time , f = wall.f;
        if(!s.empty()){
            int etime = *s.begin();
            events.emplace_back(etime - cur , -1); // latest time we miss this interval
            events.emplace_back(etime - pre , 1); // earliest time we full cover this interval
        }
        pre = cur;
        if(f > 0)s.insert(t);
        else s.erase(s.find(t));
    }
    sort(events.begin() , events.end());
    int ret = 0 , cnt = 0;
    for(int i = 1 , j = 0; i <= N; ++i){
        int cur_time; cur_time = read();
        for(; j < events.size() && events[j].x <= cur_time; ++j){
            int sign = (events[j].y < 0) ? -1 : 1;
            cnt -= sign;
            ret += sign * events[j].x;
        }
        printf("%d\n" , ret + cnt * cur_time);
    }
}
