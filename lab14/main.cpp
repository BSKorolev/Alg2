#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

// Хэш-функция для строки s длины len с началом в позиции pos
int my_hash(const char* s, int len, int pos)
{
    int h = 0;
    for (int i = 0; i < len; ++i)
    {
        h += (int)s[pos + i] * pow(128, len - i - 1);
    }
    return h;
}

// Реализация алгоритма Рабина-Карпа для поиска подстроки
int rabin_karp_search(const char* str, const char* substr)
{
    // Получение длин строк
    int str_len = strlen(str);
    int substr_len = strlen(substr);

    // Вычисление хэшей для подстроки и первого окна строки
    int substr_hash = my_hash(substr, substr_len, 0);
    int str_hash = my_hash(str, substr_len, 0);

    // Поиск подстроки
    for (int i = 0; i <= str_len - substr_len; ++i)
    {
        if (substr_hash == str_hash)
        {
            // Дополнительная проверка на совпадение символов
            int j;
            for (j = 0; j < substr_len; ++j)
            {
                if (substr[j] != str[i + j])
                {
                    break;
                }
            }
            if (j == substr_len)
            {
                return i;
            }
        }

        // Обновление хэша для следующего окна
        if (i < str_len - substr_len)
        {
            str_hash -= (int)str[i] * pow(128, substr_len - 1);
            str_hash = str_hash * 128 + (int)str[i + substr_len];
        }
    }

    return -1;
}

int main()
{
    // Открытие файлов для чтения и записи
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    // Проверка наличия файлов
    if (!fin)
    {
        cout << "Error: file input.txt not found\n";
        return 1;
    }
    if (!fout)
    {
        cout << "Error: file output.txt could not be created\n";
        return 1;
    }

    // Считывание исходной строки
    char str[1000];
    fin.getline(str, 1000);

    // Вывод исходной строки
    cout << "Input string: " << str << endl;

    // Ввод строки поиска
    char substr[1000];
    cout << "Enter substring to search: ";
    cin.getline(substr, 1000);

    // Поиск подстроки
    int pos = rabin_karp_search(str, substr);

    // Вывод результата поиска
    if (pos == -1)
    {
        cout << "Substring not found\n";
        fout << "Substring not found\n";
    }
    else
    {
        cout << "Substring found at position " << pos << endl;
        fout << "Substring found at position " << pos << endl;
    }

    // Закрытие файлов
    fin.close();
    fout.close();

    return 0;
}