#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Количество символов в алфавите (ASCII)
const int MAX_CHARS = 256;

// Функция построения конечного автомата
void buildFiniteAutomaton(string pattern, vector<vector<int> >& finiteAutomaton) {
    const int m = pattern.length();
    finiteAutomaton.resize(m + 1, vector<int>(MAX_CHARS, 0));
    int lps = 0; // длина наидлиннейшего суффикса pattern[0...i-1], который также является префиксом pattern[0...i]
    finiteAutomaton[0][pattern[0]] = 1; // первый символ
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

// Функция поиска вхождений образца в текст
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

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    string pattern;
    cout << "Введите образец для поиска: ";
    cin >> pattern;
    string fileName;
    cout << "Введите имя файла с текстом: ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file) {
        cerr << "Ошибка при открытии файла \"" << fileName << "\" для чтения!\n";
        return -1;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    vector<int> res = searchPattern(pattern, text);

    if (res.size() == 0) {
        cout << "Образец не найден в тексте.\n";
    }
    else {
        string outputFileName;
        cout << "Введите имя файла для записи результата: ";
        cin >> outputFileName;

        ofstream outputFile(outputFileName);
        if (!outputFile) {
            cerr << "Ошибка при открытии файла \"" << outputFileName << "\" для записи!\n";
            return -1;
        }

        outputFile << "Образец \"" << pattern << "\" найден в тексте в следующих позициях:\n";
        for (int i = 0; i < res.size(); i++) {
            outputFile << res[i] << " ";
        }
        outputFile << endl;

        outputFile.close();
    }

    return 0;
}