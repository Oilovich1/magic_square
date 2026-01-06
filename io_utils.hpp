#include <vector>
#include <string>
void setupConsole();
int getUserChoice();
int getOddSize();
void displayMenu();
void printSquareWithDelay(const std::vector<std::vector<int>>& square, int delay_ms = 250);
bool readSquareFromFile(const std::string& filename, std::vector<std::vector<int>>& matrix);