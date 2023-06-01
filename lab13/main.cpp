#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ���������� ��������� ������-���� ��� ������ ���������
int boyer_moore_search(const char* str, const char* substr)
{
    // ��������� ���� �����
    int str_len = strlen(str);
    int substr_len = strlen(substr);

    // �������� ������� ��������
    int table[256];
    for (int i = 0; i < 256; ++i)
    {
        table[i] = substr_len;
    }
    for (int i = 0; i < substr_len - 1; ++i)
    {
        table[substr[i]] = substr_len - i - 1;
    }

    // ����� ���������
    int i = substr_len - 1;
    int j = substr_len - 1;
    while (i < str_len)
    {
        if (str[i] == substr[j])
        {
            if (j == 0)
            {
                return i;
            }
            --i;
            --j;
        }
        else
        {
            i += table[str[i]];
            j = substr_len - 1;
        }
    }

    return -1;
}

int main()
{
    // �������� ������ ��� ������ � ������
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    // �������� ������� ������
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

    // ���������� �������� ������
    char str[1000];
    fin.getline(str, 1000);

    // ����� �������� ������
    cout << "Input string: " << str << endl;

    // ���� ������ ������
    char substr[1000];
    cout << "Enter substring to search: ";
    cin.getline(substr, 1000);

    // ����� ���������
    int pos = boyer_moore_search(str, substr);

    // ����� ���������� ������
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

    // �������� ������
    fin.close();
    fout.close();

    return 0;
}