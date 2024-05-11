#include <bits/stdc++.h>
using namespace std;
using pii = pair <int, int>;
const int MAXN = 1e3 + 6;
const double DDL = 0.1; // dividing line of chosing 0 or 1
struct tPos { int x, y, c; };
int n, cnt, nt; int T, W;
double w[MAXN][MAXN]; bool t[MAXN], flag, wrg;
int a[MAXN][MAXN], pos[MAXN], d[MAXN], wt[MAXN];
stack <pii> stk[MAXN];
vector <int> row[MAXN], col[MAXN];
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
void row_dfs(int p, int k, int r) {
	if (k > row[r].size()) {
		for (int i = p + 1; i <= n; ++i)
			if (a[r][i] == 1) return;
		fill(t + 1, t + n + 1, 0);
		wrg = 0; ++nt;
		for (int i = 1; i <= row[r].size(); ++i) {
			for (int j = 1; j <= row[r][i - 1]; ++j)
				t[pos[i] + j - 1] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			if (t[i]) ++wt[i];
			if (d[i] == 2) d[i] = t[i];
			else if (d[i] != t[i]) d[i] = -1;
		}
		return;
	}
	for (int i = p + 1; i + row[r][k - 1] - 1 <= n; ++i) {
		bool ok = true;
		if (a[r][i - 1] == 1) break;
		for (int j = i; j <= i + row[r][k - 1] - 1; ++j)
			if (!a[r][j]) { ok = false; break; }
		if (a[r][i + row[r][k - 1]] == 1) ok = false;
		if (!ok) continue;
		pos[k] = i;
		row_dfs(i + row[r][k - 1], k + 1, r);
	}
}
void col_dfs(int p, int k, int c) {
	if (k > col[c].size()) {
		for (int i = p + 1; i <= n; ++i)
			if (a[i][c] == 1) return;
		fill(t + 1, t + n + 1, 0);
		wrg = 0; ++nt;
		for (int i = 1; i <= col[c].size(); ++i) {
			for (int j = 1; j <= col[c][i - 1]; ++j)
				t[pos[i] + j - 1] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			if (t[i]) ++wt[i];
			if (d[i] == 2) d[i] = t[i];
			else if (d[i] != t[i]) d[i] = -1;
		}
		return;
	}
	for (int i = p + 1; i + col[c][k - 1] - 1 <= n; ++i) {
		bool ok = true;
		if (a[i - 1][c] == 1) break;
		for (int j = i; j <= i + col[c][k - 1] - 1; ++j)
			if (!a[j][c]) { ok = false; break; }
		if (a[i + col[c][k - 1]][c] == 1) ok = false;
		if (!ok) continue;
		pos[k] = i;
		col_dfs(i + col[c][k - 1], k + 1, c);
	}
}
bool calc(int tm, tPos bp = {0, 0, 0}) {
	queue <int> q; // +: row; -: col
	if (tm) {
		q.emplace(bp.x);
		q.emplace(-bp.y);
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
			row_dfs(0, 1, u);
			for (int i = 1; i <= n; ++i)
				if (!~a[u][i] && ~d[i]) {
					a[u][i] = d[i]; --cnt;
					stk[tm].push({u, i});
					q.emplace(u);
					q.emplace(-i);
				}
		} else {
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
tPos analyze() {
	for (int i = 1; i <= n; ++i) {
		fill(wt + 1, wt + n + 1, 0); nt = 0;
		row_dfs(0, 1, i);
		for (int j = 1; j <= n; ++j)
			w[i][j] = wt[j] * 1.0 / nt;
	}
	for (int j = 1; j <= n; ++j) {
		fill(wt + 1, wt + n + 1, 0); nt = 0;
		col_dfs(0, 1, j);
		for (int i = 1; i <= n; ++i)
			w[i][j] *= wt[i] * 1.0 / nt;
	}
	double mx = 0; tPos ret;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (!~a[i][j] && abs(w[i][j] - DDL) > mx) {
				mx = abs(w[i][j] - DDL);
				ret = {i, j, w[i][j] >= DDL};
			}
	return ret;
}
void clean(int tm) {
	cnt += stk[tm].size(); ++W;
	while (!stk[tm].empty()) {
		int nx = stk[tm].top().first;
		int ny = stk[tm].top().second;
		stk[tm].pop();
		a[nx][ny] = -1;
	}
}
bool solve(int tm) {
	if (!cnt) return true;
	tPos bp = analyze();
	a[bp.x][bp.y] = bp.c; --cnt; ++T;
	stk[tm].push({bp.x, bp.y});
	bool pd = calc(tm, bp) && solve(tm + 1);
	if (!pd) {
		clean(tm);
		a[bp.x][bp.y] = !bp.c; --cnt; ++T;
		stk[tm].push({bp.x, bp.y});
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
	if (T) printf("%d / %d\t", T - W, T);
	output();
	return 0;
}