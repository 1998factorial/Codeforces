#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int , int> ii;
const int maxn = 2e5 + 10;
int N;
set<ii> intervals;

// amortized to at most N deletion

void add(int l , int r){
    if(intervals.empty()){
        intervals.insert({l , r});
    }
    else{
        auto it = intervals.lower_bound({l , l}); // find max l boarder <= l
        if(it != intervals.begin()){ // could be a component to the left of such boarder that intersect with (l , r)
            --it;
            if(it->y >= l){
                l = min(l , it->x); 
                r = max(r , it->y);
                intervals.erase(it);
            }
        }
        it = intervals.lower_bound({l , l});
        for(; it != intervals.end() && it->x <= r;){
            auto itt = it;
            ++it;
            r = max(r , itt->y);
            intervals.erase(itt);
        }
        intervals.insert({l , r});
    }
}

int main(){
    int N;
    scanf("%d" , &N);
    while(N--){
        int l , r;
        scanf("%d %d" , &l , &r);
        add(l , r);
        printf("%d " , (int)intervals.size());
    }
    printf("\n");
}