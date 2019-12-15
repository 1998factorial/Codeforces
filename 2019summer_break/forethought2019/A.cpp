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
string a;
//简单题
int main(){
	cin>>a;
	int cnt=0,n=a.size();
	for(int i=0;i<n;i++)
		cnt+=(a[i]=='a');
	if(cnt>n/2){
		cout<<n<<endl;
	}
	else{
		cout<<2*cnt-1<<endl;
	}
	return 0;
}