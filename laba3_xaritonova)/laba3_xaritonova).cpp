#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <string>
#include <iomanip>

using namespace std;


string findMaxCommonSubsequence(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int i = m;
    int j = n;
    string result;

    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            result = str1[i - 1] + result;
            --i;
            --j;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        }
        else {
            --j;
        }
    }

    return result;
}


void printMatrix(const vector<vector<int>>& matrix) {
    for (size_t i = 1; i < matrix.size(); ++i) {
        for (const int& element : matrix[i]) {
            cout << setw(4) << element << " ";
        }
        cout << endl;
    }
}


const int MaxN = 1000; // for Solve
int Op[MaxN]; // for Solve
vector<pair<int, int>> oper; // for Solve


void printIncludedItems(const vector<vector<int>>& a, const vector<vector<int>>& w, int i, int j) {
    if (i > 0 && j > 0) {
        if (a[i][j] != a[i - 1][j]) {
            printIncludedItems(a, w, i - 1, j - w[0][i]);
            cout << "Вещь " << i << " включена в рюкзак." << endl;
        }
        else {
            printIncludedItems(a, w, i - 1, j);
        }
    }
}

int bag(vector<vector<int>>& a, const vector<vector<int>>& w, int k, int w_max) {
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= w_max; j++) {
            if (w[0][i] <= j && w[1][i] + a[i - 1][j - w[0][i]] > a[i - 1][j]) {
                a[i][j] = w[1][i] + a[i - 1][j - w[0][i]];
            }
            else {
                a[i][j] = max(a[i - 1][j], a[i][j - 1]);
            }
        }
    }
    int maxUtility = a[k][w_max];
    cout << "Максимально возможная суммарная полезность: " << maxUtility << "\n" << endl;

    int i = k;
    int j = w_max;
    cout << "Включенные вещи в рюкзак:" << endl;
    printIncludedItems(a, w, i, j);

    cout << "Итоговая стоимость: " << maxUtility << endl;
    cout << "Получившийся вес: " <<  w_max << endl;

    return 0;
}

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
        cout << "/----------------------------------------------------------------------------/\n";
        for (int j = 2; j <= i - 1; ++j) {
            int current_op = Op[j] + Op[i - j] + 1;
            if (current_op < Op[i]) {
                Op[i] = current_op;
                oper.push_back({ j, i - j });
                cout << "/------------------------------------------------------------/\n";
            }

            if (i % j == 0) {
                current_op = Op[i / j] + j - 1;
                if (current_op < Op[i]) {
                    Op[i] = current_op;
                    oper.push_back({ i / j, j - 1 });
                    cout << "/-----------------------------------------------------------------/\n";
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

            string str1, str2;

            cout << "Введите первую строку: ";
            cin >> str1;

            cout << "Введите вторую строку: ";
            cin >> str2;

            string result = findMaxCommonSubsequence(str1, str2);

            cout << "Максимально совпадающая подцепочка: " << result << endl;

            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 5) {
            cout << "Алгоритм: Решение задачи о рюкзаке\n";
            int k;
            int w_max;
            cout << "Введите количество вещей в рюкзаке: ";
            cin >> k;
            cout << "Введите максимальный вес рюкзака: ";
            cin >> w_max;
            vector<vector<int>> a(k + 1, vector<int>(w_max + 1, 0));
            // Определение размера вектора w
            vector<vector<int>> w(2, vector<int>(k + 1, 0));

            for (int i = 0; i < 2; i++) {
                for (int j = 1; j <= k; j++) {
                    cout << "Введите " << (i == 0 ? "вес" : "ценность") << " для вещи " << j << ": ";
                    cin >> w[i][j];
                }
            }
            cout << "\n";
            cout << "Сформированный массив:" << endl;
            for (int i = 0; i < 2; i++) {
                for (int j = 1; j <= k; j++) {
                    cout << w[i][j] << " ";
                }
                cout << endl;
            }
            cout << "\n";
            for (int i = 0; i <= w_max; i++) {
                a[0][i] = 0;
                for (int j = 0; j <= k; j++) {
                    a[j][0] = 0;
                }
            }

            bag(a, w, k, w_max);


            cout << "\nОптимальное заполнение рюкзака:" << endl;
            printMatrix(a);

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
