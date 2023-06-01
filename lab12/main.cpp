#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Функция построения префикс-функции
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

// Функция поиска вхождений образца в текст с помощью алгоритма Кнута-Морриса-Пратта
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