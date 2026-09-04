#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr int N = 14;
ll a[N];
ll digit;//当前需要统计的数字
// f[pos][cnt][0/1]：当最高位已经填了（没有前导0时）在[pos + 1, len]中digit填了cnt个，[1, pos]任意填，digit出现的次数
// 第三维0表示digit=0,第三维为1表示digit!=1
// 当limit=false时，容易知道填1-9的数量是相同的
ll f[N][N][2];

ll dfs(int pos, bool limit, bool lead0, int cnt)
{
    if (!pos) // 递归边界
        return cnt;
    auto now = f[pos][cnt][digit != 0];
    if (!limit && !lead0 && now!=-1) // 没限制并且dp值已搜索过
        return now;
    ll up = limit ? a[pos] : 9;
    ll res = 0;
    for(int i = 0; i <= up; i ++)
    {
        //填0的时候需注意是否为前导
        //前导零不算入0的个数
        int tmp = cnt + (i == digit);
        if(lead0 && digit == 0 && i == 0)
            tmp = 0;
        res += dfs(pos - 1, limit && i == up, lead0 && i == 0, tmp);
    }
    if (!limit && !lead0) //无限制并且没有前导0
        f[pos][cnt][digit!=0] = res;
    return res;
}

ll ans[10];
void solve(ll x, int f){
    int len = 0;
    while (x > 0)
    {
        a[++len] = x % 10;
        x /= 10;
    }
    for(int i = 0; i <= 9; i ++)
    {
        digit = i;
        ans[i] += f * dfs(len, true, true, 0);
    }
}

int main()
{
    memset(f, -1, sizeof f);
    ll l, r;
    cin >> l >> r;
    for(ll i=1;i<=N;i++)
        for(ll j=1;j<=N;j++)
            f[i][j][0]=f[i][j][1]=-1;
    solve(r, 1); //加上[1, r]
    solve(l - 1, -1); //扣除掉[1, l-1]
    for(int i = 0; i <= 9; i ++)
        cout << ans[i] << ' ';
}