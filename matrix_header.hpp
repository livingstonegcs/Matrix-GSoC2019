#include<vector>
#include<stdexcept>
#include<sstream>
#include<iomanip>

namespace matrix{
  template<typename T>
  class matrix{
    std::vector< std::vector< T > > matrix__;
    size_t rows__;
    size_t cols__;
  public:
   //Constructor for initilizing with no. of rows and no. of columns.
    matrix(size_t rows_arg, size_t cols_arg){
      rows__ = rows_arg;
      cols__ = cols_arg;
      matrix__.resize(rows__);
      for(size_t c_i = 0; c_i < rows__; c_i++)
      matrix__[c_i].resize(cols__);
    }
    //Basic Constructor
    matrix(){
      rows__ = 0 ; cols__ = 0;
    }
    //Constructor with an initialization value called init_value
    matrix(size_t rows_arg, size_t cols_arg, T init_val){
      rows__ = rows_arg;
      cols__ = cols_arg;
      matrix__.resize(rows__);
      for(size_t c_i = 0; c_i < rows__; c_i++)
      matrix__[c_i].resize(cols__);
      for(size_t c_row = 0; c_row < rows__; c_row++)
        for(size_t c_col = 0; c_col < cols__; c_col++)
          matrix__[c_row][c_col] = init_val;
    }

    //Functions to get the no. of rows and no. of columns.
    size_t rows(){ return rows__;}
    size_t columns(){return cols__;}

    //Overloading and defining the [] operator to access the matrix class as a normal index-based matrix.
    std::vector< T >& operator[](size_t ith_row){
      return matrix__[ith_row];
    }

    //Overloading and defining the = operator for assignment of matrices
    template<class T2>
     matrix& operator=(matrix<T2> mat2){
      //if(this==&mat2) return *this;
      matrix__.clear();
      matrix__.resize(mat2.rows());
      rows__ = mat2.rows();
      cols__ = mat2.columns();
      for(int c_row = 0; c_row < rows__ ; c_row++)
        for(int c_col = 0; c_col< cols__ ; c_col++)
            matrix__[c_row].push_back(mat2[c_row][c_col]);

      return *this;
    }
  };

  //Overloading and defining the + operator for the matrix class
  template<class T1, class T2>
  auto operator+(matrix <T1> mat1, matrix <T2> mat2) -> matrix<decltype(T1{} + T2{})>{
    if(mat1.rows() == mat2.rows() && mat1.columns() == mat2.columns()){

      matrix< decltype(T1{} + T2{})> mat3(mat1.rows(), mat1.columns());

      for(size_t c_row=0; c_row<mat1.rows(); c_row++){
        for(size_t c_col=0; c_col<mat1.columns();c_col++){
            mat3[c_row][c_col] = mat1[c_row][c_col]+mat2[c_row][c_col];
        }
      }
      return mat3;
    }
    throw std::runtime_error("Conflict for addition in matching the dimensions of the matrices");
  }

  //Overloading and defining the += operator for the matrix class
  template<class T1, class T2>
  void operator+=(matrix<T1> &mat1, matrix<T2> mat2){
    mat1 = operator+(mat1, mat2);
  }

  //Overloading and defining the - operator for the matrix class
  template<class T1, class T2>
  auto operator-(matrix <T1> mat1, matrix <T2> mat2) -> matrix<decltype(T1{} + T2{})>{
    if(mat1.rows() == mat2.rows() && mat1.columns() == mat2.columns()){

      matrix< decltype(T1{} + T2{})> mat3(mat1.rows(), mat1.columns());

      for(size_t c_row=0; c_row<mat1.rows(); c_row++){
        for(size_t c_col=0; c_col<mat1.columns();c_col++){
            mat3[c_row][c_col] = mat1[c_row][c_col]-mat2[c_row][c_col];
        }
      }
      return mat3;
    }
    throw std::runtime_error("Conflict for subtraction in matching the dimensions of the matrices");
  }

  //Overloading and defining the -= operator for the matrix class
  template<class T1, class T2>
  void operator-=(matrix<T1> &mat1, matrix<T2> mat2){
    mat1 = operator-(mat1, mat2);
  }

  //Overloading and defining the * operator for the matrix class
  template<class T1, class T2>
  auto operator*(matrix <T1> mat1, matrix <T2> mat2) -> matrix<decltype(T1{} * T2{})>{
    if(mat1.rows() == mat2.rows() && mat1.columns() == mat2.columns()){

      matrix< decltype(T1{} + T2{})> mat3(mat1.rows(), mat1.columns());

      for(size_t c_row=0; c_row<mat1.rows(); c_row++){
        for(size_t c_col=0; c_col<mat1.columns();c_col++){
            mat3[c_row][c_col] = mat1[c_row][c_col]*mat2[c_row][c_col];
        }
      }
      return mat3;
    }
    throw std::runtime_error("Conflict for multiplication in matching the dimensions of the matrices");
  }

  //Overloading and defining the *= operator for the matrix class
  template<class T1, class T2>
  void operator*=(matrix<T1> &mat1, matrix<T2> mat2){
    mat1 = operator*(mat1, mat2);
  }

  //Overloading and defining standard matrix multiplication by using the ^ operator for the matrix class.
  template<class T1, class T2>
  auto operator^(matrix <T1> mat1, matrix <T2> mat2) -> matrix<decltype(T1{}*T2{})>{
    if(mat1.columns() == mat2.rows()){
      matrix< decltype(T1{}*T2{})> mat3(mat1.rows(), mat2.columns());

      for(size_t c_row=0; c_row<mat3.rows(); c_row++){
        for(size_t c_col=0; c_col<mat3.columns();c_col++){
          mat3[c_row][c_col]=0;

          for(size_t c_i=0; c_i<mat1.columns(); c_i++){
            mat3[c_row][c_col] += mat1[c_row][c_i]*mat2[c_i][c_col];
          }
        }
      }
      return mat3;
    }
    throw std::runtime_error("Conflict for multiplication in matching the dimensions of the matrices");
  }

  //Overloading and defining ^= operator for the matrix class
  template<class T1, class T2>
  void operator^=(matrix<T1> &mat1, matrix<T2> mat2){
    mat1 = operator^(mat1, mat2);
  }

  //Overloading and << operator for output stream
  //[This is Referred from an open implementation]
  template<typename T>
  std::ostream& operator<<(std::ostream& os, matrix<T> m){
    size_t maximum_entry_length = 0;
    for (size_t row = 0; row < m.rows(); ++row){
      for (size_t col = 0; col < m.columns(); ++col){
        std::stringstream ss;
        ss << m[row][col];
        std::string entry_text;
        ss >> entry_text;
        maximum_entry_length = std::max(maximum_entry_length, entry_text.length());
        }
      }

      for (size_t row = 0; row < m.rows(); ++row){
        for (size_t col = 0; col < m.columns(); ++col){
          os << std::setw((int) maximum_entry_length) << m[row][col];

          if (col < m.columns() - 1){
            os << ' ';
          }
        }

        if (row < m.rows() - 1){
          os << '\n';
        }
      }
      return os;
    }
}
