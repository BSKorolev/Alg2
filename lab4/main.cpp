#include <iostream>
#include <fstream>
using namespace std;

const int N = 10;
int n;
void dfs(int v, int visited[], int graph[N][N])
{
    visited[v] = 1; // �������� ������� ��� ����������
    for (int i = 0; i <n; i++)
    {
        if (graph[v][i] == 1 && visited[i] == 0) // ���� ������� i ��������� � v � ��� �� ��������
        {
            dfs(i, visited, graph); // ���������� �������� dfs ��� ������� i
        }
    }
}

int main()
{
    ifstream fin;
    fin.open("graph.txt"); // ��������� ���� � �������
    int n;
    fin >> n; // ��������� ���������� ������
    int graph[N][N]; // ������� ������� ���������
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> graph[i][j]; // ��������� ������� ���������
        }
    }
    fin.close(); // ��������� ����

    int visited[N] = { 0 }; // ������ ��� ������� ���������� ������
    int count = 0; // ������� ��������� ���������
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0) // ���� ������� ��� �� ��������
        {
            count++; // ����������� ������� ��������� ���������
            dfs(i, visited, graph); // �������� dfs ��� ����� ���������� ���������
        }
    }

    // ������� ��������� � ����
    ofstream fout;
    fout.open("result.txt");
    fout << "���������� ��������� ���������: " << count << endl;
    fout.close();

    return 0;
}