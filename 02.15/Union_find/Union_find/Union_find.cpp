#include <iostream>

using namespace std;
int N, Q;
int arr[1001];


void init() {
	for (int i = 0; i < 1001; i++) {
		arr[i] = i;
	}
}
int find(int tar) {
	if (tar == arr[tar]) return tar;
	int ret = find(arr[tar]);

	arr[tar] = ret;
	return ret;
}
void setUnion(int a, int b) {
	int t1 = find(a);
	int t2 = find(b);
	if (t1 == t2) {
		return;
	}
	else {
		arr[t2] = t1;
	}
}
int main() {

	cin >> N >> Q;

	init();

	int K, A, B;
	for (int i = 0; i < Q; i++) {
		cin >> K >> A >> B;

		if (K == 1) {
			setUnion(A, B);
		}
		else {
			if (arr[A] == find(B))
				cout << "YES" << "\n";
			else
				cout << "NO" << "\n";
		}
	}
}