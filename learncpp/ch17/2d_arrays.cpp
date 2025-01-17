#include <array>
#include <iostream>
#include <mdspan>

// An alias template for a two-dimensional std::array.
// Note dimensions are switched because of the way templates get nested.
template<typename T, std::size_t Row, std::size_t Col> using Array2d = std::array<std::array<T, Col>, Row>;

// Fetch the number of rows from the Row non-type template parameter
template<typename T, std::size_t Row, std::size_t Col>
constexpr int rowLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
  return Row;
}

// Fetch the number of cols from the Col non-type template parameter
template<typename T, std::size_t Row, std::size_t Col>
constexpr int colLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
  return Col;
}

// When using Array2d as a function parameter, we need to respecify the template parameters
template<typename T, std::size_t Row, std::size_t Col> void printArray(const Array2d<T, Row, Col>& arr)
{
  for (const auto& arow : arr) // get each array row
  {
    for (const auto& e : arow) // get each element of the row
      std::cout << e << ' ';

    std::cout << '\n';
  }
}

int main()
{
  // Define a two-dimensional array of int with 3 rows and 4 columns. We need double braces.
  Array2d<int, 3, 4> arr{ {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 },
  } };

  printArray(arr);

  std::cout << arr[1][2];

  std::cout << "Rows: " << arr.size() << '\n'; // get length of first dimension (rows)
  std::cout << "Cols: " << arr[0].size()
            << '\n'; // get length of second dimension (cols), UB if length of first dimension is zero

  // A better way to get the length (from type)
  std::cout << "Rows: " << rowLength(arr) << '\n'; // get length of first dimension (rows)
  std::cout << "Cols: " << colLength(arr) << '\n'; // get length of second dimension (cols)

  // // // // // // // // // // // // // // // // // //

  /*
  (C++23) std::mdspan is a modifiable view that provides a multidimensional array interface for a contiguous sequence of
  elements -- if the underlying sequence of elements is non-const, those elements can be modified.
  */

  std::array arr2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

  // Define a two-dimensional span into our one-dimensional array. We must pass std::mdspan a pointer to the sequence of
  // elements which we can do via the data() member function of std::array or std::vector
  std::mdspan mdView{ arr2.data(), 3, 4 };

  // print array dimensions
  // std::mdspan calls these extents
  std::size_t rows{ mdView.extents().extent(0) };
  std::size_t cols{ mdView.extents().extent(1) };
  std::cout << "Rows: " << rows << '\n';
  std::cout << "Cols: " << cols << '\n';

  // print array in 1d
  // The data_handle() member gives us a pointer to the sequence of elements which we can then index
  for (std::size_t i = 0; i < mdView.size(); ++i) std::cout << mdView.data_handle()[i] << ' ';
  std::cout << '\n';

  // print array in 2d
  // We use multidimensional [] to access elements (added in C++23)
  for (std::size_t row = 0; row < rows; ++row) {
    for (std::size_t col = 0; col < cols; ++col) std::cout << mdView[row, col] << ' ';
    std::cout << '\n';
  }
  std::cout << '\n';

  return 0;
}