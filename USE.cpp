#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> PII;
constexpr int mod = 1e9 + 7;
constexpr int N = 4e5 + 10;
int n, m;
struct node
{
	int a, b;
	bool operator<(const node &x) const
	{
		return b > x.b;
	}
};
node num[N];
int lowbit(int x)
{
	return x & (-x);
}
int tree[N];
int cnt[N];
void add(int x, int v)
{
	for (int pos = x; pos < N; pos += lowbit(pos))
	{
		tree[pos] += v;
	}
}
int query(int x)
{
	int ans = 0;
	for (int pos = x; pos; pos -= lowbit(pos))
	{
		ans += tree[pos];
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	// get_prim();
	int t = 1;
	cin >> t;
	while (t--)
	{
		unordered_map<int, int> mp;
		cin >> n >> m;
		int tot = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> num[i].a;
			cnt[++tot] = num[i].a;
		}
		for (int i = 1; i <= n; i++)
		{
			cin >> num[i].b;
			cnt[++tot] = num[i].b;
		}
		sort(num + 1, num + n + 1);
		sort(cnt + 1, cnt + 1 + tot);
		tot = unique(cnt + 1, cnt + 1 + tot) - cnt - 1;
		for (int i = 1; i <= n; i++)
		{
			mp[num[i].a] = lower_bound(cnt + 1, cnt + 1 + tot, num[i].a) - cnt;
			mp[num[i].b] = lower_bound(cnt + 1, cnt + 1 + tot, num[i].b) - cnt;
			// cout<<mp[num[i].a]<<'\n';
		}
		priority_queue<int> pr;
		int ans = 0;
		for (int i = 1; i <= n; i++)
		{
			while (pr.size() && pr.top() > num[i].b)
			{
				int now = pr.top();
				pr.pop();
				if (query(mp[now] - 1) > m)
				{
					continue;
				}
				ans = max(ans, now * (i - 1));
			}
			add(mp[num[i].a], 1);
			pr.push(num[i].a);
			if (query(mp[num[i].b] - 1) <= m)
			{
				ans = max(ans, num[i].b * i);
			}
		}
		while (pr.size())
		{
			int now = pr.top();
			pr.pop();
			if (query(mp[now] - 1) > m)
			{
				continue;
			}
			ans = max(ans, now * n);
			break;
		}
		cout << ans << '\n';
		for (int i = 1; i <= n; i++)
		{
			add(mp[num[i].a], -1);
		}
	}
}
