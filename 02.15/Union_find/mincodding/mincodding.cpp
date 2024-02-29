#include <iostream>
using namespace std;

int arr[100000];
int flag = 0;
int group_cnt = 0;
int visited[100000] = { 0, };
int T, N;
int car_cnt = 0;
void init() {
	for (int i = 0; i <= T; i++) {
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
	
	arr[t2] = t1;
}
int main() {
	cin >> T >> N;
	init();
	visited[0] = -1;

	for (int i = 0; i < N; i++) {
		int car;
		cin >> car;

		int emptyPlace = find(car);

		if (visited[emptyPlace] == 0) {
			visited[emptyPlace] = 1;
			car_cnt++;
		}
		else if (visited[emptyPlace] == -1) {
			break;
		}

		setUnion(find(emptyPlace - 1), emptyPlace);
	}

	cout << car_cnt;

	return 0;
}