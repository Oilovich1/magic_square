#include <vector>
#include <array>
bool isValidSquare(const std::vector<std::vector<int>>& square);
std::vector<std::vector<int>> generateMagicSquare(int n);
std::vector<std::vector<int>> rotateSquare(const std::vector<std::vector<int>>& square);
std::vector<std::vector<int>> reflectSquare(const std::vector<std::vector<int>>& square, int diagonal);
bool isMagicSquare(const std::vector<std::vector<int>>& square);
std::vector<int> getRowSums(const std::vector<std::vector<int>>& square);
std::vector<int> getColSums(const std::vector<std::vector<int>>& square);
std::array<int,2> getDiagonalSums(const std::vector<std::vector<int>>& square);
int generateRandomNumber(int min, int max);