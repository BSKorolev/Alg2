#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// ��������� ������ ��� �������� ����� Graph
struct Edge {
    int src, dest;
};

class Graph
{
public:
    // ������ �������� ��� ������������� ������ ���������
    vector<vector<int>> adjList;

    // �����������
    Graph(vector<Edge> const& edges, int n)
    {
        // �������� ������ �������, ����� �� �������� `n` ��������� ���� `vector<int>`
        adjList.resize(n);

        // ��������� ����� � ����������������� graph
        for (Edge edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;

            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
    }
};

// ��������� ������ ������ ��� graphs � ������� ����������� ������
string color[] =
{
    "", "BLUE", "GREEN", "RED", "YELLOW", "ORANGE", "PINK",
    "BLACK", "BROWN", "WHITE", "PURPLE", "VOILET"
};

// ������� ��� ���������� ����� �������� Graph
void colorGraph(Graph const& graph, int n)
{
    // ����������� ����, ����������� ������ �������
    unordered_map<int, int> result;

    // ��������� ���� ������� ���� �� ������
    for (int u = 0; u < n; u++)
    {
        // ������������� ��� �������� ����� ������� ������ `u`
        set<int> assigned;

        // ��������� ����� ������� ������ `u` � ��������� �� � ������
        for (int i : graph.adjList[u])
        {
            if (result[i]) {
                assigned.insert(result[i]);
            }
        }

        // ��������� ������ ��������� ����
        int color = 1;
        for (auto& c : assigned)
        {
            if (color != c) {
                break;
            }
            color++;
        }

        // ��������� ������� `u` ������ ��������� ����
        result[u] = color;
    }

    for (int v = 0; v < n; v++)
    {
        cout << "The color assigned to vertex " << v << " is "
            << color[result[v]] << endl;
    }
}

int main()
{
    // vector ����� Graph �������� ����� ����
    vector<Edge> edges = {
        {0, 2}, {0, 4}, {1, 5}, {4, 5}, {1, 4}, {1, 3}, {3, 3}, {2, 5}
    };

    // ����� ���������� ����� � Graph (�� 0 �� 5)
    int n = 6;

    // ������ graph �� �������� �����
    Graph graph(edges, n);

    // ������� Graph � �������������� ������� ���������
    colorGraph(graph, n);

    return 0;
}