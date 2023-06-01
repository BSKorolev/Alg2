#include <iostream>
#include <cmath>
using namespace std;

// Функция расчета минимального количества ящиков
int calcMinBoxes(int n, int capacity) {
    return ceil(n * 1.0 / capacity); // округляем до ближайшего целого числа (вверх)
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n = 10; // количество объектов
    int weight = 1.5; // вес каждого объекта в кг
    int capacity = 5; // вместимость ящика в кг
    int boxes = calcMinBoxes(n, capacity); // расчет минимального количества ящиков
    cout << "Минимальное количество ящиков: " << boxes << endl;

    // Распределение объектов по ящикам
    int objCount = 0; // счетчик объектов
    for (int i = 0; i < boxes; i++) {
        int objInBox = min(n - objCount, capacity / weight); // количество объектов в ящике
        objCount += objInBox; // обновляем счетчик объектов
        cout << "Ящик " << i + 1 << ": " << objInBox << " объектов" << endl;
    }

    return 0;
}