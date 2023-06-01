#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> readMatrixFromFile(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    vector<vector<int>> matrix;
    int n;
    file >> n;

    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            int value;
            file >> value;
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    file.close();

    return matrix;
}

void dfs(vector<vector<int>>& adj_matrix, int current_vertex, vector<int>& visited_vertices, vector<int>& component) {
    visited_vertices[current_vertex] = true;
    component.push_back(current_vertex);

    for (int i = 0; i < adj_matrix.size(); ++i) {
        if (adj_matrix[current_vertex][i] && !visited_vertices[i]) {
            dfs(adj_matrix, i, visited_vertices, component);
        }
    }
}

vector<vector<int>> findStronglyConnectedComponents(vector<vector<int>> adj_matrix) {
    vector<vector<int>> scc;

    int n = adj_matrix.size();
    vector<int> visited_vertices(n, false);

    // 1. Прямой обход графа и сбор "финишных" вершин
    vector<int> order;
    for (int i = 0; i < n; ++i) {
        if (!visited_vertices[i]) {
            dfs(adj_matrix, i, visited_vertices, order);
        }
    }

    // 2. Транспонирование графа
    vector<vector<int>> transp_matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transp_matrix[i][j] = adj_matrix[j][i];
        }
    }

    visited_vertices.assign(n, false);

    // 3. Обход в порядке, обратном "финишным" вершинам
    for (int i = n - 1; i >= 0; --i) {
        int current_vertex = order[i];

        if (!visited_vertices[current_vertex]) {
            vector<int> component;
            dfs(transp_matrix, current_vertex, visited_vertices, component);

            scc.push_back(component);
        }
    }

    return scc;
}

void writeResultsToFile(string path, vector<vector<int>> scc) {
    ofstream file(path);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    file << "Number of strongly connected components: " << scc.size() << endl;

    for (int i = 0; i < scc.size(); ++i) {
        file << "Component " << i + 1 << ": ";
        for (int j = 0; j < scc[i].size(); ++j) {
            file << scc[i][j] << " ";
        }
        file << endl;
    }

    file.close();
}

int main() {
    string input_file = "graph.txt";
    string output_file = "result.txt";

    vector<vector<int>> adj_matrix = readMatrixFromFile(input_file);

    vector<vector<int>> scc = findStronglyConnectedComponents(adj_matrix);

    writeResultsToFile(output_file, scc);

    return 0;
}