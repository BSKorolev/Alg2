#include <iostream>
#include <fstream>
using namespace std;

const int MAXN = 100; // максимальное количество вершин в графе

int n; // количество вершин в графе
int graph[MAXN][MAXN]; // матрица смежности
int parent[MAXN]; // массив родительских вершин
int key[MAXN]; // массив ключей
bool visited[MAXN]; // массив, хранящий информацию о посещении вершины

// Функция, находящая вершину с минимальным ключом
int minKey() {
    int m = INT_MAX, index;

    for (int i = 0; i < n; i++)
        if (!visited[i] && key[i] < m)
            m = key[i], index = i;

    return index;
}

// Функция, реализующая алгоритм Прима
void prim() {
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        visited[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {
        int u = minKey();
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
}

int main() {
    ifstream fin("graph.txt");
    ofstream fout("result.txt");

    // считываем матрицу смежности из файла
    fin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> graph[i][j];

    prim(); // решаем задачу алгоритмом Прима

    // выводим результат в файл
    for (int i = 1; i < n; i++)
        fout << parent[i] << " - " << i << " " << graph[i][parent[i]] << endl;

    fin.close();
    fout.close();
    return 0;
}