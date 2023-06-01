#include <iostream>
#include <fstream>
using namespace std;

const int N = 10;
int n;
void dfs(int v, int visited[], int graph[N][N])
{
    visited[v] = 1; // отмечаем вершину как посещенную
    for (int i = 0; i <n; i++)
    {
        if (graph[v][i] == 1 && visited[i] == 0) // если вершина i соединена с v и еще не посещена
        {
            dfs(i, visited, graph); // рекурсивно вызываем dfs для вершины i
        }
    }
}

int main()
{
    ifstream fin;
    fin.open("graph.txt"); // открываем файл с данными
    int n;
    fin >> n; // считываем количество вершин
    int graph[N][N]; // создаем матрицу смежности
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> graph[i][j]; // считываем матрицу смежности
        }
    }
    fin.close(); // закрываем файл

    int visited[N] = { 0 }; // массив для отметки посещенных вершин
    int count = 0; // счетчик компонент связности
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0) // если вершина еще не посещена
        {
            count++; // увеличиваем счетчик компонент связности
            dfs(i, visited, graph); // вызываем dfs для новой компоненты связности
        }
    }

    // выводим результат в файл
    ofstream fout;
    fout.open("result.txt");
    fout << "Количество компонент связности: " << count << endl;
    fout.close();

    return 0;
}