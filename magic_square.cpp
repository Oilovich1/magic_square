#include "magic_square.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
#include <random>

bool isValidSquare(const std::vector<std::vector<int>>& square) {
    if (square.empty()) {
        std::cerr << "Ошибка: Квадрат пуст (0 строк).\n";
        return false;
    }

    size_t expectedCols = square[0].size();

    if (square.size() != expectedCols) {
        std::cerr << "Ошибка: Количество строк (" << square.size() << ") не равно количеству столбцов (" << expectedCols << ").\n";
        return false;
    }

    for (size_t i = 1; i < square.size(); ++i) {
        if (square[i].size() != expectedCols) {
            std::cerr << "Ошибка: Строка " << i << " имеет длину " << square[i].size()  << ", ожидалось " << expectedCols << ".\n";
            return false;
        }
    }

    return true;
}

std::vector<std::vector<int>> generateMagicSquare(int n) {
    if (n <= 0 || n % 2 == 0) {
        std::cout << "Ошибка: введеное число должно быть положительным нечетным." << std::endl;
        return std::vector<std::vector<int>>{};
    }

    std::vector<std::vector<int>> square(n, std::vector<int>(n, 0));

    int num = 1;
    int row = 0;
    int col = n / 2;

    while (num <= n * n) {
        square[row][col] = num;

        int next_row = row - 1;
        int next_col = col + 1;

        // Применяем "граничные условия" для выхода за пределы сетки
        if (next_row < 0) {
            next_row = n - 1;
        }
        if (next_col >= n) {
            next_col = 0;
        }

        // Если следующая ячейка занята, идём вниз от текущей
        if (square[next_row][next_col] != 0) {
            row = (row + 1) % n;
            col = col;
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
    if (!isValidSquare(square)) {
        std::cout << "Ошибка: Получен некорректный квадрат. Операция не может быть выполнена.\n";
        return std::vector<std::vector<int>>{};
    }
    int n = square.size();
    std::vector<std::vector<int>> rotated_square(n, std::vector<int>(n));

    // Поворот на 90 градусов по часовой стрелке
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotated_square[j][n - 1 - i] = square[i][j];
        }
    }
   
    return rotated_square;
}

std::vector<std::vector<int>> reflectSquare(const std::vector<std::vector<int>>& square, int diagonal) {
    if (!isValidSquare(square)) {
        std::cout << "Ошибка: Получен некорректный квадрат. Операция не может быть выполнена.\n";
        return std::vector<std::vector<int>>{};
    }
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
    return reflected_square;
}

bool isMagicSquare(const std::vector<std::vector<int>>& square) {
    if (!isValidSquare(square)) {
        std::cout << "Ошибка: Получен некорректный квадрат. Операция не может быть выполнена.\n";
        return false;
    }
    int n = square.size();

    int target_sum = std::accumulate(square[0].begin(), square[0].end(), 0);

    // Проверка сумм строк
    for (int i = 0; i < n; i++) {
        int row_sum = std::accumulate(square[i].begin(), square[i].end(), 0);
        if (row_sum != target_sum)
            return false;
    }

    // Проверка сумм столбцов
    for (int j = 0; j < n; ++j) {
        int col_sum = 0;
        for (int i = 0; i < n; ++i) {
            col_sum += square[i][j];
        }
        if (col_sum != target_sum) {
            return false;
        }

    }

    // Проверка сумм диагоналей
    int diag1_sum = 0;
    int diag2_sum = 0;
    for (int i = 0; i < n; ++i) {
        diag1_sum += square[i][i]; // Главная диагональ
        diag2_sum += square[i][n - 1 - i]; // Побочная диагональ
    }
    if (diag1_sum != target_sum || diag2_sum != target_sum) {
        return false;
    }

    // Проверка уникальности чисел от 1 до n*n
    std::set<int> numbers;
    int expected_max = n * n;

    for (const auto& row : square) {
        for (int num : row) {
            if (num < 1 || num > expected_max) {
                return false;
            }
            if (!numbers.insert(num).second) {
                return false;
            }
        }
    }
    if (static_cast<int>(numbers.size()) != expected_max) {
        return false;
    }
    return true;
}

std::vector<int> getRowSums(const std::vector<std::vector<int>>& square) {
    if (!isValidSquare(square)) {
        std::cout << "Ошибка: Получен некорректный квадрат. Операция не может быть выполнена.\n";
        return std::vector<int>{};
    }
    std::vector<int> rowSums;
    rowSums.reserve(square.size());

    for (const auto& row : square) {
        int sum = std::accumulate(row.begin(), row.end(), 0);
        rowSums.push_back(sum);
    }

    return rowSums;
}

std::vector<int> getColSums(const std::vector<std::vector<int>>& square) {
    if (!isValidSquare(square)) {
        std::cout << "Ошибка: Получен некорректный квадрат. Операция не может быть выполнена.\n";
        return std::vector<int>{};
    }
    int n = square.size();

    std::vector<int> colSums(n, 0);

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            colSums[j] += square[i][j];
        }
    }

    return colSums;
}

std::pair<int, int> getDiagonalSums(const std::vector<std::vector<int>>& square) {
    if (!isValidSquare(square)) {
        std::cout << "Ошибка: Получен некорректный квадрат. Операция не может быть выполнена.\n";
        return {0,0};
    }
    int n = square.size();
    int diag1_sum = 0;
    int diag2_sum = 0;

    for (int i = 0; i < n; ++i) {
        diag1_sum += square[i][i];
        diag2_sum += square[i][n - 1 - i];
    }

    return std::make_pair(diag1_sum, diag2_sum);
}

int generateRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    return dis(gen);
}