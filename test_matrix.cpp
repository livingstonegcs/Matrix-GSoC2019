#define BOOST_TEST_MODULE matrix_test_cases
#include <boost/test/included/unit_test.hpp>
#include <boost/variant.hpp>

#include <chrono> //For measuring execution time
#include "matrix_header.hpp" // Custom header file for matrix

BOOST_AUTO_TEST_SUITE (test_suite1)

BOOST_AUTO_TEST_CASE(addition_subtraction_test){
  int rows = 1000, columns = 1000;
  int val1 = 0, val2 = 1;

  //Created matrix size(100 X 100) with elements=0
  matrix::matrix<int> A(rows, columns, val1);
  //Created matrix size(100 X 100) with elements=1
  matrix::matrix<int> B(rows, columns, val2);

  //CHECKING initialization
  BOOST_CHECK(A.rows()==rows && A.columns()==columns);
  BOOST_CHECK(B.rows()==rows && B.columns()==columns);

  //CHECKING OPERATION +
  auto start = std::chrono::high_resolution_clock::now();

  auto result = A + B;

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(+ operator) Addition of 2 (1000 x 1000) matrices done in: "<< duration.count() <<" milliseconds.\n";

  for(int c_i=0;c_i<rows;c_i++)
    for(int c_j=0;c_j<columns;c_j++)
      BOOST_CHECK(val1+val2 == result[c_i][c_j]);

  //CHECKING OPERATION -
  start = std::chrono::high_resolution_clock::now();
  result = A - B;
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(- operator) Subtraction of 2 (1000 x 1000) matrices done in: "<< duration.count() <<" milliseconds.\n";

  for(int c_i=0;c_i<rows;c_i++)
    for(int c_j=0;c_j<columns;c_j++)
      BOOST_CHECK(val1-val2 == result[c_i][c_j]);

  //CHECKING OPERATION +=
  start = std::chrono::high_resolution_clock::now();
  B += B;
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(+= operator) Addition and self assignment of 2 (1000 x 1000) matrices done in: "<< duration.count() <<" milliseconds.\n";

  for(int c_i=0;c_i<rows;c_i++)
    for(int c_j=0;c_j<columns;c_j++)
      BOOST_CHECK(val2+val2 == B[c_i][c_j]);

  //CHECKING OPERATION -
  start = std::chrono::high_resolution_clock::now();
  A -= B;
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(-= operator) Subtraction and self assignment of 2 (1000 x 1000) matrices done in: "<< duration.count() <<" milliseconds.\n";

  for(int c_i=0;c_i<rows;c_i++)
    for(int c_j=0;c_j<columns;c_j++)
      BOOST_CHECK(val1-2*val2 == A[c_i][c_j]);
}

BOOST_AUTO_TEST_CASE(corresponding_multiplication_test){
  int rows = 1000, columns = 1000;
  int val1 = 5, val2 = 45;

  //Created matrix size(1000 X 1000) with elements=0
  matrix::matrix<int> A(rows, columns, val1);
  //Created matrix size(1000 X 1000) with elements=1
  matrix::matrix<int> B(rows, columns, val2);

  //CHECKING initialization
  BOOST_CHECK(A.rows()==rows && A.columns()==columns);
  BOOST_CHECK(B.rows()==rows && B.columns()==columns);

  //CHECKING OPERATION *
  auto start = std::chrono::high_resolution_clock::now();

  auto result = A * B;

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(* operator) Corresponding element Multiplication of 2 (1000 x 1000) matrices done in: "<< duration.count() <<" milliseconds.\n";

  for(int c_i=0;c_i<rows;c_i++)
    for(int c_j=0;c_j<columns;c_j++)
      BOOST_CHECK(val1*val2 == result[c_i][c_j]);

  //CHECKING OPERATION *=
  start = std::chrono::high_resolution_clock::now();
  B *= A;
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(*= operator) Corresponding element Multiplication and self assignment of 2 (1000 x 1000) matrices done in: "<< duration.count() <<" milliseconds.\n";

  for(int c_i=0;c_i<rows;c_i++)
    for(int c_j=0;c_j<columns;c_j++)
      BOOST_CHECK(val1*val2 == B[c_i][c_j]);
}

BOOST_AUTO_TEST_CASE(standard_matrix_multiplication_test){
  int r1 = 100, c1 = 200;
  int r2 = 200, c2 = 150;
  int val1 = 5, val2 = 45;

  //Created matrix size(r1 X c1) with elements=val1
  matrix::matrix<int> A(r1, c1, val1);
  //Created matrix size(r2 X c2) with elements=val2
  matrix::matrix<int> B(r2, c2, val2);

  //CHECKING initialization
  BOOST_CHECK(A.rows()==r1 && A.columns()==c1);
  BOOST_CHECK(B.rows()==r2 && B.columns()==c2);

  //CHECKING OPERATION ^ standard matrix multiplication
  auto start = std::chrono::high_resolution_clock::now();

  auto result = A ^ B;

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(^ operator) Matrix Multiplication of (100 x 200) and (200 x 150) matrices done in: "<< duration.count() <<" milliseconds.\n";

  //checking for correctness of dimension
  BOOST_CHECK(result.rows()==r1 && result.columns()==c2);


  //CHECKING OPERATION *=
  start = std::chrono::high_resolution_clock::now();
  A ^= B;
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout<< "(^= operator) Matrix Multiplication and self assignment of (100 x 200) and (200 x 150) matrices done in: "<< duration.count() <<" milliseconds.\n";

  //CHECKING Changed dimension of A
  BOOST_CHECK(A.rows() == r1 && A.columns()==c2);
}

BOOST_AUTO_TEST_CASE(demonastrable_test){
  std::cout<<"\nDemonstrable Test Case:\n";
  auto start = std::chrono::high_resolution_clock::now();

  matrix::matrix<int> A(2, 3);
  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[1][0] = 4;
  A[1][1] = 5;
  A[1][2] = 6;
  std::cout<<"Matrix A:\n"<<A;
  matrix::matrix<float> B(3, 2);
  B[0][0] = 5.0f;
  B[0][1] = 4.0f;
  B[1][0] = 3.0f;
  B[1][1] = 2.0f;
  B[2][0] = 1.0f;
  B[2][1] = 0.0f;
  std::cout<<"\nMatrix B:\n"<<B;

  matrix::matrix<float> C(2,2);
  C[0][0]=14.0f;
  C[0][1]=8.0f;
  C[1][0]=1.0f;
  C[1][1]=26.0f;

  std::cout<<"\nMatrix C:\n"<<C;

  matrix::matrix<float> D(2,2);
  D[0][0]=4.0f;
  D[0][1]=6.0f;
  D[1][0]=11.0f;
  D[1][1]=6.0f;

  std::cout<<"\nMatrix D:\n"<<D;

  std::cout<<"\nAddition A + A:\n"<< A + A;

  std::cout<<"\nAddition C - D:\n"<< C - D;

  std::cout<<"\nMultiplication C * D : \n"<< C * D;

  std::cout<<"\nMatrix Multiplication A ^ B\n"<< (A ^ B);

  auto result = (A ^ B) + C - D;

  std::cout<<"Expression (A ^ B) + C - D :\n"<< result <<"\n";

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout<< "The demonastrable initialization and operations are done in: "<< duration.count() <<" microseconds.\n";

}
BOOST_AUTO_TEST_SUITE_END()
