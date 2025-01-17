#include <iostream>

int main()
{

  int array[3][5]{
    { 1, 2 }, // row 0 = 1, 2, 0, 0, 0
    { 6, 7, 8 }, // row 1 = 6, 7, 8, 0, 0
    { 11, 12, 13, 14 } // row 2 = 11, 12, 13, 14, 0
  };

  // leftmost length can be omited
  int array2[][5]{
    { 1, 2, 3, 4, 5 },
    { 6, 7, 8, 9, 10 },
    { 11, 12, 13, 14, 15 },
  };

  int array3[3][5]{};

  // // // // // // // // // // // // // // // // // // // //

  constexpr int numRows{ 10 };
  constexpr int numCols{ 10 };

  // Declare a 10x10 array
  int product[numRows][numCols]{};

  // Calculate a multiplication table. We don't need to calc row and col 0 since mult by 0 always is 0.
  for (std::size_t row{ 1 }; row < numRows; ++row) {
    for (std::size_t col{ 1 }; col < numCols; ++col) { product[row][col] = static_cast<int>(row * col); }
  }

  for (std::size_t row{ 1 }; row < numRows; ++row) {
    for (std::size_t col{ 1 }; col < numCols; ++col) { std::cout << product[row][col] << '\t'; }

    std::cout << '\n';
  }

  return 0;
}