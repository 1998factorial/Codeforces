#include <bits/stdc++.h>
using namespace std;

int a, b;

void convert(int v) {
    std::string binary = std::bitset<10>(v).to_string(); //to binary
    std::cout<<binary<<"\n";
}

int main() {
    
    int i, j, k;
    scanf("%d%d%d", &a, &b, &k);
    for (i = (1 << (a + b)) - 1; i >= 1 << (a + b - 1); --i) {
        for (j = i; j >= 1 << (a + b - 1); --j) {
            if (__builtin_popcount(i) == b && __builtin_popcount(j) == b) {
                if (__builtin_popcount(i - j) == k) {
                    printf("yes\n");
                    convert(i);
                    convert(j);
                    return 0;
                }
            }
        }
    }
    
    printf("no\n");
    return 0;
}