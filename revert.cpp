#include <bits/stdc++.h>
using namespace std;
int main() {
	freopen("./data/num.txt", "r", stdin);
	int n; scanf("%d", &n);
    fclose(stdin);
	freopen("./data/input.txt", "r", stdin);
    freopen("./data/code.txt", "w", stdout);
	for (int i = 1; i <= n; ++i) {
		int x; scanf("%d", &x);
		while (x) {
            printf("%d", x);
			scanf("%d", &x);
            if (x) putchar('_');
		}
        if (i < n) putchar('-');
	}
    printf("___");
	for (int i = 1; i <= n; ++i) {
		int x; scanf("%d", &x);
		while (x) {
            printf("%d", x);
			scanf("%d", &x);
            if (x) putchar('_');
		}
        if (i < n) putchar('-');
	}
	fclose(stdin);
    fclose(stdout);
    return 0;
}