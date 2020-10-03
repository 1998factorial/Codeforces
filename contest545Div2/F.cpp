/*
    https://leetcode.com/problems/linked-list-cycle-ii/
    goal is to move all 10 points to the entry of cycle
    we use a fast and a slow to meet in cycle first
    then move the rest 8 points together as well as both fast and slow together
    until they meet
    this always work, proves can be seen in the link
*/
#include <bits/stdc++.h>
using namespace std;

int len;
char s[15][15];

void read(){
    scanf("%d" , &len);
    for(int i = 1; i <= len; ++i){
        scanf("%s", s[i]);
    }    
}

int move_fast_slow(){
    printf("next 0 1\n");
    fflush(stdout);
    read();
    printf("next 1\n");
    fflush(stdout);
    read();
    if(len == 2)return 0;
    return 1; // move until 0 and 1 meet
}

int move_all(){
    if(len == 1)return 0;
    printf("next 0 1 2 3 4 5 6 7 8 9\n");
    fflush(stdout);
    read();
    if(len == 1)return 0;
    return 1;
}

int main(){
    while(move_fast_slow());
    while(move_all());
    printf("done\n");
    fflush(stdout);
}