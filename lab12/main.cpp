#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ������� ���������� �������-�������
vector<int> buildPrefixFunction(string pattern) {
    const int m = pattern.length();
    vector<int> prefixFunction(m);
    prefixFunction[0] = 0;
    int k = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[i] != pattern[k]) {
            k = prefixFunction[k - 1];
        }
        if (pattern[i] == pattern[k]) {
            k++;
        }
        prefixFunction[i] = k;
    }
    return prefixFunction;
}

// ������� ������ ��������� ������� � ����� � ������� ��������� �����-�������-������
vector<int> searchPattern(string pattern, string text) {
    vector<int> prefixFunction = buildPrefixFunction(pattern);
    vector<int> res;
    int n = text.length();
    int m = pattern.length();
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = prefixFunction[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            res.push_back(i - m + 1);
            j = prefixFunction[j - 1];
        }
    }
    return res;
}

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