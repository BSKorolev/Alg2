#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ���������� �������� � �������� (ASCII)
const int MAX_CHARS = 256;

// ������� ���������� ��������� ��������
void buildFiniteAutomaton(string pattern, vector<vector<int> >& finiteAutomaton) {
    const int m = pattern.length();
    finiteAutomaton.resize(m + 1, vector<int>(MAX_CHARS, 0));
    int lps = 0; // ����� �������������� �������� pattern[0...i-1], ������� ����� �������� ��������� pattern[0...i]
    finiteAutomaton[0][pattern[0]] = 1; // ������ ������
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < MAX_CHARS; j++) {
            finiteAutomaton[i][j] = finiteAutomaton[lps][j];
        }
        if (i < m) {
            finiteAutomaton[i][pattern[i]] = i + 1;
            lps = finiteAutomaton[lps][pattern[i]];
        }
    }
}

// ������� ������ ��������� ������� � �����
vector<int> searchPattern(string pattern, string text) {
    vector<vector<int> > finiteAutomaton;
    buildFiniteAutomaton(pattern, finiteAutomaton);
    vector<int> res;
    const int m = pattern.length();
    const int n = text.length();
    int currentState = 0;
    for (int i = 0; i < n; i++) {
        currentState = finiteAutomaton[currentState][text[i]];
        if (currentState == m) {
            res.push_back(i - m + 1);
        }
    }
    return res;
}

// ������� �������
int main() {
    setlocale(LC_ALL, "Russian");
    string pattern;
    cout << "������� ������� ��� ������: ";
    cin >> pattern;
    string fileName;
    cout << "������� ��� ����� � �������: ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file) {
        cerr << "������ ��� �������� ����� \"" << fileName << "\" ��� ������!\n";
        return -1;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    vector<int> res = searchPattern(pattern, text);

    if (res.size() == 0) {
        cout << "������� �� ������ � ������.\n";
    }
    else {
        string outputFileName;
        cout << "������� ��� ����� ��� ������ ����������: ";
        cin >> outputFileName;

        ofstream outputFile(outputFileName);
        if (!outputFile) {
            cerr << "������ ��� �������� ����� \"" << outputFileName << "\" ��� ������!\n";
            return -1;
        }

        outputFile << "������� \"" << pattern << "\" ������ � ������ � ��������� ��������:\n";
        for (int i = 0; i < res.size(); i++) {
            outputFile << res[i] << " ";
        }
        outputFile << endl;

        outputFile.close();
    }

    return 0;
}