#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;

int DP[maxn][105][2]; // 0 -> prefix direction, 1 <- sufix direction
// DP[i][j][0] = can we put the first j clues among the first i cells ?
// DP[i][j][1] = can we put the last j clues among the last i cells ?
int sum[maxn][2][2];
// sum[i][0][0] = # of forced white in first i cells
// sum[i][0][1] = # of forced white in last i cells
int canW[maxn];
int canB[maxn];
int N , K;
char S[maxn];
int C[maxn];

void init(string s , vector<int> c){
    N = s.size();
    K = c.size();
    S[0] = S[N + 1] = 'N'; // dummy value
    for(int i = 0; i < N; ++i){
        S[i + 1] = s[i];
    }
    for(int i = 0; i < K; ++i){
        C[i + 1] = c[i];
    }
    memset(DP , 0 , sizeof(DP));
    memset(sum , 0 , sizeof(sum));
    memset(canW , 0 , sizeof(canW));
    memset(canB , 0 , sizeof(canB));
}

void get_DP(int x){
    for(int i = 1; i <= N; ++i){
        sum[i][0][x] = sum[i - 1][0][x];
        sum[i][1][x] = sum[i - 1][1][x];
        if(S[i] == '_')++sum[i][0][x];
        if(S[i] == 'X')++sum[i][1][x];
        DP[i][0][x] = (sum[i][1][x] == 0); // no forced black
    }
    DP[0][0][x] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= K; ++j){
            if(S[i] == '_'){ // forced white
                // we can not place j-th clue's right end at S[i]
                DP[i][j][x] = DP[i - 1][j][x];
                // so we should ignore the i-th cell and check previous ones
            }
            if(S[i] == 'X'){ // forced black
                // so we should try to place j-th clue's right end on S[i]
                int len = C[j];
                if(i - len >= 0 && sum[i - len][0][x] == sum[i][0][x]){
                    // no forced white on overlapped cells
                    if(S[i - len] != 'X'){ // S[i - len] can not be forced black
                        if(i - len == 0)DP[i][j][x] = DP[i - len][j - 1][x];
                        else DP[i][j][x] = DP[i - len - 1][j - 1][x]; // S[i - len] is reserved for white
                    }
                }
            }
            else{ // not forced
                // try both possibilities
                int len = C[j];
                DP[i][j][x] = DP[i - 1][j][x];
                if(i - len >= 0 && sum[i - len][0][x] == sum[i][0][x]){
                    // no forced white on overlapped cells
                    if(S[i - len] != 'X'){ // S[i - len] can not be forced black
                        if(i - len == 0)DP[i][j][x] |= DP[i - len][j - 1][x];
                        else DP[i][j][x] |= DP[i - len - 1][j - 1][x]; // S[i - len] is reserved for white
                    }
                }
            }
            /*if(DP[i][j][x]){
                if(x == 0){
                    printf("we can place %d clues in first %d cells\n" , j , i);
                }
                else{
                    printf("we can place %d clues in last %d cells\n" , j , i);
                }
            }*/
        }
    }
}

string solve_puzzle(string s, vector<int> c){
    init(s , c);
    // for prefix
    get_DP(0);
    reverse(S + 1 , S + 1 + N);
    reverse(C + 1 , C + 1 + K);
    // for sufix
    get_DP(1);
    reverse(S + 1 , S + 1 + N);
    reverse(C + 1 , C + 1 + K);
    for(int i = 1; i <= N; ++i){
        // use DP to check if i-th cell can be black or white.
        if(S[i] != 'X'){
            // check if there exists a good configuration that S[i] is white
            for(int j = 0; j <= K && canW[i] == 0; ++j){
                if(DP[i - 1][j][0] && DP[N - i][K - j][1]){
                    canW[i] = 1;
                    //printf("we can force %d th cell to be white\n" , i);
                }
            }
        }
        if(S[i] != '_'){
            // check if there exists a configuration that S[i] is black
            for(int j = 1; j <= K; ++j){
                // can we place the right end point of C[j] on S[i] ?
                bool ok = 0;
                int len = C[j];
                if(i - len >= 0 && sum[i - len][0][0] == sum[i][0][0]){ // can place the jth cell here
                    // check if good configuration exists
                    if(S[i - len] != 'X' && S[i + 1] != 'X'){
                        if(i - len == 0 && N - i == 0){
                            ok = DP[i - len][j - 1][0] && DP[N - i][K - j][1];
                        }
                        if(i - len == 0 && N - i > 0){
                            ok = DP[i - len][j - 1][0] && DP[N - i - 1][K - j][1];
                        }
                        if(i - len > 0 && N - i == 0){
                            ok = DP[i - len - 1][j - 1][0] && DP[N - i][K - j][1];
                        }
                        if(i - len > 0 && N - i > 0){
                            ok = DP[i - len - 1][j - 1][0] && DP[N - i - 1][K - j][1];
                        }
                    }
                }
                if(ok){
                    ++canB[i - len + 1];
                    --canB[i + 1];
                    //printf("we can place the %d th clue's right end point on %d th cell\n" , j , i);
                }
            }
        }
    }
    string ret = "";
    for(int i = 1; i <= N; ++i){
        canB[i] += canB[i - 1];
        if(S[i] != '.'){
            ret += S[i];
        }
        else{
            if(canB[i] && canW[i]){
                ret += '?';
            }
            else if(canB[i]){
                ret += 'X';
            }
            else{
                ret += '_';
            }
        }
    }
    return ret;
}


int main(){
    string s;
    cin >> s;
    int sz; cin >> sz;
    vector<int> vec;
    for(int i = 1; i <= sz; ++i){
        int x; cin >> x;
        vec.push_back(x);
    }
    cout << solve_puzzle(s , vec) << endl;
}
