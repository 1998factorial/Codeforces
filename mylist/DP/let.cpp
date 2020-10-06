#include <bits/stdc++.h>
class Solution {
public:
    // always make 0s from largest bit to least bit
    int make_at(int& n , int pos , int f){
        if(f == 1){
        // find the number of steps to make n's pos bit 1
            if(n & (1 << pos))return 0;
            if(pos == 0){
                n |= (1 << pos);
                return 1;
            }
            int ret = 0;
            if(pos == 1){
                ret += make_at(n , pos - 1 , 1);
            }   
            else{
                ret += make_at(n , pos - 1 , 1);
                for(int i = pos - 2; i >= 0; --i)ret += make_at(n , i , 0);
            }
            n |= (1 << pos);
            return 1 + ret;
        }
        else{
        // find the number of steps to make n's pos bit to 0
            if((n & (1 << pos)) == 0)return 0;
            if(pos == 0){
                n ^= (1 << pos);
                return 1;
            }
            int ret = 0;
            if(pos == 1){
                ret += make_at(n , pos - 1 , 1);
            }
            else{
                ret += make_at(n , pos - 1 , 1);
                for(int i = pos - 2; i >= 0; --i)ret += make_at(n , i , 0);
            }
            n ^= (1 << pos);
            return 1 + ret;
        }
    }
    
    int solve(int n){
        //printf("currently at %d\n" , n);
        if(n == 0)return 0; // base
        if(n == 1)return 1;
        int pos = 30;
        for(; pos >= 0; --pos){
            if(n & (1 << pos))break;
        }
        // pos > 0
        if(pos == 1){
            if(n & (1 << (pos - 1))){
                return 1 + solve(n ^ (1 << pos));
            }
            else{
                return 2 + solve(n ^ (1 << pos) | (1 << (pos - 1)));
            }
        }
        int ret = 0;
        ret += make_at(n ,  pos - 1 , 1);
        for(int i = pos - 2; i >= 0; --i){
            ret += make_at(n , i , 0);
        }
        //printf("getting %d\n" , 1 + ret);
        return 1 + ret + solve(n ^ (1 << pos));
    }
    
    int minimumOneBitOperations(int n) {
        int ret = solve(n);
        return ret;
    }
} S;


int main(){
    for(int i = 0; i <= 10; ++i){
        printf("f(%d) = %d\n" , i , S.solve(i));
    }
}