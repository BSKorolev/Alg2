/*  
Структура данных Edge - представляет ребро в графе. У каждого ребра есть исходящая вершина (src) и входящая вершина (dest).
Класс Graph - представляет граф, построенный на основе списка ребер. В конструкторе класса создается вектор векторов для представления списка смежности.
Функция colorGraph -осуществляет раскраску графа. Для хранения цветов вершин используется структура данных unordered_map. 
Функция перебирает каждую вершину графа и назначает ей первый доступный цвет. Для каждой вершины функция проверяет уже назначенные цвета соседей и сохраняет их в наборе. 
Затем она перебирает цвета, пока не найдет первый свободный цвет, и назначает его данной вершине. Затем назначенный цвет вершины выводится на экран.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// Ñòðóêòóðà äàííûõ äëÿ õðàíåíèÿ ðåáðà Graph
struct Edge {
    int src, dest;
};

class Graph
{
public:
    // âåêòîð âåêòîðîâ äëÿ ïðåäñòàâëåíèÿ ñïèñêà ñìåæíîñòè
    vector<vector<int>> adjList;

    // Êîíñòðóêòîð
    Graph(vector<Edge> const& edges, int n)
    {
        // èçìåíèòü ðàçìåð âåêòîðà, ÷òîáû îí ñîäåðæàë `n` ýëåìåíòîâ òèïà `vector<int>`
        adjList.resize(n);

        // äîáàâëÿåì ðåáðà â íåîðèåíòèðîâàííûé graph
        for (Edge edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;

            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
    }
};

// Äîáàâëÿåì áîëüøå öâåòîâ äëÿ graphs ñ áîëüøèì êîëè÷åñòâîì âåðøèí
string color[] =
{
    "", "BLUE", "GREEN", "RED", "YELLOW", "ORANGE", "PINK",
    "BLACK", "BROWN", "WHITE", "PURPLE", "VOILET"
};

// Ôóíêöèÿ äëÿ ïðèñâîåíèÿ öâåòà âåðøèíàì Graph
void colorGraph(Graph const& graph, int n)
{
    // îòñëåæèâàåì öâåò, ïðèñâîåííûé êàæäîé âåðøèíå
    unordered_map<int, int> result;

    // íàçíà÷àåì öâåò âåðøèíå îäíó çà äðóãîé
    for (int u = 0; u < n; u++)
    {
        // óñòàíàâëèâàåì äëÿ õðàíåíèÿ öâåòà ñìåæíûõ âåðøèí `u`
        set<int> assigned;

        // ïðîâåðÿåì öâåòà ñìåæíûõ âåðøèí `u` è ñîõðàíÿåì èõ â íàáîðå
        for (int i : graph.adjList[u])
        {
            if (result[i]) {
                assigned.insert(result[i]);
            }
        }

        // ïðîâåðÿåì ïåðâûé ñâîáîäíûé öâåò
        int color = 1;
        for (auto& c : assigned)
        {
            if (color != c) {
                break;
            }
            color++;
        }

        // íàçíà÷àåì âåðøèíå `u` ïåðâûé äîñòóïíûé öâåò
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
    // vector ðåáåð Graph ñîãëàñíî ñõåìå âûøå
    vector<Edge> edges = {
        {0, 2}, {0, 4}, {1, 5}, {4, 5}, {1, 4}, {1, 3}, {3, 3}, {2, 5}
    };

    // îáùåå êîëè÷åñòâî óçëîâ â Graph (îò 0 äî 5)
    int n = 6;

    // ñòðîèì graph èç çàäàííûõ ðåáåð
    Graph graph(edges, n);

    // öâåòíîé Graph ñ èñïîëüçîâàíèåì æàäíîãî àëãîðèòìà
    colorGraph(graph, n);

    return 0;
}
