																																													#include <iostream>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;
#define N 100
struct point {
    double x, y;
};

point p0;

point nextToTop(stack<point> &S) {
    point p = S.top();
    S.pop();
    point res = S.top();
    S.push(p);
    return res;
}

double dist(point p1, point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

int orientation(point p, point q, point r) {
    double val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;       
}

int compare(const void *vp1, const void *vp2) {
   point *p1 = (point *)vp1;
   point *p2 = (point *)vp2;

   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}

stack<point> grahamScan(point points[], int n) {
    stack<point> S;

    double ymin = points[0].y;
    int min = 0;
    for (int i = 1; i < n; i++) {
        double y = points[i].y;

        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    swap(points[0], points[min]);

    p0 = points[0];
    qsort(&points[1], n-1, sizeof(point), compare);

    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0)
            i++;

        points[m] = points[i];
        m++;
    }

    if (m < 3) return S;

    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (int i = 3; i < m; i++) {
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    return S;
}

int main() {

    setlocale(LC_ALL, "Russian");

    int n;

    cout << "Введите количество точек: ";
    cin >> n;

    point points[N];

    for (int i = 0; i < n; i++) {
        cout << "Введите координату x точки " << i+1 << ": ";
        cin >> points[i].x;

        cout << "Введите координату y точки " << i+1 << ": ";
        cin >> points[i].y;
    }

    stack<point> S = grahamScan(points, n);

    if (S.empty())
        cout << "Выпуклая оболочка не существует." << endl;
    else
        cout << "Выпуклая оболочка существует." << endl;

    return 0;
}