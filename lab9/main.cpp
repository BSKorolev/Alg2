#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

// ������� ��� ������ ����� �� �����
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

// ������� ��� ������ ���������� ����� � ����
void printResultToFile(string filename, int* distances, int n) {
    ofstream file(filename);
    for (int i = 0; i < n; i++) {
        file << i << " " << distances[i] << endl;
    }
    file.close();
}

// ������� ��� ���������� ��������� ��������-�����
void bellmanFord(int** graph, int n, int startVertex, string outputFile) {
    int* distances = new int[n];
    // ������������� ������� ����������
    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX;
    }
    distances[startVertex] = 0;

    /* ������ �� ���� �������� (n - 1) ���, ����� ����� ���������� ����
       ������������ ���������� ����� � ����� ����� n-1 */
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (graph[k][j] != 0) {
                    int newDistance = distances[k] + graph[k][j];
                    if (newDistance < distances[j]) {
                        distances[j] = newDistance;
                    }
                }
            }
        }
    }

    // ����� ������� ������������� ������ 
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            if (graph[k][j] != 0) {
                int newDistance = distances[k] + graph[k][j];
                if (newDistance < distances[j]) {
                    cout << "������������� ���� � �����!" << endl;
                    return;
                }
            }
        }
    }

    // ����� ����������� � ����
    printResultToFile(outputFile, distances, n);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    int** graph = readGraphFromFile("graph.txt", n);
    bellmanFord(graph, n, 0, "result.txt");
    return 0;
}