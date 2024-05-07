#include <bits/stdc++.h>
using namespace std;
using pii = pair <int, int>;
const int MAXN = 1e3 + 6;
int a[MAXN][MAXN], w[MAXN][MAXN];
int pos[MAXN], d[MAXN], wt[MAXN];
bool t[MAXN], flag, wrg;
int n, cnt;
stack <pii> stk[MAXN];
vector <int> row[MAXN], col[MAXN];
pair <int, int> lnk[MAXN];
// first: next head of a black block
// second: current tail of the black block
void input() {
	memset(a, -1, sizeof a);
	freopen("./data/num.txt", "r", stdin);
	scanf("%d", &n); fclose(stdin);
	cnt = n * n;
	freopen("./data/input.txt", "r", stdin);
	for (int i = 1; i <= n; ++i) {
		int x; scanf("%d", &x);
		while (x) {
			col[i].emplace_back(x);
			scanf("%d", &x);
		}
	}
	for (int i = 1; i <= n; ++i) {
		int x; scanf("%d", &x);
		while (x) {
			row[i].emplace_back(x);
			scanf("%d", &x);
		}
	}
	fclose(stdin);
}
void row_link(int r) {
	int nxt = 0, end = 0;
	for (int i = n; i; --i) {
		if (a[r][i]) { // not 0
			if (!end) end = i;
		} else end = 0; // can't bear any black
		lnk[i].second = end;
	}
	for (int i = n; i; --i) {
		lnk[i].first = nxt; // here we need both 0 and not 0
		if (!a[r][i - 1]) nxt = i;
	}
}
void col_link(int c) {
	int nxt = 0, end = 0;
	for (int i = n; i; --i) {
		if (a[i][c]) {
			if (!end) end = i;
		} else end = 0;
		lnk[i].second = end;
	}
	for (int i = n; i; --i) {
		lnk[i].first = nxt;
		if (!a[i - 1][c]) nxt = i;
	}
}
void row_dfs(int p, int k, int r) {
	if (k > row[r].size()) {
		for (int i = p + 1; i <= n; ++i)
			if (a[r][i] == 1) return;
		fill(t + 1, t + n + 1, 0); wrg = 0;
		for (int i = 1; i <= row[r].size(); ++i) {
			for (int j = 1; j <= row[r][i - 1]; ++j)
				t[pos[i] + j - 1] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			t[i] ? ++wt[i] : --wt[i];
			if (d[i] == 2) d[i] = t[i];
			else if (d[i] != t[i]) d[i] = -1;
		}
		return;
	}
	for (int i = p + 1; ; ++i) {
		while (i + row[r][k - 1] - 1 > lnk[i].second) {
			if (!lnk[i].first || a[r][i] == 1) return;
			i = lnk[i].first;
		}
		if (a[r][i + row[r][k - 1]] == 1) {
			if (a[r][i] == 1) return;
			continue;
		}
		pos[k] = i;
		row_dfs(i + row[r][k - 1], k + 1, r);
		if (a[r][i] == 1) return;
	}
}
void col_dfs(int p, int k, int c) {
	if (k > col[c].size()) {
		for (int i = p + 1; i <= n; ++i)
			if (a[i][c] == 1) return;
		fill(t + 1, t + n + 1, 0); wrg = 0;
		for (int i = 1; i <= col[c].size(); ++i) {
			for (int j = 1; j <= col[c][i - 1]; ++j)
				t[pos[i] + j - 1] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			t[i] ? ++wt[i] : --wt[i];
			if (d[i] == 2) d[i] = t[i];
			else if (d[i] != t[i]) d[i] = -1;
		}
		return;
	}
	for (int i = p + 1; ; ++i) {
		while (i + col[c][k - 1] - 1 > lnk[i].second) {
			if (!lnk[i].first || a[i][c] == 1) return;
			i = lnk[i].first;
		}
		if (a[i + col[c][k - 1]][c] == 1) {
			if (a[i][c] == 1) return;
			continue;
		}
		pos[k] = i;
		col_dfs(i + col[c][k - 1], k + 1, c);
		if (a[i][c] == 1) return;
	}
}
bool calc(int tm, pii bp = {0, 0}) {
	queue <int> q; // +: row; -: col
	while (!q.empty()) q.pop();
	if (tm) {
		q.emplace(bp.first);
		q.emplace(-bp.second);
	} else {
		for (int i = 1; i <= n; ++i) {
			q.emplace(i);
			q.emplace(-i);
		}
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		fill(d + 1, d + n + 1, 2); wrg = 1;
		if (u > 0) {
			row_link(u);
			row_dfs(0, 1, u);
			for (int i = 1; i <= n; ++i)
				if (!~a[u][i] && ~d[i]) {
					a[u][i] = d[i]; --cnt;
					stk[tm].push({u, i});
					q.emplace(u);
					q.emplace(-i);
				}
		} else {
			col_link(-u);
			col_dfs(0, 1, -u);
			for (int i = 1; i <= n; ++i)
				if (!~a[i][-u] && ~d[i]) {
					a[i][-u] = d[i]; --cnt;
					stk[tm].push({i, -u});
					q.emplace(-u);
					q.emplace(i);
				}
		}
		if (wrg) return false;
	}
	return true;
}
pii analyze() {
	memset(w, 0, sizeof w);
	for (int i = 1; i <= n; ++i) {
		fill(wt + 1, wt + n + 1, 0);
		row_link(i);
		row_dfs(0, 1, i);
		for (int j = 1; j <= n; ++j)
			w[i][j] += wt[j];
	}
	for (int j = 1; j <= n; ++j) {
		fill(wt + 1, wt + n + 1, 0);
		col_link(j);
		col_dfs(0, 1, j);
		for (int i = 1; i <= n; ++i)
			w[i][j] += wt[i];
	}
	// search 1 or 0 ?
	int mx = INT_MIN; pii ret;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (!~a[i][j] && w[i][j] > mx) {
				mx = w[i][j];
				ret = {i, j};
			}
	return ret;
}
void clean(int tm) {
	cnt += stk[tm].size();
	while (!stk[tm].empty()) {
		int nx = stk[tm].top().first;
		int ny = stk[tm].top().second;
		stk[tm].pop();
		a[nx][ny] = -1;
	}
}
bool solve(int tm) {
	if (!cnt) return true;
	pii bp = analyze();
	int bx = bp.first, by = bp.second;
	a[bx][by] = 1; --cnt;
	stk[tm].push({bx, by});
	bool pd = calc(tm, bp) && solve(tm + 1);
	if (!pd) {
		clean(tm);
		a[bx][by] = 0; --cnt;
		stk[tm].push({bx, by});
		pd = calc(tm, bp) && solve(tm + 1);
	}
	if (!pd) return clean(tm), false;
	else return true;
}
void output() {
	freopen("./data/output.txt", "w", stdout);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			printf("%d ", a[i][j]);
		putchar('\n');
	}
	fclose(stdout);
}
int main() {
	input();
	auto st = clock();
	calc(0); solve(1);
	auto et = clock();
	printf("T + %lfs\t", (et - st) * 1.0 / CLOCKS_PER_SEC);
	output();
	return 0;
}