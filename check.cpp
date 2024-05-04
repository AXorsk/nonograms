#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 6;
bool a[MAXN][MAXN];
vector <int> row[MAXN], col[MAXN];
int main() {
	freopen("num.txt", "r", stdin);
	int n; scanf("%d", &n);
	fclose(stdin);
	freopen("output.txt", "r", stdin);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]);
	fclose(stdin);
	freopen("input.txt", "r", stdin);
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
	for (int j = 1; j <= n; ++j) {
		int tot = 0, p = 0;
		for (int i = 1; i <= n + 1; ++i) {
			if (a[i][j]) ++tot;
			else if (tot) {
				if (col[j][p] != tot) {
					printf("No!\t");
					return 0;
				}
				tot = 0; ++p;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		int tot = 0, p = 0;
		for (int j = 1; j <= n + 1; ++j) {
			if (a[i][j]) ++tot;
			else if (tot) {
				if (row[i][p] != tot) {
					printf("No!\t");
					return 0;
				}
				tot = 0; ++p;
			}
		}
	}
	printf("Yes!\t");
	return 0;
}