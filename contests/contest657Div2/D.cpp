#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef pair<int , int> ii;

const int maxn = 3e5 + 10;

struct interval{
    int l , r , id , e;
    interval(){}
    interval(int l_ , int r_ , int id_ , int e_) : l(l_) , r(r_) , id(id_) , e(e_) {}
};
vector<interval> intervals;
int N , M , H , K;
int h[maxn] , m[maxn];
vector<int> tmp;
map<int , int> mp , imp;
vector<int> add[maxn] , del[maxn];
int tot;

int main(){
    tot = 0;
    scanf("%d %d %d %d" , &N , &H , &M , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d" , &h[i] , &m[i]);
        int l = (m[i] + 1 + (M / 2)) % (M / 2);
        int r = (m[i] + K + (M / 2)) % (M / 2);
        if(l > r){
            intervals.emplace_back(l , M / 2 - 1 , i , 0);
            intervals.emplace_back(0 , r , i , 1);
        }
        else{
            intervals.emplace_back(l , r , i , 1);
        }
        tmp.push_back(l);
        tmp.push_back(r);
    }
    tmp.push_back(0);
    tmp.push_back(M / 2 - 1);
    sort(tmp.begin() , tmp.end());
    for(int i : tmp){
        if(!mp[i]){
            mp[i] = ++tot;
            imp[tot] = i;
        }
    }
    for(int i = 0; i < intervals.size(); ++i){
        int l = intervals[i].l , r = intervals[i].r , id = intervals[i].id , e = intervals[i].e;
        if(ID)cout << l << " " << r << endl;
        add[mp[l]].push_back(id);
        if(e)del[mp[r]].push_back(id);
    }
    int min_val = N + 1;
    int bpos = 0;
    set<int> instack;
    for(int i = 1; i <= tot; ++i){
        for(int j : add[i]){
            //cout << "at pos = " << imp[i] << " add " << j << endl;
            instack.insert(j);
        }
        for(int j : del[i]){
            //cout << "at pos = " << imp[i] << " del " << j << endl;
            instack.erase(instack.find(j));
        }
        if(min_val > instack.size()){
            //cout << "pos = " << imp[i] << endl;
            min_val = instack.size();
            bpos = i;
        }
    }
    bpos = imp[bpos];
    printf("%d %d\n" , min_val , bpos);
    instack.clear();
    for(int i = 0; i < intervals.size(); ++i){
        int l = intervals[i].l , r = intervals[i].r , id = intervals[i].id , e = intervals[i].e;
        if(e){
            if(bpos >= l && bpos < r){
                instack.insert(id);
            }
        }
        else{
            if(bpos >= l && bpos <= r){
                instack.insert(id);
            }
        }
    }
    for(int i : instack)printf("%d " , i);
    printf("\n");
}