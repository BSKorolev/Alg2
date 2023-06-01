#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// ������� ��� ������ ����� �� ����� (������� ���������)
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

// ������� ��� ������ ����������� � ����
void printResultToFile(string filename, vector<int>& result) {
    ofstream file(filename);
    for (int i = 0; i < result.size(); i++) {
        file << result[i] << " ";
    }
    file.close();
}

// ����������� ������� ��� ������ �������� ����� � �����
void findEulerCycle(int** graph, int n, int v, vector<int>& result) {
    // ��� ������ ������� ��������� �� �������, ������� ��� �� ���� ��������.
    vector<int> unvisited;
    for (int i = 0; i < n; i++) {
        if (graph[v][i])
            unvisited.push_back(i);
    }
    while (!unvisited.empty()) {
        int u = unvisited.back(); // ����� ����� �� ������������ �������� ������.
        unvisited.pop_back();
        // ������� �����, ����� �������� ���������� ��������� �������.
        graph[v][u] = 0;
        graph[u][v] = 0;
        findEulerCycle(graph, n, u, result);
    }
    // ��������� ������� � ��������� (���� ��� ����)
    result.push_back(v);
}

// ������� ��� ��������, ���������� �� ������� ���� � �����
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

// �������� ������� ��� ������ ����� � ������ ������� ������ �������� �����
int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    int** graph = readGraphFromFile("graph.txt", n);
    if (!hasEulerCycle(graph, n)) {
        cout << "������� ���� �� ����������!" << endl;
        return 0;
    }
    // �������� ����� ������� � �������� ����� ����� �� ���.
    vector<int> result;
    findEulerCycle(graph, n, 0, result);
    // ����������� ���������, ����� �������� ������� ������ � ��������� �����.
    reverse(result.begin(), result.end());
    // ������� ��������� � ����
    printResultToFile("result.txt", result);
    return 0;
}