#include "magic_square.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

std::vector<std::vector<int>> generateMagicSquare(int n) {
    if (n <= 0 || n % 2 == 0) {
        std::cout << "Ошибка: введеное число должно быть положительным нечетным." << std::endl;
        return std::vector<std::vector<int>>();
    }

    std::vector<std::vector<int>> square(n, std::vector<int>(n, 0));

    int num = 1;
    int row = 0;
    int col = n / 2;

    while (num <= n * n) {
        square[row][col] = num;

        int next_row = row - 1;
        int next_col = col + 1;

        if (next_row < 0) {
            next_row = n - 1;
        }
        if (next_col >= n) {
            next_col = 0;
        }

        if (square[next_row][next_col] != 0) {
            // Если следующая ячейка занята, следующее число помещается под текущим.
            row = (row + 1) % n; // Смещаемся вниз, используя модуль для обработки границы
            col = col;           // Столбец не меняется
        }
        else {
            row = next_row;
            col = next_col;
        }

        num++;
    }

    return square;
}

std::vector<std::vector<int>> rotateSquare(const std::vector<std::vector<int>>& square) {
    int n = square.size();
    std::vector<std::vector<int>> rotated_square(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotated_square[j][n - 1 - i] = square[i][j];
        }
    }
   
    return rotated_square;
}

std::vector<std::vector<int>> reflectSquare(const std::vector<std::vector<int>>& square, int diagonal) {
    int n = square.size();
    std::vector<std::vector<int>> reflected_square(n, std::vector<int>(n));
    for (int i = 0;i<n;i++){
        for (int j = 0; j<n;j++){
            if (diagonal == 0) {// отражение по главной диагонали
                reflected_square[j][i] = square[i][j];
            }
            else {//отражение по побочной диагонали
                reflected_square[n - 1 - j][n - 1 - i] = square[i][j];
            }
        }
    }
}

bool isMagicSquare(const std::vector<std::vector<int>>& square) {
    int n = square.size();

    int target_sum = std::accumulate(square[0].begin(), square[0].end(), 0);

    for (int i = 0; i < n; i++) {
        int row_sum = std::accumulate(square[i].begin(), square[i].end(), 0);
        if (row_sum != target_sum)
            return false;
    }
    for (int j = 0; j < n; ++j) {
        int col_sum = 0;
        for (int i = 0; i < n; ++i) {
            col_sum += square[i][j];
        }
        if (col_sum != target_sum) {
            return false;
        }

    }
    int diag1_sum = 0;
    int diag2_sum = 0;
    for (int i = 0; i < n; ++i) {
        diag1_sum += square[i][i]; // Главная диагональ
        diag2_sum += square[i][n - 1 - i]; // Побочная диагональ
    }
    if (diag1_sum != target_sum || diag2_sum != target_sum) {
        return false;
    }
    return true;
}

