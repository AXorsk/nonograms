#include <bits/stdc++.h>
using namespace std;
int main() {
	system("ls | grep -e 'code*' > tasks.txt");
	freopen("tasks.txt", "r", stdin);
	string S;
	while (cin >> S) {
		string T = "cat " + S + " > ../code.txt";
		system(T.c_str());
		system("./run_test.sh");
		T = "echo " + S;
		system(T.c_str());
	}
	fclose(stdin);
	return 0;
}