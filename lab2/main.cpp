#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

const int MAX = 100;
int graph[MAX][MAX], d[MAX], p[MAX];
bool visited[MAX];
int n, start, last;

void bfs(int s) {
    queue<int> q; // ������� ������
    q.push(s);
    visited[s] = true; // �������� ������� ����������
    d[s] = 0; // ���������� �� ��������� ������� �� ��� ����� ����� 0
    p[s] = -1; // �������������� ��� ��������� ������� -1

    while (!q.empty()) {
        int v = q.front(); // ��������� ������� �� �������
        q.pop();

        // ���������� ��� ������������ ������� �������
        for (int u = 0; u < n; u++) {
            if (graph[v][u] && !visited[u]) {
                visited[u] = true; // �������� ������� ����������
                q.push(u); // ��������� � �������
                d[u] = d[v] + 1; // ���������� �� ������� u �� 1 ������, ��� ���������� �� ������� v
                p[u] = v; // ���������� ���������������
            }
        }
    }
}

void read_graph(string filename) {
    ifstream fin(filename); // ��������� ����
    fin >> n >> start >> last; // ��������� ���������� ������, ��������� � �������� �������
    start--; // ��������� �� 1, ����� ������ ������ ���������� � 0
    last--;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> graph[i][j]; // ��������� ������� ���������
        }
    }
}

void write_result(string filename) {
    ofstream fout(filename); // ������� ���� ��� ������
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
    read_graph("graph.txt"); // ������ ���� �� �����
    bfs(start); // ���� ���������� ���� �� ��������� �������
    write_result("result.txt"); // ���������� ��������� � ����
    return 0;
}