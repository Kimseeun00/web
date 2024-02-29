#include <iostream>
using namespace std;

int arr[5];

void init() {
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
}

int find(int tar) {
    if (tar == arr[tar]) return tar;
    int ret = find(arr[tar]);

    //돌아오는 코드 영역
    //여기서 보스를 바꿔버리는 최적화
    arr[tar] = ret; //이제부터 새로운 너의 직속 보스는 최종보스로 바꿔. ==> 최적화
    //이를 "경로압축" 표현 --- 유니온파인 빠른 이유는 "경로압축"

    return ret;
}

void setUnion(int a, int b) {
    int t1 = find(a);
    int t2 = find(b);
    if (t1 == t2) return;
    arr[t2] = t1;
}

int main() {
    init(); //처음에 자기자신이 최종 보스임

    setUnion(0, 1);
    setUnion(2, 3);
    setUnion(4, 3);

    //union 이후 조직 몇갭니까?
    cout << zozicCount;
   
}

