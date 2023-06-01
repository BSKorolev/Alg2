#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

const int MAX_SIZE = 100;

int getNextVertex(bool visited[], int distances[], int n) {
    int minDist = INT_MAX;
    int minVertex = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && distances[i] < minDist) {
            minDist = distances[i];
            minVertex = i;
        }
    }
    return minVertex;
}

void dijkstra(int graph[][MAX_SIZE], int n, int start) {
    bool visited[MAX_SIZE] = { false }; // ������������ ���������� ������
    int distances[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX; // ��������� ���������� �� ���� ������ � "�������������"
    }
    distances[start] = 0; // ���������� �� ��������� ������� ����� 0
    for (int i = 0; i < n; i++) {
        int v = getNextVertex(visited, distances, n); // ����� ��������� ������� � ����������� �����������
        if (v == -1) { // ���� ��� ������� ���� ��������, ������������� ��������
            break;
        }
        visited[v] = true; // �������� ��������� ������� ��� ����������
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[v][j] > 0) { // ���� ������� ��� �� �������� � ���� ����� ����� ������� � j
                int d = distances[v] + graph[v][j]; // ��������� ����� ���������� �� j ����� ������� �������
                if (d < distances[j]) { // ���� ����� ���������� ������, ��������� ������ �������� � ������� distances
                    distances[j] = d;
                }
            }
        }
    }
    ofstream fout("result.txt");
    for (int i = 0; i < n; i++) {
        fout << start << " -> " << i << " : " << distances[i] << endl;
    }
    fout.close();
}

int main() {
    int n;
    int graph[MAX_SIZE][MAX_SIZE];
    ifstream fin("graph.txt");
    fin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> graph[i][j];
        }
    }
    fin.close();
    dijkstra(graph, n, 0);
    return 0;
}