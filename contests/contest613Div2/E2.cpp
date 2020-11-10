SubmitSubmit
返回主页
~Lanly~
指尖跃动的换行符，是我此生不变的信仰。
首页新随笔联系管理随笔 - 74  文章 - 0  评论 - 31
Codeforces Round #613 (Div. 2)
A. Mezo Playing Zoma (CF 1285 A)
题目大意
机器人初始位置为0，给了一串指令告诉机器人是往左走一格还是右走一格，部分指令可能会丢失，问机器人最终可能的位置的情况数。

解题思路
𝐿,𝑅的个数加一即为答案。
神奇的代码


B. Just Eat It! (CF 1285 B)
题目大意
给定一个数列，问整个区间和以及部分区间和哪个大。

解题思路
区间和最值的用𝑑𝑦𝑛𝑎𝑚𝑖𝑐 𝑝𝑟𝑜𝑔𝑟𝑎𝑚𝑚𝑖𝑛𝑔，特判最值是否在全部区间取的即可。𝑑𝑝[𝑖]表示前𝑖个数，其中第𝑖个数必取的最大值。则𝑑𝑝[𝑖]=max(𝑑𝑝[𝑖−1],𝑎[𝑖])，答案为max1≤𝑖≤𝑛(𝑑𝑝[𝑖])。

对应为代码注释部分。

注意到区间可以理解为是去掉从开头的连续几个数以及从结尾的连续几个数。去掉后如果和会变大或者不变，则说明存在某点的前缀和或后缀和小于等于0，如此两边扫一遍也行。
神奇的代码


C. Fadi and LCM (CF 1285 C)
题目大意
给定𝑥，找出一对𝑎,𝑏使得𝑙𝑐𝑚(𝑎,𝑏)=𝑥且max(𝑎,𝑏)最小。

解题思路
𝑙𝑐𝑚(𝑎,𝑏)=𝑎×𝑏𝑔𝑐𝑑(𝑎,𝑏)=𝑥，令𝑎=𝑘1×𝑔𝑐𝑑(𝑎,𝑏),𝑏=𝑘2×𝑔𝑐𝑑(𝑎,𝑏)，则𝑘1×𝑘2×𝑔𝑐𝑑(𝑎,𝑏)=𝑥，不失一般性，我们设𝑎≤𝑏即𝑘1≤𝑘2，我们要最小化𝑏，即最小化𝑘2×𝑔𝑐𝑑(𝑎,𝑏)，即最大化𝑘1，即找到最大的𝑘1且𝑘1≤𝑘2，由于𝑥≤1012，而𝑘1≤𝑥‾‾√，所以我们从大到小枚举𝑘1判断𝑙𝑐𝑚(𝑎,𝑏)是否等于𝑥即可。我们也可以假设𝑔𝑐𝑑(𝑎,𝑏)=1，这是始终有解且一定是最小的。
神奇的代码

复制
#include <bits/stdc++.h>
#define MIN(a,b) ((((a)<(b)?(a):(b))))
#define MAX(a,b) ((((a)>(b)?(a):(b))))
#define ABS(a) ((((a)>0?(a):-(a))))
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<LL> VL;
typedef pair<LL,LL> PLL;
typedef vector<PLL> VPLL;

template <typename T>
void read(T &x) {
    int s = 0, c = getchar();
    x = 0;
    while (isspace(c)) c = getchar();
    if (c == 45) s = 1, c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if (s) x = -x;
}

template <typename T>
void write(T x, char c = ' ') {
    int b[40], l = 0;
    if (x < 0) putchar(45), x = -x;
    while (x > 0) b[l++] = x % 10, x /= 10;
    if (!l) putchar(48);
    while (l) putchar(b[--l] | 48);
    putchar(c);
}

int main(void) {
    //ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    LL x=0;
    read(x);
    LL qwq=sqrt(x);
    while(qwq){
        if (x%qwq==0) if(__gcd(qwq,x/qwq)==1) break;
        --qwq;
    }
    printf("%lld %lld\n",qwq,x/qwq);
    return 0;
}


D. Dr. Evil Underscores (CF 1285 D)
题目大意
给定𝑛个数𝑎𝑖 (𝑖=1,2,3,...,𝑛)，要求找一个数𝑋，最小化max1≤𝑖≤𝑛(𝑎𝑖⊕𝑋)。输出这个最小值。

解题思路
异或题盲猜trie
然后弄dp然后暴毙
经过分析我们发现，对于在二进制下的某一位，如果全都是1或者0，我们都可以对𝑋在这一位添1或0来变小，但如果某一位既有1又有0，那这一位将不可避免的存在1。那么我们从高位起，判断该位，如果全部是0或1，那么答案在该位就是0，否则将是1，然后分𝑋在该位是0或1两种情况继续搜下去即可。在𝑡𝑟𝑖𝑒树上跑。
神奇的代码

复制
#include <bits/stdc++.h>
#define MIN(a,b) ((((a)<(b)?(a):(b))))
#define MAX(a,b) ((((a)>(b)?(a):(b))))
#define ABS(a) ((((a)>0?(a):-(a))))
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<LL> VL;
typedef pair<LL,LL> PLL;
typedef vector<PLL> VPLL;

template <typename T>
void read(T &x) {
    int s = 0, c = getchar();
    x = 0;
    while (isspace(c)) c = getchar();
    if (c == 45) s = 1, c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if (s) x = -x;
}

template <typename T>
void write(T x, char c = ' ') {
    int b[40], l = 0;
    if (x < 0) putchar(45), x = -x;
    while (x > 0) b[l++] = x % 10, x /= 10;
    if (!l) putchar(48);
    while (l) putchar(b[--l] | 48);
    putchar(c);
}

const int N=4e6+7;

int trie[N][2],n,m=1;

void add(int x){
    int t=1;
    for(int i=29;i>=0;--i){
        if (!trie[t][(x>>i)&1]) trie[t][(x>>i)&1]=++m;
        t=trie[t][(x>>i)&1];
    }
}

int DFS(int t,int len){
    if (len<0) return 0;
    if (!trie[t][0]) return DFS(trie[t][1],len-1);
    if (!trie[t][1]) return DFS(trie[t][0],len-1);
    return (min(DFS(trie[t][0],len-1),DFS(trie[t][1],len-1))|(1<<len));
}

int main(void) {
    //ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    read(n);
    for(int u,i=1;i<=n;++i){
        read(u);
        add(u);
    }
    printf("%d\n",DFS(1,29));
    return 0;
}


E. Delete a Segment (CF 1285 E)
题目大意
给定𝑛条线段，线段之间若有交叉（端点值相同也算交叉）或者重合则可以联合起来成为新的一条（可能）更长的线段，现在要求去掉一条线段（不能不去），使得去掉后联合后的线段最多，问是多少。

解题思路
我们考虑去掉一条线段后能够增加多少个线段。

我们可以发现，如果该线段所覆盖的区间里，存在某个子区间，它只被该线段覆盖的话，去掉该线段后，这里就有一个空隙。而如果有𝑥个空隙出来的话，那就会多出𝑥个线段出来。这启示我们从空隙数量的角度来解决联合线段的个数。

我们考虑如何求只被该线段覆盖的区间的数量。

我们按左端点从小到大排列枚举，对于当前枚举的这条线段𝑖，前𝑖−1条线段的右端点的最大值为𝑟，次大值为𝑟0，则对于其右端点为𝑟的某条线段𝑗来说，它所覆盖的[𝑙𝑗,𝑟𝑗]区间中，(𝑟0,𝑟𝑗]区间（或[𝑙𝑗,𝑟𝑗]，如果𝑙𝑗>𝑟0）并没有被其他线段覆盖，如果第𝑖条线段的左端点𝑙𝑖>𝑟0的话，那么区间(𝑟0,𝑙𝑖)这部分区间就只被线段𝑗覆盖，然后我们更新𝑟及𝑟0重复操作，得到每条线段覆盖的区间内没被其他线段覆盖的区间数𝑐𝑛𝑡𝑖（或者说线段内的空隙），还有本身存在的空隙𝑔𝑎𝑝，最后由植树原理得答案𝑎𝑛𝑠=𝑔𝑎𝑝+max1≤𝑖≤𝑛(𝑐𝑛𝑡𝑖)+1。

要特判全部线段没有交叉的情况，此时最终答案应是𝑎𝑛𝑠=𝑛−1。
神奇的代码

复制
#include <bits/stdc++.h>
#define MIN(a,b) ((((a)<(b)?(a):(b))))
#define MAX(a,b) ((((a)>(b)?(a):(b))))
#define ABS(a) ((((a)>0?(a):-(a))))
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<LL> VL;
typedef pair<LL,LL> PLL;
typedef vector<PLL> VPLL;

template <typename T>
void read(T &x) {
    int s = 0, c = getchar();
    x = 0;
    while (isspace(c)) c = getchar();
    if (c == 45) s = 1, c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if (s) x = -x;
}

template <typename T>
void write(T x, char c = ' ') {
    int b[40], l = 0;
    if (x < 0) putchar(45), x = -x;
    while (x > 0) b[l++] = x % 10, x /= 10;
    if (!l) putchar(48);
    while (l) putchar(b[--l] | 48);
    putchar(c);
}

int main(void) {
    //ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int kase; read(kase);
    for (int i = 1; i <= kase; i++) {
        //printf("Case #%d: ", i);
        int n;
        vector<pair<int,int>> a;
        read(n);
        for(int l,r,i=0;i<n;++i){
            read(l);
            read(r);
            a.push_back(make_pair(l,r));
        }
        sort(a.begin(),a.end(),less<pair<int,int>>());
        int r=a[0].second,ans=0,ma=-2147483644,cnt=0,gap=0;
        for(int i=1;i<n;++i){
            if (a[i].first>r){
                ++gap;
                r=a[i].second;
                ma=-2147483644;
                ans=max(ans,cnt);
                cnt=0;
            }else if (ma==-2147483644){
                ma=min(r,a[i].second);
                r=max(r,a[i].second);
            }else{
                if (a[i].first>ma) ++cnt;
                if (a[i].second>=r){
                    ans=max(ans,cnt);
                    cnt=0;
                }
                ma=max(ma,min(r,a[i].second));
                r=max(r,a[i].second);
            }
        }
        ans=max(ans,cnt);
        ans=ans+gap+1;
        if (gap+1==n) ans=n-1;
        printf("%d\n",ans);
    }
    return 0;
}


F. Classical? (CF 1285 F)
题目大意
给定𝑛个数𝑎𝑖，求max1≤𝑖<𝑗≤𝑛𝑙𝑐𝑚(𝑎𝑖,𝑎𝑗)。

解题思路
𝑙𝑐𝑚(𝑎𝑖,𝑎𝑗)=𝑎𝑖×𝑎𝑗𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)。我们可以枚举𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)，然后所有数都除以𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)，这样我们要寻找的就是两个互质的数𝑎𝑥,𝑎𝑦，它们的乘积最大。我们从大到小遍历这些数，对于当前的数𝑎𝑖，我们想知道大于它的数中是否有与它互质的，即求∑𝑎𝑗>𝑎𝑖[𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)=1]是否大于零。这是个经典式子，由于[𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)=1]=∑𝑑|𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)𝜇(𝑑)，我们对其变形：

∑𝑎𝑗>𝑎𝑖[𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)=1]=∑𝑎𝑗>𝑎𝑖∑𝑑|𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)𝜇(𝑑)

我们改变它的求和顺序，由于𝑑肯定是𝑎𝑖的因子，我们枚举它的每一个因子，这样的因子在求和式中出现次数为𝑐𝑛𝑡𝑑，得

∑𝑎𝑗>𝑎𝑖∑𝑑|𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)𝜇(𝑑)=∑𝑑|𝑎𝑖𝜇(𝑑)∗𝑐𝑛𝑡𝑑

其中𝑐𝑛𝑡𝑑表示大于𝑎𝑖的数中是𝑑的倍数的个数，𝜇(𝑥)是莫比乌斯函数。

这样我们维护一个𝑐𝑛𝑡数组，就能够知道是否有与𝑎𝑖互质的数，拿一个指针往回扫，扫到那个互质的数，然后计算答案𝑎𝑖∗𝑎𝑗∗𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)（因为这里的两个数𝑎𝑖,𝑎𝑗都除以了一次𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)）。注意下次再遇到有互质的时候，指针从上次的位置继续往回找即可，不需要重新回到原来位置往回扫，因为我们是从大到小遍历这些数，小的数与前面的数的乘积不可能大于原先的答案，这里可以用栈处理。

时间复杂度为𝑂(∑𝑖=1𝑛𝜎0(𝑖)2)，其中𝜎0(𝑛)=∑𝑑|𝑛1。

还可以再优化一下，我们把𝑎𝑖×𝑎𝑗𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)视为𝑎𝑖×𝑎𝑗𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)，于是把𝑎𝑗的每个因子都储存下来，这样虽然会增加原本不应有的答案，但这些答案会小于𝑎𝑗对应的答案，对我们要找的最大值无影响。

也就是说我们对于每个𝑎𝑖，把它的因子𝑑𝑖𝑗全部加到数组里，因为拿𝑎𝑖与另一个数求𝐿𝐶𝑀不会小于拿它的某个因子𝑑𝑖与另一个数求𝐿𝐶𝑀，所以这对最终答案没有影响，尽管会增加原本不会出现的答案。然后再从大到小枚举𝑎𝑖，寻找比𝑎𝑖大的且与𝑎𝑖互质的数，这仍是上面的方法，只是省去了枚举𝑔𝑐𝑑(𝑎𝑖,𝑎𝑗)的操作，最终的时间复杂度为(∑𝑖=1𝑛𝜎0(𝑖))
神奇的代码

复制
#include <bits/stdc++.h>
#define MIN(a,b) ((((a)<(b)?(a):(b))))
#define MAX(a,b) ((((a)>(b)?(a):(b))))
#define ABS(a) ((((a)>0?(a):-(a))))
using namespace std;

template <typename T>
void read(T &x) {
    int s = 0, c = getchar();
    x = 0;
    while (isspace(c)) c = getchar();
    if (c == 45) s = 1, c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if (s) x = -x;
}

template <typename T>
void write(T x, char c = ' ') {
    int b[40], l = 0;
    if (x < 0) putchar(45), x = -x;
    while (x > 0) b[l++] = x % 10, x /= 10;
    if (!l) putchar(48);
    while (l) putchar(b[--l] | 48);
    putchar(c);
}

const int N=1e5+8;

bool sign[N];

int n,ma,u[N],cnt[N];

LL ans;

vector<int> d[N];

stack<LL> s;

void pre(){
    for(int i=1;i<=ma;++i){
        for(int j=i;j<=ma;j+=i) d[j].push_back(i);
        if (i==1) u[i]=1;
        else if (i/d[i][1]%d[i][1]==0) u[i]=0;
        else u[i]=-u[i/d[i][1]];
    }
}

int coprime(int x){
    int tmp=0;
    for(int i:d[x])
        tmp+=u[i]*cnt[i];
    return tmp;
}

void updata(int x,int val){
    for(int i:d[x])
        cnt[i]+=val;
}

int main(void) {
    //ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    read(n);
    for(int a,i=1;i<=n;++i){
        read(a);
        sign[a]=true;
        ma=MAX(ma,a);
    }
    pre();
    for(int i=1;i<=ma;++i)
        for(int j=2;i*j<=ma;++j)
            sign[i]|=sign[i*j];
    for(int qwq,i=ma;i>=1;--i){
        if (!sign[i]) continue;
        qwq=coprime(i);
        while(qwq){
            if (__gcd(s.top(),(LL)i)==1){
                ans=max(s.top()*(LL)i,ans);
                --qwq;
            }
            updata(s.top(),-1);
            s.pop();
        }
        updata(i,1);
        s.push((LL)i);
    }
    write(ans,'\n');
    return 0;
}


标签: DP, 构造, 数论, 容斥, 莫比乌斯反演, Trie树
好文要顶 关注我 收藏该文
