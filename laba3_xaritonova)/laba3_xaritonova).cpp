#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

const int MaxN = 1000; // for Solve
int Op[MaxN]; // for Solve
vector<pair<int, int>> oper; // for Solve

int optimal_path_triangle(const vector<vector<int>>& a, int n) {
    vector<vector<int>> copy(n, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++) {
        copy[i][0] = 0;
        for (int j = 1; j <= i + 1; j++) {
            copy[i][j] = a[i][j - 1];
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i + 1; j++) {
            copy[i][j] = copy[i][j] + max(copy[i - 1][j - 1], copy[i - 1][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << copy[i][j] << " ";
        }
        cout << endl;
    }

    int result = *max_element(copy[n - 1].begin() + 1, copy[n - 1].end());
    cout << "Максимальное суммарное значение нагрузок: " << result << endl;

    vector<int> path(n, 0);
    int max_col = distance(copy[n - 1].begin() + 1, max_element(copy[n - 1].begin() + 1, copy[n - 1].end())) + 1;
    path[n - 1] = max_col;

    for (int i = n - 2; i >= 0; i--) {
        if (max_col > 1 && copy[i][max_col - 1] > copy[i][max_col]) {
            max_col = max_col - 1;
        }
        else {
            max_col = max_col;
        }
        path[i] = max_col;
    }

    cout << "Оптимальный путь: ";
    for (int i = 0; i < n; i++) {
        cout << "(" << i + 1 << ", " << path[i] << ") ";
    }
    cout << endl;

    return result;
}

void Solve(int n) {
    Op[1] = 0;

    for (int i = 2; i <= n; ++i) {
        Op[i] = Op[i - 1] + 1;
        oper.push_back({ i - 1, i });

        for (int j = 2; j <= i - 1; ++j) {
            int current_op = Op[j] + Op[i - j] + 1;
            if (current_op < Op[i]) {
                Op[i] = current_op;
                oper.push_back({ j, i - j });
            }

            if (i % j == 0) {
                current_op = Op[i / j] + j - 1;
                if (current_op < Op[i]) {
                    Op[i] = current_op;
                    oper.push_back({ i / j, j - 1 });
                }
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    while (true) {
        cout << "Алгоритмы динамического программирования : \n1.Алгоритм оптимального пути в треугольнике(на максимум)\n2.Алгоритм Поиск оптимального пути в четырехугольнике(на минимум)" << endl;
        cout << "3.Алгоритм Поиск оптимальной последовательности операций при возведении числа в степень\n4.Алгоритм Поиск максимально совпадающей подцепочки\n5.Алгоритм Решение задачи о рюкзаке" << endl;
        cout << "6.Выход" << endl;
        cout << "/---------------------------------------------------------------/\n" << endl;

        int m;
        cout << "Введите номер алгоритма в соответствии с нумерацией в списке : "; cin >> m; cout << "\n";
        cout << "/---------------------------------------------------------------/\n" << endl;

        if (m == 6) {
            cout << "Выход из программы.\n";
            break;
        }
        if (m == 1) {
            cout << "Алгоритм оптимального пути в треугольнике(на максимум)\n";
            cout << "Введите количество строк в треугольнике: ";
            int n;
            cin >> n;
            vector<vector<int>> a(n, vector<int>(n));
            cout << "Введите элементы треугольника(элементы предполагают собой вес каждой вершины треугольника):\n";
            cout << "Пример ввода при 3 вершинах:" << endl;
            cout << "1\n1 2\n1 2 3\n" << endl;
            cout << "/---------------------------------------------------------------/\n" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j <= i; j++)
                    cin >> a[i][j];
            }
            cout << "\n";
            optimal_path_triangle(a, n);
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 2) {
            cout << "Алгоритм Поиск оптимального пути в четырехугольнике(на минимум)\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 3) {
            cout << "Алгоритм Поиск оптимальной последовательности операций при возведении числа в степень\n";
            int n;
            cout << "Введи степень: ";
            cin >> n;

            Solve(n);

            cout << "Минимальное количество операций для возведения в " << n << " степень: " << Op[n] << endl;
            cout << "Операции, примененные для возведения в " << n << " степень:" << endl;

            for (const auto& operation : oper) {
                cout << operation.first << " + " << operation.second << endl;
            }
            
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 4) {
            cout << "Алгоритм Поиск максимально совпадающей подцепочки\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 5) {
            cout << "Алгоритм Решение задачи о рюкзаке\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else {
            cout << "/---------------------------------------------------------------/\n" << endl;
            cout << "\nНеверный выбор. Попробуйте еще раз.\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
    }

    return 0;
}
