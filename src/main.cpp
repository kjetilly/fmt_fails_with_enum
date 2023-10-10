#include <fmt/format.h>
#include <fmt/core.h>
#include <iostream>

template<int ROWS, int COLS>
struct FieldMatrix {
    enum {
      //! The number of rows.
      rows = ROWS,
      //! The number of columns.
      cols = COLS
    };
};

template<int ROWS, int COLS>
struct FieldMatrixModernCPP {
      //! The number of rows.
  static constexpr int rows = ROWS;
      //! The number of columns.
  static constexpr int cols = COLS;
};


template<class Matrix>
struct BlockMatrix {
  using block_type = Matrix;
};

template<class Matrix>
void printmatrixcompiles(const Matrix& m) {
  std::cout << fmt::format("Rows are {}", int(Matrix::block_type::rows)) << std::endl;
}

template<class Matrix>
void printmatrixdoesnotcompile(const Matrix& m) {
  std::cout << fmt::format("Rows are {}", Matrix::block_type::rows) << std::endl;
}


int main(int, char**) {
  BlockMatrix<FieldMatrix<1, 1>> matrix_enum;
  printmatrixcompiles(matrix_enum);
  printmatrixdoesnotcompile(matrix_enum);

  
  BlockMatrix<FieldMatrixModernCPP<1, 1>> matrix;
  printmatrixcompiles(matrix);
  printmatrixdoesnotcompile(matrix);
  return 0;
}


