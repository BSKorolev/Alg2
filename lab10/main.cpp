#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Функция для чтения графа из файла (матрицы смежности)
int** readGraphFromFile(string filename, int& n) {
    ifstream file(filename);
    file >> n;
    int** graph = new int* [n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            file >> graph[i][j];
        }
    }
    file.close();
    return graph;
}

// Функция для записи результатов в файл
void printResultToFile(string filename, vector<int>& result) {
    ofstream file(filename);
    for (int i = 0; i < result.size(); i++) {
        file << result[i] << " ";
    }
    file.close();
}

// Рекурсивная функция для поиска эйлерова цикла в графе
void findEulerCycle(int** graph, int n, int v, vector<int>& result) {
    // Для каждой вершины сохраняем ее соседей, которые еще не были посещены.
    vector<int> unvisited;
    for (int i = 0; i < n; i++) {
        if (graph[v][i])
            unvisited.push_back(i);
    }
    while (!unvisited.empty()) {
        int u = unvisited.back(); // Берем любую из непосещенных соседних вершин.
        unvisited.pop_back();
        // Удаляем ребро, чтобы избежать повторного посещения вершины.
        graph[v][u] = 0;
        graph[u][v] = 0;
        findEulerCycle(graph, n, u, result);
    }
    // Добавляем вершину в результат (цепь или цикл)
    result.push_back(v);
}

// Функция для проверки, существует ли эйлеров цикл в графе
bool hasEulerCycle(int** graph, int n) {
    int oddVertices = 0;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) degree++;
        }
        if (degree % 2 != 0) oddVertices++;
    }
    return (oddVertices == 0);
}

// Основная функция для чтения файла и вызова функции поиска эйлерова цикла
int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    int** graph = readGraphFromFile("graph.txt", n);
    if (!hasEulerCycle(graph, n)) {
        cout << "Эйлеров цикл не существует!" << endl;
        return 0;
    }
    // Выбираем любую вершину и начинаем обход графа из нее.
    vector<int> result;
    findEulerCycle(graph, n, 0, result);
    // Реверсируем результат, чтобы получить порядок вершин в эйлеровом цикле.
    reverse(result.begin(), result.end());
    // Выводим результат в файл
    printResultToFile("result.txt", result);
    return 0;
}