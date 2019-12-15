#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <complex>
//#include <unordered_set>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define RREP(i,a,b) for(int i=a;i>=b;i--)
#define FILL(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
int main(){
	int n,m;
	while(~scanf("%d",&n)){
		for(m=1;2*m-1<n;++m);
		cout<<m<<endl;
		for(int i=1;i<=m&&n;++i,--n)cout<<1<<" "<<i<<endl;
		for(int i=2;i<=m&&n;++i,--n)cout<<i<<" "<<m<<endl;
	}
	return 0;
}