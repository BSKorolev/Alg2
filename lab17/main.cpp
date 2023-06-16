/*
Функция distribute_items инициализирует список box_items, который представляет распределение предметов по ящикам с помощью нулей. 
Затем она вызывает функцию distribute_recursive, которая пытается рекурсивно распределить предметы по ящикам. 
Если распределение невозможно, функция возвращает пустой список. 
В противном случае она возвращает список, содержащий распределение предметов по ящикам.
*/
#include <iostream>
#include <vector>

using namespace std;

bool distribute_recursive(int num_items, int num_boxes, int max_items, vector<int>& box_items, int current_box);

vector<int> distribute_items(int num_items, int num_boxes, int max_items) {
    vector<int> box_items(num_boxes, 0);
    if (!distribute_recursive(num_items, num_boxes, max_items, box_items, 0)) {
        return vector<int>();
    }
    return box_items;
}

bool distribute_recursive(int num_items, int num_boxes, int max_items, vector<int>& box_items, int current_box) {
    if (num_items == 0) {
        return true;
    }
    if (current_box >= num_boxes) {
        return false;
    }
    if (box_items[current_box] == max_items) {
        return distribute_recursive(num_items, num_boxes, max_items, box_items, current_box + 1);
    }
    for (int i = min(num_items, max_items - box_items[current_box]); i >= 0; i--) {
        box_items[current_box] += i;
        if (distribute_recursive(num_items - i, num_boxes, max_items, box_items, current_box + 1)) {
            return true;
        }
        box_items[current_box] -= i;
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int num_items = 10;
    int num_boxes = 3;  
    int max_items = 4;
    vector<int> box_items = distribute_items(num_items, num_boxes, max_items);
    if (!box_items.empty()) {
        cout << "Предметы распределены по ящикам: ";
        for (int item : box_items) {
            cout << item << " ";
        }
    }
    else {
        cout << "Распределение невозможно";
    }
    return 0;
}
