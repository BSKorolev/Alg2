/* 
Функция `knapsack` использует мемоизацию, чтобы избежать повторных рассчетов при вызове функции для одних и тех же параметров.
Для этого используется двумерный массив K, который хранит рассчитанные ранее значения. Каждый элемент K[i][j] соответствует рассчету максимальной стоимости для i предметов и j веса рюкзака.
Начальное значение каждого элемента устанавливается на -1.
Если число предметов или максимальный вес рюкзака равен нулю, функция возвращает ноль.
Если значение для данного подмножества предметов уже было рассчитано, функция возвращает его.
 Если вес текущего предмета больше максимального веса рюкзака, пропускаем его и рассчитываем максимальную стоимость для подмножества предметов, не включающего текущий.
 Возвращаем максимум между рассчетом максимальной стоимости для данного подмножества предметов с учётом рассматриваемого предмета и без него.
*/
#include <iostream>
using namespace std;

int Knapsack(int W, int wt[], int val[], int n)
{
    int i, w;

    int** K = new int* [n + 1]; // îáúÿâëÿåì äâóìåðíûé ìàññèâ
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

    // îñâîáîæäàåì ïàìÿòü
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
