#include <iostream>
#include <fstream>
using namespace std;

const int MAXN = 100; // ������������ ���������� ������ � �����

int n; // ���������� ������ � �����
int graph[MAXN][MAXN]; // ������� ���������
int parent[MAXN]; // ������ ������������ ������
int key[MAXN]; // ������ ������
bool visited[MAXN]; // ������, �������� ���������� � ��������� �������

// �������, ��������� ������� � ����������� ������
int minKey() {
    int m = INT_MAX, index;

    for (int i = 0; i < n; i++)
        if (!visited[i] && key[i] < m)
            m = key[i], index = i;

    return index;
}

// �������, ����������� �������� �����
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

    // ��������� ������� ��������� �� �����
    fin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> graph[i][j];

    prim(); // ������ ������ ���������� �����

    // ������� ��������� � ����
    for (int i = 1; i < n; i++)
        fout << parent[i] << " - " << i << " " << graph[i][parent[i]] << endl;

    fin.close();
    fout.close();
    return 0;
}