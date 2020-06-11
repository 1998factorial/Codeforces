/*
    Sweep line , fenwick tree . rating 2200
    The key to solve this problem is to stay organized.
    details are written in the code section, most important thing is to realise that
    vertical and horizontal lines can be interpreted seperatly. so if we maintain the
    range sum of [x1 , x2] , and we fix a lower horizontal line h1, we can get all the
    vertical lines that intersect with h1 , and we sweep from small y to large y,
    if we see vertcal line, just -1, otherwise , we can query the range sum [xl , xr] ,
    the val will be the number of vertical lines intersect with both h1 and this upper horizontal line
    and ans += (val) * (val - 1) / 2 as we are free to choose any to vertical lines to make a rectangle.
    overrall time complexity : O(N * N * logN) ~ O(5 * 10 ^ 8) , which a 2 second limit allows to pass.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e4 + 10;
const int base = 5001;

ll sum[maxn << 2];

int N;
vector<ii> horizontal[maxn]; // h[y] : {xl , xr}
vector<ii> vertical[maxn]; // v[y] : {yr , x}
vector<int> del[maxn]; // del[y] : {x1} decrememt at x1 when sweeping to y


void update(int pos , ll val){
    while(pos < maxn){
        sum[pos] += val; pos += (-pos) & pos;
    }
}

ll get(int pos){
    ll ret = 0;
    while(pos){
        ret += sum[pos]; pos -= pos & (-pos);
    }
    return ret;
}

int main(){
    scanf("%d" , &N);
    int max_y = 0;
    for(int i = 1; i <= N; ++i){
        int x1 , y1 , x2 , y2; scanf("%d %d %d %d" , &x1 , &y1 , &x2 , &y2);
        x1 += base; x2 += base; y1 += base; y2 += base; // scale them and get rid off the negative values
        if(y1 == y2){ // horizontal line
            if(x1 > x2)swap(x1 , x2);
            horizontal[y1].emplace_back(x1 , x2);
        }
        else if(x1 == x2){ // vertical line
            if(y1 > y2)swap(y1 , y2);
            vertical[y1].emplace_back(y2 , x1);
        }
        max_y = max(max_y , max(y1 , y2));
    }
    ll ans = 0;
    // fix a lower horizontal line
    for(int y1 = 1; y1 < maxn; ++y1){
        for(auto& e : horizontal[y1]){
            int l = e.first , r = e.second;
            //cout << "fixing horizontal line : " << l << " " << r << " at y = " << y1 << endl;
            memset(sum , 0 , sizeof(sum));
            for(int i = 1; i < maxn; ++i)del[i].clear();
            for(int y2 = 1; y2 <= y1; ++y2){
                for(auto& v : vertical[y2]){
                    int yy = v.first , xx = v.second;
                    if(l <= xx && xx <= r && yy > y1){
                        //cout << " considering vertical line : " << y2 << " " << yy << " at x = " << xx << endl;
                        del[yy + 1].push_back(xx);
                        update(xx , 1);
                    }
                }
            }
            //cout << get(maxn - 1) << endl;
            for(int y2 = y1 + 1; y2 < maxn; ++y2){
                for(int& p : del[y2]){
                    //printf("at y = %d , delete vertical line at x = %d\n" , y2 , p);
                    update(p , -1);
                }
                for(auto& h : horizontal[y2]){
                    ll val = get(h.second) - get(h.first - 1);
                    //printf("at y = %d , query(%d %d) = %lld\n" , y2 , h.first , h.second , val);
                    ans += val * (val - 1) / 2;
                }
            }
        }
    }
    printf("%lld\n" , ans);
}
