#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <string>
#include <iomanip>
#include <windows.h>
#include <cmath>

using namespace std;

// function to calculate the minimum path in a quadrilateral
int min_path_sum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[0][0] = grid[0][0];
    for (int j = 1; j < n; ++j) {
        dp[0][j] = grid[0][j] + dp[0][j - 1];
    }
    for (int i = 1; i < m; ++i) {
        dp[i][0] = grid[i][0] + dp[i - 1][0];
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    cout << "Матрица минимальных сумм путей:\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    return dp[m - 1][n - 1];
}

// function for Finding the maximum matching substring
void findMaxCommonSubsequence(const string& word1, const string& word2) {
    int m = word1.length();
    int n = word2.length();

    vector<vector<int>> A(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (tolower(word1[i - 1]) == tolower(word2[j - 1])) {
                A[i][j] = A[i - 1][j - 1] + 1;
            }
            else {
                A[i][j] = max(A[i - 1][j], A[i][j - 1]);
            }
        }
    }

    int lon = A[m][n];
    string result(lon, ' ');

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (tolower(word1[i - 1]) == tolower(word2[j - 1])) {
            result[--lon] = word1[i - 1];
            i--;
            j--;
        }
        else if (A[i - 1][j] > A[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    reverse(result.begin(), result.end());

    cout << "Длина максимальной подпоследовательности: " << A[m][n] << endl;
    cout << "Максимальная подпоследовательность: " << result << endl;
}

// helper function for outputting a matrix from a function findMaxCommonSubsequence
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

//helper function for outputting matrix function bag

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


// function for solving the knapsack problem
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


// function for calculating the optimal path in a triangle to the maximum
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


// helper function for helper function for outputting operations from Solve
struct Step {
    int op_count; 
    vector<string> operations; 
};


// function for finding the optimal sequence of operations when raising a number to a power
void Solve(int n) {
    vector<Step> steps(n + 1);

    steps[1].op_count = 0;

    for (int i = 2; i <= n; ++i) {
        steps[i].op_count = steps[i - 1].op_count + 1;
        steps[i].operations = steps[i - 1].operations;
        steps[i].operations.push_back("k^" + to_string(i));

        for (int j = 2; j <= i - 1; ++j) {
            int current_op = steps[j].op_count + steps[i - j].op_count + 1;
            if (current_op < steps[i].op_count) {
                steps[i].op_count = current_op;
                steps[i].operations = steps[j].operations;
                for (const auto& op : steps[i - j].operations) {
                    steps[i].operations.push_back(op);
                }
                steps[i].operations.push_back("Умножить результат шага " + to_string(j) + " на резульат " + to_string(i - j));
            }

            if (i % j == 0) {
                current_op = steps[i / j].op_count + j - 1;
                if (current_op < steps[i].op_count) {
                    steps[i].op_count = current_op;
                    steps[i].operations = steps[i / j].operations;
                    for (int k = 1; k < j; ++k) {
                        steps[i].operations.push_back("Умножить результат шага " + to_string(i / j) + " на себя");
                    }
                }
            }
        }
    }

    cout << "Operations for " << n << ": " << endl;
    for (const auto& op : steps[n].operations) {
        cout << op << endl;
    }
}


int main()
{
    // setting the console code page
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // program menu
    while (true) {
        cout << "Алгоритмы динамического программирования : \n1.Алгоритм оптимального пути в треугольнике(на максимум)\n2.Алгоритм Поиск оптимального пути в четырехугольнике(на минимум)" << endl;
        cout << "3.Алгоритм Поиск оптимальной последовательности операций при возведении числа в степень\n4.Алгоритм Поиск максимально совпадающей подцепочки\n5.Алгоритм Решение задачи о рюкзаке" << endl;
        cout << "6.Выход" << endl;
        cout << "/---------------------------------------------------------------/\n" << endl;

        int m;
        cout << "Введите номер алгоритма в соответствии с нумерацией в списке : "; cin >> m; cout << "\n";
        cout << "/---------------------------------------------------------------/\n" << endl;

        if (m == 6) { // exit the program
            cout << "Выход из программы.\n";
            break;
        }
        if (m == 1) { // print optimal_path_triangle
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
        else if (m == 2) { // print min_path_sum
            cout << "Алгоритм Поиск оптимального пути в четырехугольнике(на минимум)\n";
            int n;
            int k;
            cout << "Ввведите размерность квадрата nxk " << endl;
            cout << "Введите n: "; cin >> n; 
            cout << "Введите k: "; cin >> k;
            vector<vector<int>> b(n * 2 - 1, vector<int>(k, k + 2));

            for (int i = 0; i < n * 2 - 1; i++) {
                for (int j = 0; j < k; j++) {
                    b[i][j] = 0;
                }
            }
            for (int i = 0; i < n * 2 - 1; i++) {
                if (i % 2 != 0) {
                    for (int j = 0; j < k; j++) {
                        cout << "Введите дорогу " << i + 1 << "-" << j + 1 << ": ";
                        cin >> b[i][j];
                    }
                }
                else {
                    for (int j = 0; j < k - 1; j++) {
                        cout << "Введите дорогу " << i + 1 << "-" << j + 1 << ": ";
                        cin >> b[i][j];
                    }
                }
            }
            for (int i = 0; i < n * 2 - 1; i++) {
                cout << endl;
                for (int j = 0; j < k; j++) {
                    cout << " " << b[i][j];
                }
            }
            cout << endl;
            int result = min_path_sum(b);

            cout << "Минимальная сумма пути: " << result << endl;

            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 3) { // print Solve
            cout << "Алгоритм Поиск оптимальной последовательности операций при возведении числа в степень\n";
            int n;
            cout << "Введи степень: ";
            cin >> n;

            Solve(n);

  
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 4) { //print findMaxCommonSubsequence
            cout << "Алгоритм Поиск максимально совпадающей подцепочки\n";
            string word1, word2;

            cout << "Введите первое слово: ";
            cin >> word1;

            cout << "Введите второе слово: ";
            cin >> word2;

            findMaxCommonSubsequence(word1, word2);
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 5) { //print bag
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
        else {  // exception
            cout << "/---------------------------------------------------------------/\n" << endl;
            cout << "\nНеверный выбор. Попробуйте еще раз.\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
    }

    return 0;
}
