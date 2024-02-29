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

    //���ƿ��� �ڵ� ����
    //���⼭ ������ �ٲ������ ����ȭ
    arr[tar] = ret; //�������� ���ο� ���� ���� ������ ���������� �ٲ�. ==> ����ȭ
    //�̸� "��ξ���" ǥ�� --- ���Ͽ����� ���� ������ "��ξ���"

    return ret;
}

void setUnion(int a, int b) {
    int t1 = find(a);
    int t2 = find(b);
    if (t1 == t2) return;
    arr[t2] = t1;
}

int main() {
    init(); //ó���� �ڱ��ڽ��� ���� ������

    setUnion(0, 1);
    setUnion(2, 3);
    setUnion(4, 3);

    //union ���� ���� ��ϱ�?
    cout << zozicCount;
   
}

