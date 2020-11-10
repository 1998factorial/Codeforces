#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
int K , T , lim[20];
ll DP[20][20] , C[20][20];
vector<char> symbol = {'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , 'a' , 'b' , 'c' , 'd' , 'e' , 'f'};
// DP[i][j] = # interesting number using first i symbols, with length = j

int main(){
    cin >> K >> T;
    int i , j , k , len , pos , x;
    C[0][0] = 1;
    for(i = 1; i <= 16; ++i){
        for(j = 0; j <= i; ++j){
            C[i][j] = (!j) ? 1 : C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    // find the length of our answer 
    for(i = 0; i < 16; ++i)lim[i] = T; // any symbol can appear at most T times
    for(len = 1; len <= 20; ++len){
        memset(DP , 0 , sizeof(DP));
        // for zero, we can not have leading zero
        for(i = 0; i <= min(len - 1 , lim[0]); ++i)DP[0][i] = C[len - 1][i];
        for(i = 1; i < 16; ++i){ // consider the ith symbol
            for(j = 0; j <= len; ++j){ // for length j interesting number
                for(k = 0; k <= min(j , lim[i]); ++k){ // if we put k of symbol[i]
                    // we have len - (j - k) free spot for k symbok[i]s
                    DP[i][j] += DP[i - 1][j - k] * C[len - (j - k)][k]; 
                }
            }
        }
        if(DP[15][len] >= K){ // means our answer has length len
            break;
        }
        K -= DP[15][len]; // means our answer is longer than len
    }
    // now we know the length of our ans, and we need to find it
    // we can start with smallest digit on the most significant position
    for(pos = 1; pos <= len; ++pos){ // consider the pos - th position
        int nlen = len - pos; // we are left with length nlen
        for(x = (pos == 1) ? 1 : 0; x < 16; ++x){ // we put symbol[x] on this spot, be careful of leading zero
            if(lim[x] <= 0)continue; // run out of symbol[x]
            --lim[x];
            memset(DP , 0 , sizeof(DP));
            // handel zero
            for(i = 0; i <= min(nlen , lim[0]); ++i)DP[0][i] = C[nlen][i];
            for(i = 1; i < 16; ++i){ // focus on symbol[i]
                for(j = 0; j <= nlen; ++j){ // for length j interestig number
                    for(k = 0; k <= min(j , lim[i]); ++k){ // if we put k symbol[i]s 
                        DP[i][j] += DP[i - 1][j - k] * C[nlen - (j - k)][k];
                    }
                }
            } 
            if(DP[15][nlen] >= K){ // we know that ans[pos] = symbol[x]
                cout << symbol[x];
                break;
            }
            ++lim[x];
            K -= DP[15][nlen];
        }
    }
}