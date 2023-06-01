#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// —труктура данных дл€ хранени€ ребра Graph
struct Edge {
    int src, dest;
};

class Graph
{
public:
    // вектор векторов дл€ представлени€ списка смежности
    vector<vector<int>> adjList;

    //  онструктор
    Graph(vector<Edge> const& edges, int n)
    {
        // изменить размер вектора, чтобы он содержал `n` элементов типа `vector<int>`
        adjList.resize(n);

        // добавл€ем ребра в неориентированный graph
        for (Edge edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;

            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
    }
};

// ƒобавл€ем больше цветов дл€ graphs с большим количеством вершин
string color[] =
{
    "", "BLUE", "GREEN", "RED", "YELLOW", "ORANGE", "PINK",
    "BLACK", "BROWN", "WHITE", "PURPLE", "VOILET"
};

// ‘ункци€ дл€ присвоени€ цвета вершинам Graph
void colorGraph(Graph const& graph, int n)
{
    // отслеживаем цвет, присвоенный каждой вершине
    unordered_map<int, int> result;

    // назначаем цвет вершине одну за другой
    for (int u = 0; u < n; u++)
    {
        // устанавливаем дл€ хранени€ цвета смежных вершин `u`
        set<int> assigned;

        // провер€ем цвета смежных вершин `u` и сохран€ем их в наборе
        for (int i : graph.adjList[u])
        {
            if (result[i]) {
                assigned.insert(result[i]);
            }
        }

        // провер€ем первый свободный цвет
        int color = 1;
        for (auto& c : assigned)
        {
            if (color != c) {
                break;
            }
            color++;
        }

        // назначаем вершине `u` первый доступный цвет
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
    // vector ребер Graph согласно схеме выше
    vector<Edge> edges = {
        {0, 2}, {0, 4}, {1, 5}, {4, 5}, {1, 4}, {1, 3}, {3, 3}, {2, 5}
    };

    // общее количество узлов в Graph (от 0 до 5)
    int n = 6;

    // строим graph из заданных ребер
    Graph graph(edges, n);

    // цветной Graph с использованием жадного алгоритма
    colorGraph(graph, n);

    return 0;
}