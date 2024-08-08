## **FQ-MATRIX** - A matrix library implemented in C language

> This matrix library is implemented by referring to [glMatrix](https://glmatrix.net/docs/index.html)

If you are a geek and you want to pursue extreme performance, then this library may not be suitable for you. Maybe you need GSL, BLAS/LAPACK.

If you are a beginner and are learning graphics related knowledge. Then this library may help you. Because the function implementation of this library is simple and easy to understand, and there will be a relatively complete derivation process for all functions.

#### Compile
We use [cmake](https://cmake.org/) to compile code. Please make sure you have cmake installed on your computer

```
./clear.sh
./cbuild.sh
```

The compilation results are stored in the **lib/** folder

#### Unit test
We use [CuTest](https://cutest.sourceforge.net/) to manage/execute test cases.
1. Execute the following shell in sequence. The compilation results are stored in the **bin/** folder.
```javascript
./clear.sh
./cbuild.sh
./ctest.sh
```

2. Then execute the following shell.

```
./bin/FQ_MATRIX_CTEST
```

#### Contribute

Welcome to contribute for any features/docs/bugs. when you  contribute your code, you need to add and execute complete test cases.
We use [CuTest](https://cutest.sourceforge.net/) to manage/execute test cases, which is a **Small** and **Easy to Deploy** unit testing library. Here are some instructions for how to add unit test cases: 

- Test files correspond to source files one by one. For example, if there is a source file named *fq_matrix.c* in the ```src/``` folder, then there must be a corresponding test file named *test_fq_matrix.c* in the ```test/``` folder.

- Test functions are named in the format of **test_XXX_base** or **test_XXX_edge**. For example, *test_mat_create_base* is a test case for the function mat_create.

- If you find a new test case, you need create a new function in the form of **test_XXX_YYY**. For example, *test_mat_create_withzero* is a test case for the function mat_create in fq_matrix.c with fill = 0.0.

- Finally, you need to add new test cases to the suite. such as:
```SUITE_ADD_TEST(suite, test_mat_create_withzero);```

> You can refer to the test cases in test/test_fq_matrix.c for details.

#### version history

- 2024-08-04 init project
