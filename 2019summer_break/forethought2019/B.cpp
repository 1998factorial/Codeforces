#include <iostream>
#include <cstdio>
#include <string>
#include <sstream> 
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;
//切入点：找到一个可以将t分成s和s'的点，然后核实
int main(){
    string a;
    cin>>a;
    int n=a.size(),cnt=0,pos=-1;
    for(int i=0;i<n;i++){
        if(a[i]=='a')cnt++;
        if(2*(i+1)-cnt==n){ //can split to 2 parts where L has all 'a'
            pos=i;
            break;
        }
    }
    if(pos==-1)cout<<":(\n";
    else{
        int i=pos+1,j=0;
        for(;i<n;i++){
            if(a[i]=='a'){
                cout<<":(\n";
                return 0;
            }
            while(j<=pos&&a[j]=='a')++j;
            if(a[i]!=a[j]){
                cout<<":(\n";
                return 0;
            }
            ++j;
        }
        cout<<a.substr(0,pos+1)<<endl;
    }
    return 0;
}