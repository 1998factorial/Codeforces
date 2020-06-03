/*
    Constructive , Greedy
    N = 2 , 1 2 1
    N = 3 , 1 2 1 3 2 3 1
    N = 4 , 1 2 1 3 1 4 2 3 2 4 3 4 1

    Observe for N = 4 , 1 2 1 3 1 4 , 1 as starting point , length 3 * 2
    2 3 2 4 , 2 as starting point , length 2 * 2
    3 4 , 3 as starting point , length 2 * 1
    [] , 4 as starting point , length 2 * 0
    -> when i as starting point , its length will be 2 * (N - i)
    1 at the end. This pattern turns out to be optimal

    The remaining problem is to construct it.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        ll N , l , r; scanf("%lld %lld %lld" , &N , &l , &r);
        ll start = 1; // starting vertex
        ll length = 2 * (N - 1); // length of current section
        ll index = 1; // index of the starting points in the pattern
        while(index + length < l){
            // as long as the index of starting point in pattern does not excceed l
            ++start;
            index += length;
            length -= 2;
        }
        for(ll i = l; i <= r; ++i){
            ll inner_index = i - index + 1; // index within the sub pattern
            if(inner_index == length + 1){ // if we go over bound
                ++start;
                index += length;
                length -= 2;
                inner_index = 1;
                // just start at another pattern
            }
            if(i == N * (N - 1) + 1){
                printf("1");
            }
            else if(inner_index % 2 == 1){
                printf("%lld " , start);
            }
            else{
                printf("%lld " , start + inner_index / 2);
            }
        }
        printf("\n");
    }
}
