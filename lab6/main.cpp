#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100; // ������������ ���������� ������ � �����

// ��������� ��� ����� �����
struct Edge {
    int from, to, weight;
};

// ��������� ��� ������ �����������
struct Subset {
    int parent, rank;
};

// ������� ��������� ����� ����� �� ����
bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

// ������� ������ ������������, � �������� ����������� i-�� �������
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// ������� ����������� ���� ����������� � ����
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

// ������� ���������� ��������� ��������
void kruskalMST(int graph[][MAXN], int V, vector<Edge>& result) {
    int E = 0;
    vector<Edge> edges;

    // ��������� ������ edges ������� �����
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                Edge e = { i, j, graph[i][j] };
                edges.push_back(e);
            }
        }
    }

    // ��������� ��� ����� ����� �� ����
    sort(edges.begin(), edges.end(), compareEdges);

    // ������� ����� ����������� ��� ������ ������� �����
    Subset* subsets = new Subset[V];
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // �������� �� ���� ������, ������� �� ����� � ����������� �����
    for (int i = 0; i < edges.size(); i++) {
        // ������� ������������ ������, � ������� ����������� �����
        int x = find(subsets, edges[i].from);
        int y = find(subsets, edges[i].to);

        // ���� ������������ ��������, �� ���������� �� � ����
        if (x != y) {
            result.push_back(edges[i]);
            Union(subsets, x, y);
            E++;
        }

        // ���� �� ��� �������� V-1 �����, �� ����������� ��������
        if (E == V - 1) {
            break;
        }
    }

    delete[] subsets;
}

// ������� ������ ���������� � ����
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
    int graph[MAXN][MAXN]; // ������� ��������� �����
    int V; // ���������� ������

    // ��������� ������ �� �����
    ifstream in("graph.txt");
    in >> V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            in >> graph[i][j];
        }
    }
    in.close();

    vector<Edge> result; // ��������� ������ ���������
    kruskalMST(graph, V, result); // ��������� �������� ��������

    writeToFile(result); // ���������� ��������� � ����

    return 0;
}