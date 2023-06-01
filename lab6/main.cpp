#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100; // Максимальное количество вершин в графе

// Структура для ребра графа
struct Edge {
    int from, to, weight;
};

// Структура для набора подмножеств
struct Subset {
    int parent, rank;
};

// Функция сравнения ребер графа по весу
bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

// Функция поиска подмножества, к которому принадлежит i-ый элемент
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Функция объединения двух подмножеств в одно
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    }
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Функция реализации алгоритма Крускала
void kruskalMST(int graph[][MAXN], int V, vector<Edge>& result) {
    int E = 0;
    vector<Edge> edges;

    // Заполняем вектор edges ребрами графа
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                Edge e = { i, j, graph[i][j] };
                edges.push_back(e);
            }
        }
    }

    // Сортируем все ребра графа по весу
    sort(edges.begin(), edges.end(), compareEdges);

    // Создаем набор подмножеств для каждой вершины графа
    Subset* subsets = new Subset[V];
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // Проходим по всем ребрам, начиная от ребер с минимальным весом
    for (int i = 0; i < edges.size(); i++) {
        // Находим подмножества вершин, к которым принадлежат ребра
        int x = find(subsets, edges[i].from);
        int y = find(subsets, edges[i].to);

        // Если подмножества различны, то объединяем их в одно
        if (x != y) {
            result.push_back(edges[i]);
            Union(subsets, x, y);
            E++;
        }

        // Если мы уже добавили V-1 ребер, то заканчиваем алгоритм
        if (E == V - 1) {
            break;
        }
    }

    delete[] subsets;
}

// Функция записи результата в файл
void writeToFile(vector<Edge>& result) {
    ofstream out("result.txt");
    int totalWeight = 0;
    for (int i = 0; i < result.size(); i++) {
        out << "Edge " << i + 1 << ": " << result[i].from << " - " << result[i].to
            << " with weight " << result[i].weight << endl;
        totalWeight += result[i].weight;
    }
    out << "Total weight of MST is " << totalWeight << endl;
    out.close();
}

int main() {
    int graph[MAXN][MAXN]; // Матрица смежности графа
    int V; // Количество вершин

    // Считываем данные из файла
    ifstream in("graph.txt");
    in >> V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            in >> graph[i][j];
        }
    }
    in.close();

    vector<Edge> result; // Результат работы алгоритма
    kruskalMST(graph, V, result); // Запускаем алгоритм Крускала

    writeToFile(result); // Записываем результат в файл

    return 0;
}