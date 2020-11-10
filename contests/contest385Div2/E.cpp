#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
const int INF = 1e9 + 10;
int N;
struct card{
    int c , r , b; // R->1 , B->0
    card(){}
    card(int c_ , int r_ , int b_) : c(c_) , r(r_) , b(b_) {}
} cards[17];
vector<map<array<int , 2> , int>> DP;

template<class T>
void min(T& a , const T& b){
    if(a > b)a = b;
}

template<class T>
void max(T& a , const T& b){
    if(a < b)a = b;
}

int solve(int mask , int R , int B){
    if(mask == (1 << N) - 1){
        return 0;
    }
    if(DP[mask].count({R , B})){
        return DP[mask][{R , B}];
    }
    int ret = INF;
    int nred = 0 , nblue = 0;
    for(int i = 0; i < N; ++i){
        if(mask & (1 << i)){
            nred += cards[i].c;
            nblue += 1 - cards[i].c;
        }
    }
    for(int i = 0; i < N; ++i){
        if(mask & (1 << i))continue;
        int nmask = mask | (1 << i);
        int rc = 0 , bc = 0;
        max(rc , cards[i].r - nred);
        max(bc , cards[i].b - nblue);
        if(R >= rc && B >= bc){ // just buy
            min(ret , 1 + solve(nmask , R - rc , B - bc));
        }
        if(R >= rc && B < bc){
            min(ret , 1 + bc - B + solve(nmask , R - rc + bc - B , 0));
        }
        if(R < rc && B >= bc){
            min(ret , 1 + rc - R + solve(nmask , 0 , B - bc + rc - R));
        }
        if(R < rc && B < bc){
            int st = rc - R > bc - B ? rc - R : bc - B;
            min(ret , 1 + st + solve(nmask , R + st - rc , B + st - bc));
        }
    }
    return DP[mask][{R , B}] = ret;
}


int main(){
    cin >> N;
    for(int i = 0; i < N; ++i){
        char t;
        cin >> t;
        cin >> cards[i].r >> cards[i].b;
        cards[i].c = t == 'R';
    }
    DP = vector<map<array<int , 2> , int>> (1 << N);
    int ret = solve(0 , 0 , 0);
    cout << ret << endl;
}