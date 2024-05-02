#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("code_804170.txt", "r", stdin);
    string s; cin >> s;
    int n, t = 0;
    fclose(stdin);
    freopen("input.txt", "w", stdout);
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '_') {
            if (s[i + 1] == '_') {
                puts(" 0"); ++t;
                i += 2; n = t;
            } else putchar(' ');
        } else if (s[i] == '-') {
            puts(" 0"); ++t;
        } else putchar(s[i]);
    }
    puts(" 0");
    fclose(stdout);
    freopen("num.txt", "w", stdout);
    printf("%d\n", n);
    fclose(stdout);
    return 0;
}