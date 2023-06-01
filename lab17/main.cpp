#include <iostream>
#include <cmath>
using namespace std;

// ������� ������� ������������ ���������� ������
int calcMinBoxes(int n, int capacity) {
    return ceil(n * 1.0 / capacity); // ��������� �� ���������� ������ ����� (�����)
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n = 10; // ���������� ��������
    int weight = 1.5; // ��� ������� ������� � ��
    int capacity = 5; // ����������� ����� � ��
    int boxes = calcMinBoxes(n, capacity); // ������ ������������ ���������� ������
    cout << "����������� ���������� ������: " << boxes << endl;

    // ������������� �������� �� ������
    int objCount = 0; // ������� ��������
    for (int i = 0; i < boxes; i++) {
        int objInBox = min(n - objCount, capacity / weight); // ���������� �������� � �����
        objCount += objInBox; // ��������� ������� ��������
        cout << "���� " << i + 1 << ": " << objInBox << " ��������" << endl;
    }

    return 0;
}