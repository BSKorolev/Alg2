#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

const int MAX = 100;
int graph[MAX][MAX], d[MAX], p[MAX];
bool visited[MAX];
int n, start, last;

void bfs(int s) {
    queue<int> q; // очередь вершин
    q.push(s);
    visited[s] = true; // помечаем вершину посещенной
    d[s] = 0; // расстояние от стартовой вершины до нее самой равно 0
    p[s] = -1; // предшественник для стартовой вершины -1

    while (!q.empty()) {
        int v = q.front(); // извлекаем вершину из очереди
        q.pop();

        // перебираем все непосещенные смежные вершины
        for (int u = 0; u < n; u++) {
            if (graph[v][u] && !visited[u]) {
                visited[u] = true; // помечаем вершину посещенной
                q.push(u); // добавляем в очередь
                d[u] = d[v] + 1; // расстояние до вершины u на 1 больше, чем расстояние до вершины v
                p[u] = v; // запоминаем предшественника
            }
        }
    }
}

void read_graph(string filename) {
    ifstream fin(filename); // открываем файл
    fin >> n >> start >> last; // считываем количество вершин, стартовую и конечную вершины
    start--; // уменьшаем на 1, чтобы номера вершин начинались с 0
    last--;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> graph[i][j]; // считываем матрицу смежности
        }
    }
}

void write_result(string filename) {
    ofstream fout(filename); // создаем файл для записи
    fout << "Shortest paths from vertex " << start << " to all other vertices:" << endl;
    for (int i = 0; i < n; i++) {
        fout << i + 1 << ": ";
        if (visited[i]) {
            fout << d[i] << " | Path: ";
            int j = i;
            while (j != -1) {
                fout << j + 1 << " ";
                j = p[j];
            }
        }
        else {
            fout << "not reachable";
        }
        fout << endl;
    }
}

int main() {
    read_graph("graph.txt"); // читаем граф из файла
    bfs(start); // ищем кратчайшие пути из стартовой вершины
    write_result("result.txt"); // записываем результат в файл
    return 0;
}