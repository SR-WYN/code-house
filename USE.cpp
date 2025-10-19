#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> PII;
constexpr int mod = 1e9 + 7;
constexpr int N = 2e5 + 10;
int n, m;
void show(int num[], int len)
{
	for (int i = 1; i <= len; i++)
	{
		cout << num[i] << ' ';
	}
	cout << '\n';
}
int base[N];
vector<int> p;
bitset<N> prim;
void get_prim()
{
	prim[1] = true;
	for (int i = 2; i < N; i++)
	{
		if (!prim[i])
		{
			p.push_back(i);
			base[i] = i;
		}
		for (auto j : p)
		{
			if (j * i >= N)
			{
				break;
			}
			prim[j * i] = true;
			base[j * i] = j;
			if (i % j == 0)
			{
				break;
			}
		}
	}
}
int qpow(int a, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1)
		{
			ans = ans * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
int num[N];
int dp[N];
int get_small(int l, int r, int k)
{
	int ans = 0x3f3f3f3f;
	r += k;
	while (l != r)
	{
		if (dp[l-k] >= 0)
		{
			dp[l] = num[l];
		}
		else
		{
			dp[l] = num[l] + dp[l-k];
		}
		ans = min(ans, dp[l]);
		l += k;
	}
	return ans;
}
int get_big(int l, int r, int k)
{
	int ans = -0x3f3f3f3f;
	r += k;
	while (l != r)
	{
		if (dp[l-k] <= 0)
		{
			dp[l] = num[l];
		}
		else
		{
			dp[l] = dp[l-k]+num[l];
		}
		ans = max(ans, dp[l]);
		l += k;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	cin >> t;
	while (t--)
	{
		cin >> n;
		int id = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> num[i];
			if (num[i] != 1 && num[i] != -1)
			{
				id = i;
			}
		}
		if (!id)
		{
			int small = get_small(1, n, 1);
			int big = get_big(1, n, 1);
			//cout<<small<<' '<<big<<'\n';
			set<int>s;
			while (small<=big)
			{
				s.insert(small);
				s.insert(big);
				small++;
				big--;
			}
			s.insert(0);
			cout << s.size() << '\n';
			for (auto i : s)
			{
				cout << i << ' ';
			}
			cout << '\n';
		}
		else
		{
			int sl = get_small(id - 1, 1, -1);
			int bl = get_big(id - 1, 1, -1);
			int sr = get_small(id + 1, n, 1);
			int br = get_big(id + 1, n, 1);
			//cout<<sl<<' '<<bl<<' '<<sr<<' '<<br<<'\n';
			set<int> s;
			s.insert(num[id]);
			s.insert(0);
			while (sl <= bl)
			{
				s.insert(sl);
				sl++;
			}
			while (sr <= br)
			{
				s.insert(sr);
				sr++;
			}
			dp[id]=0;
			sl = 0x3f3f3f3f, bl = -0x3f3f3f3f;
			for (int i = id - 1; i >= 1; i--)
			{
				dp[i] = num[i] + dp[i + 1];
				sl = min(sl, dp[i]);
				bl = max(bl, dp[i]);
			}
			sr = 0x3f3f3f3f, br = -0x3f3f3f3f;
			for (int i = id + 1; i <= n; i++)
			{
				dp[i] = num[i] + dp[i - 1];
				sr = min(sr, dp[i]);
				br = max(br, dp[i]);
			}
			int small = sl + sr + num[id];
			int big = bl + br + num[id];
			while (sl<=bl)
			{
				s.insert(sl+num[id]);
				sl++;
			}
			while (sr<=br)
			{
				s.insert(sr+num[id]);
				sr++;
			}
			while (small <= big)
			{
				s.insert(small);
				s.insert(big);
				small++;
				big--;
			}
			cout << s.size() << '\n';
			for (auto i : s)
			{
				cout << i << ' ';
			}
			cout << '\n';
		}
		for (int i = 1; i <= n; i++)
		{
			dp[i] = 0;
		}
	}
}
