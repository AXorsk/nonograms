#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 6;
bool a[MAXN][MAXN];
mt19937 rnd(time(NULL));
uniform_int_distribution <int> u(0, 1);
int main() {
	int n = 30;
	freopen("./data/num.txt", "w", stdout);
	printf("%d\n", n);
	fclose(stdout);
	freopen("./data/origin.txt", "w", stdout);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			printf("%d ", a[i][j] = u(rnd));
		putchar('\n');
	}
	fclose(stdout);
	freopen("./data/input.txt", "w", stdout);
	for (int j = 1; j <= n; ++j) {
		int tot = 0;
		for (int i = 1; i <= n + 1; ++i) {
			if (a[i][j]) ++tot;
			else if (tot) { printf("%d ", tot); tot = 0; }
		}
		puts("0"); // end with 0 as a sign
	}
	for (int i = 1; i <= n; ++i) {
		int tot = 0;
		for (int j = 1; j <= n + 1; ++j) {
			if (a[i][j]) ++tot;
			else if (tot) { printf("%d ", tot); tot = 0; }
		}
		puts("0");
	}
	fclose(stdout);
	return 0;
}