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
const int maxn=1e5+50;
int a[maxn],n,b[maxn];
int main(){
	scanf("%d",&n);
	int odd=0,even=0;
	REP(i,0,n){
		scanf("%d",&a[i]);
		if(a[i]%2==0)even++;
		else odd++;
	}	
	if(even&&odd)
		sort(a,a+n);
	REP(i,0,n)cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}