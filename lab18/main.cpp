#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    vector<int> arr = { 5, 1, 3, 7, 9, 2 }; // исходный массив
    sort(arr.begin(), arr.end()); // сортировка массива
    int sum = arr[0]; // начальная сумма
    vector<int> subset = { arr[0] }; // начальное подмножество
    for (int i = 1; i < arr.size(); i++) {
        if (sum + arr[i] >= arr[i]) { // проверка условия на включение элемента в подмножество
            sum += arr[i];
            subset.push_back(arr[i]);
        }
    }
    cout << "Сумма наибольшего подмножества: " << sum << endl;
    for (int i = 0; i < subset.size(); i++) {
        cout << subset[i] << " "; // вывод элементов подмножества
    }
    cout << endl;

    return 0;
}