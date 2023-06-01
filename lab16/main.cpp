#include <iostream>
using namespace std;

int Knapsack(int W, int wt[], int val[], int n)
{
    int i, w;

    int** K = new int* [n + 1]; // объ€вл€ем двумерный массив
    for (int i = 0; i < n + 1; i++)
        K[i] = new int[W + 1];
            
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(
                    val[i - 1] + K[i - 1][w - wt[i - 1]],
                    K[i - 1][w]
                );
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int result = K[n][W];

    // освобождаем пам€ть
    for (int i = 0; i < n + 1; i++)
        delete[] K[i];
    delete[] K;

    return result;
}

int main()
{
    int val[] = { 60, 100, 120 };
    int wt[] = { 10, 20, 30 };
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    cout << "Maximum value that can be put in a knapsack : " << Knapsack(W, wt, val, n);
    return 0;
}