# Matrix Library:
## This is an implementation of generic matrix library in cpp. 

It contains two programs:
- LIBRARY HEADER
- TEST PROGRAM

```To see the demonstration run the test file by executing "g++ -std=c++11 test_matrix.cpp"```

---
#### 1. LIBRARY: `matrix_header.hpp` contains the implementation of the library under the namespace `matrix`
- **Creation/Declaration of a matrix** 
  - Declaration Prototype 1: `matrix::matrix< type_name > mat_name(num_rows, num_cols)`
  
    >Eg: `matrix::matrix<int> mat1(3,3)` :
    This will create a matrix named "mat1" with rows = 3 and columns = 3
    
  - Declaration Prototype 2: `matrix::matrix< type_name > mat_name(num_rows, num_cols, init_value)`
  
    >Eg: `matrix::matrix<int> mat1(3,3, -3)` :
    This will create a matrix named "mat1" with rows = 3 and columns = 3 with all element values equal to -3
  ---
- **Operators overloaded and their usage in matrix class**  
  - `[]` Makes matrix class accessible as a normal matrix by indexing
  - `=`  Assign matrix directly to a variable
  - `+`  Adds two matrix instances
  - `-` Subtracts two matrix instances
  - `*` Multiplies two matrix instances (It is corresponding elementwise multiplication)
  - `+=` Adds matrix instance to self
  - `-=` Subtracts matrix instance from self
  - `^` Performs standard matrix multiplication between two matrix instances
  - `^=` Performs standard matrix multiplication with self and stores the value
  - `<<` Outputs the matrices as each row in newline and each column element of a row separated by spaces
  ---
- **Additional Functionalities implemented** 
  - FLEXIBLE DATATYPE: A matrix if gets multiplied by another matrix it changes the datatype to the highest attainable datatype:
    >Eg: Operation between `matrix<double>` and `matrix<int>` will give a `matrix<long>` and accordingly the datatype will be calculated
  - Dimension malleable on the `^=` operation: The dimension of a matrix can change for matrix multiplication and self assignment under this operator.
    >If a matrix A of dimension (2, 3) undergoes matrix multiplication with B of dimension(3, 5) and self assignment then matrix A will attain dimension (2, 5)
  
---
#### 2. TEST PROGRAM : `test_matrix.cpp` contains the auto testing of the `matrix_header` library.
 - It is prepared with boost auto test environment and measures the time for every operation.
 ```Running 4 test cases...
(+ operator) Addition of 2 (1000 x 1000) matrices done in: 52 milliseconds.
(- operator) Subtraction of 2 (1000 x 1000) matrices done in: 50 milliseconds.
(+= operator) Addition and self assignment of 2 (1000 x 1000) matrices done in: 51 milliseconds.
(-= operator) Subtraction and self assignment of 2 (1000 x 1000) matrices done in: 49 milliseconds.
(* operator) Corresponding element Multiplication of 2 (1000 x 1000) matrices done in: 51 milliseconds.
(*= operator) Corresponding element Multiplication and self assignment of 2 (1000 x 1000) matrices done in: 52 milliseconds.
(^ operator) Matrix Multiplication of (100 x 200) and (200 x 150) matrices done in: 124 milliseconds.
(^= operator) Matrix Multiplication and self assignment of (100 x 200) and (200 x 150) matrices done in: 124 milliseconds.

Demonstrable Test Case:
Matrix A:
1 2 3
4 5 6
Matrix B:
5 4
3 2
1 0
Matrix C:
14  8
 1 26
Matrix D:
 4  6
11  6
Addition A + A:
 2  4  6
 8 10 12
Addition C - D:
 10   2
-10  20
Multiplication C * D : 
 56  48
 11 156
Matrix Multiplication A ^ B
14  8
41 26Expression (A ^ B) + C - D :
24 10
31 46
The demonastrable initialization and operations are done in: 368 microseconds.

*** No errors detected
```
 
  
