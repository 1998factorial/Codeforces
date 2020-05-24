/*
    Dynamic programming , Greedy , Backtracking

    DP[i][j][chosen set] = minimal value of the largest element if we make the original array
    into a strictly increasing sequence of length i using the elements in chosen set
    where the right most element in the sequence is on position j on the original array

    transit:
    DP[i][j][chosen] -> DP[i + 1][nj][chosen | choose] where
    sum[choose] > DP[i][j][chosen] and choose must have at least one element to the right of j

    Greedy optimize: we do not need to enumerate the possible nj given j, we can just let nj
    be j + 1 + #(trailing zero of choose right shifted j) , in other word, we want nj to be as
    close as possible to j

    Backtrack:
    1. store backtracking array
    2. when printing out, don't forget to check number previous elements that are removed
*/

#include <bits/stdc++.h>
#define INF 1000000000
using namespace std;
typedef pair<int , int> ii;

int DP[16][16][1 << 15];
ii track[16][16][1 << 15];
int sum[1 << 15];
int a[15];
int N;

void show(int state){
    for(int i = 0; i < N; ++i){
        if((1 << i) & state)cout << 1;
        else cout << 0;
    }
    cout << endl;
}

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        for(int i = 0; i < N; ++i)scanf("%d" , &a[i]);
        for(int s = 0; s < (1 << N); ++s){
            sum[s] = 0;
            for(int i = 0; i < N; ++i){
                if((1 << i) & s){
                    sum[s] += a[i];
                }
            }
        }
        for(int i = 0; i <= N; ++i){
            for(int j = 0; j <= N; ++j){
                for(int s = 0; s < (1 << N); ++s){
                    DP[i][j][s] = INF;
                    track[i][j][s] = make_pair(-1 , -1);
                }
            }
        }
        DP[0][0][0] = 0;
        for(int cnt = 0; cnt < N; ++cnt){ // cnt
            for(int pos = 0; pos < N; ++pos){ // pos
                for(int chosen = 0; chosen < (1 << N); ++chosen){ // set of elements chosen
                    if(DP[cnt][pos][chosen] < INF){
                        int not_chosen = chosen ^ ((1 << N) - 1);
                        for(int choose = not_chosen; choose; choose = (choose - 1) & not_chosen){
                            if(sum[choose] <= DP[cnt][pos][chosen])continue;
                            if((choose >> pos) == 0)continue;
                            int npos = pos + 1 + __builtin_ctz(choose >> pos); // next right most = # trailing zero + 1 + current right most
                            if(DP[cnt + 1][npos][chosen | choose] > sum[choose]){
                                DP[cnt + 1][npos][chosen | choose] = sum[choose];
                                track[cnt + 1][npos][chosen | choose] = make_pair(pos , chosen);
                            }
                        }
                    }
                }
            }
        }
        int bcnt = -1 , bpos = -1 , bmask = (1 << N) - 1;
        for(int cnt = 0; cnt <= N; ++cnt){
            for(int pos = 0; pos <= N; ++pos){
                if(DP[cnt][pos][(1 << N) - 1] < INF){
                    bcnt = cnt;
                    bpos = pos;
                }
            }
        }
        vector<ii> ret;
        for(; bcnt >= 1; --bcnt){
            int npos = track[bcnt][bpos][bmask].first;
            int nmask = track[bcnt][bpos][bmask].second;
            for(int i = 0; i < N; ++i){
                if((bmask ^ nmask) & (1 << i)){
                    if(i != bpos - 1){
                        ret.emplace_back(i , bpos - 1);
                    }
                }
            }
            bpos = npos;
            bmask = nmask;
        }
        printf("%d\n" , (int)ret.size());
        for(int i = 0; i < (int)ret.size(); ++i){
            int x = ret[i].first;
            int y = ret[i].second;
            for(int j = 0; j < i; ++j){
                if(ret[j].first < ret[i].first)--x; // gone
                if(ret[j].first < ret[i].second)--y; // gone
            }
            printf("%d %d\n" , x + 1 , y + 1);
        }
    }
}
