#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    vector<int> arr = { 5, 1, 3, 7, 9, 2 }; // �������� ������
    sort(arr.begin(), arr.end()); // ���������� �������
    int sum = arr[0]; // ��������� �����
    vector<int> subset = { arr[0] }; // ��������� ������������
    for (int i = 1; i < arr.size(); i++) {
        if (sum + arr[i] >= arr[i]) { // �������� ������� �� ��������� �������� � ������������
            sum += arr[i];
            subset.push_back(arr[i]);
        }
    }
    cout << "����� ����������� ������������: " << sum << endl;
    for (int i = 0; i < subset.size(); i++) {
        cout << subset[i] << " "; // ����� ��������� ������������
    }
    cout << endl;

    return 0;
}