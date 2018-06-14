/**
@file   hw4.cpp

@author Danny Brown (dmb0057)
@version 02-25-2018 21:15

@section DESCRIPTION

A program that merges the numbers in two files and writes all the numbers into a
third file. The program takes input from two different files and writes its
output to a third file. Each input file contains a list of numbers of type int
in sorted order from the smallest to the largest. After the program is run, the
output file will contain all the numbers in the two input files in one longer
list in sorted order from smallest to largest.

To compile, you will need to use g++ in a Linux terminal with C++11.
i.e. "g++ -o hw4 hw4.cpp -std=c++0x" or "g++ -o hw4 hw4.cpp -std=c++11".
note: I used the former to compile my source code and it worked as desired.
If errors occurs during testing, be sure that the provided test files are in the
current directory.

http://www.cplusplus.com/ was used for more information on arrays and sorting.

*/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 1000; // the maximum size of the list

// -----------------------Function Prototypes-------------------------
// Used to pause console
void pause(void);
void makeArrays(void);
// Input: (1) Array storing data retrieved from the file (i.e., instream)
//        (2) input file stream object
// Output: Size of array.
int getArrayLength(int inputArray[], ifstream &inStream);
// Test driver for getArrayLength()
void test_getArrayLength(void);
// Test driver for sort()
void test_arraySorting(void);
// Test driver 1 for makeArrays()
void test_makeArrays1(void);
// Test driver 2 for makeArrays()
void test_makeArrays2(void);
//--------------------------------------------------------------------

/**
@brief Helper function used to pause console.

@param none.
@return void.
*/
void pause(void) {
  cout << "Press any key to continue...";
  cin.ignore().get();
}

/**
@brief The bulk of program operations. Takes files and converts the
integers contained in those files into 2 integer arrays. The function
then concatenates those arrays into a 3rd, in which that third array of
integers is then written to an output file.

@param none.
@return void.
*/
void makeArrays(void) {
  //----------------------- First File Operations-----------------------------

  ifstream inStreamFirst;

  string file1;

  int iArray1[MAX_SIZE];
  int iArray1_size;

  std::cout << "Enter the first input file name: ";
  std::cin >> file1;
  inStreamFirst.open(file1);
  if (!inStreamFirst.is_open()) {
    std::cerr << "\nError: File not found - " << file1 << endl;
    exit(EXIT_FAILURE);
  }
  iArray1_size = getArrayLength(iArray1, inStreamFirst);
  std::cout << "The list of " << iArray1_size << " numbers in file " << file1
            << " is:" << endl;
  for (int i = 0; i < iArray1_size; i++) {
    std::cout << iArray1[i] << '\n';
  }
  inStreamFirst.close();

  //----------------------- Second File Operations-----------------------------

  ifstream teststream2;

  string file2;

  int iArray2[MAX_SIZE];
  int iArray2_size;

  std::cout << "\nEnter the second input file name: ";
  std::cin >> file2;
  teststream2.open(file2);
  if (!teststream2.is_open()) {
    std::cerr << "\nError: File not found - " << file2 << endl;
    exit(EXIT_FAILURE);
  }
  iArray2_size = getArrayLength(iArray2, teststream2);
  std::cout << "The list of " << iArray2_size << " numbers in file " << file2
            << " is:" << endl;
  for (int j = 0; j < iArray2_size; j++) {
    std::cout << iArray2[j] << '\n';
  }
  teststream2.close();

  //----------------------- Third File Operations -----------------------------
  string file3;
  int count = iArray1_size + iArray2_size;
  int array3[count];
  copy(iArray1, iArray1 + iArray1_size, array3);
  copy(iArray2, iArray2 + iArray2_size, array3 + iArray1_size);
  std::cout << "\nThe sorted list of " << count << " numbers is: ";
  sort(array3, array3 + count);
  for (int l = 0; l < count; l++) {
    std::cout << array3[l] << ' ';
  }
  std::cout << "\nEnter the output file name: ";
  std::cin >> file3;
  ofstream newfile;
  newfile.open(file3);
  for (int m = 0; m < count; m++) {
    newfile << array3[m] << endl;
  }
  std::cout << "*** Please check the new file - " << file3 << " ***" << '\n';
}

/**
@brief Returns the length of the array after integers
are inserted by the file stream. Furthermore, that insertion
is also done in this function.

@param inputArray[] the array in question.
@param &inStream Input stream to operate on files.
@return index the length of the array.
*/
int getArrayLength(int inputArray[], ifstream &inStream) {
  int index = 0;
  inStream >> inputArray[index];
  while (!inStream.fail()) {
    index++;
    inStream >> inputArray[index];
  }
  return index;
}

/**
@brief Test whether of not the length of the array is in direct proportion
to the amount of integers in a given file. If errors occur, be sure that the
test files are in the current directory.

@param none.
@return void.
*/
void test_getArrayLength(void) {
  std::cout << "Unit Test Case 1: Function Name - getArrayLength()." << '\n';
  std::cout
      << "\tCase 1.1: Testing if array lenth == actual number of integers (5)"
      << '\n';
  ifstream teststream;
  int testArray[MAX_SIZE];
  int testArray_Size;
  teststream.open("testfile1.txt");
  if (!teststream.is_open()) {
    std::cerr << "\nError: File not found - "
              << "testfile1.txt" << endl;
    exit(EXIT_FAILURE);
  }
  testArray_Size = getArrayLength(testArray, teststream);
  teststream.close();
  assert(testArray_Size == 5);
  std::cout << "\tCase 1.1 passed." << '\n';

  std::cout
      << "\tCase 1.2: Testing if array lenth == actual number of integers (8)"
      << '\n';
  int testArray2[MAX_SIZE];
  int testArray2_Size;
  teststream.open("testfile2.txt");
  if (!teststream.is_open()) {
    std::cerr << "\nError: File not found - "
              << "testfile2.txt" << endl;
    exit(EXIT_FAILURE);
  }
  testArray2_Size = getArrayLength(testArray2, teststream);
  assert(testArray2_Size == 8);
  teststream.close();
  std::cout << "\tCase 1.2 passed." << '\n';

  std::cout
      << "\tCase 1.3: Testing if array lenth == actual number of integers (13)"
      << '\n';
  int testArray3[MAX_SIZE];
  int testArray3_Size;
  teststream.open("testfile3.txt");
  if (!teststream.is_open()) {
    std::cerr << "\nError: File not found - "
              << "testfile3.txt" << endl;
    exit(EXIT_FAILURE);
  }
  testArray3_Size = getArrayLength(testArray3, teststream);
  assert(testArray3_Size == 13);
  teststream.close();
  std::cout << "\tCase 1.3 passed." << '\n';

  std::cout
      << "\tCase 1.4: Testing if array is empty given empty file (no integers)"
      << '\n';
  int testArray4[MAX_SIZE];
  int testArray4_Size;
  teststream.open("testfile4.txt");
  if (!teststream.is_open()) {
    std::cerr << "\nError: File not found - "
              << "testfile4.txt" << endl;
    exit(EXIT_FAILURE);
  }
  testArray4_Size = getArrayLength(testArray4, teststream);
  assert(testArray4_Size == 0);
  teststream.close();
  std::cout << "\tCase 1.4 passed." << '\n';
  std::cout << "\t..." << '\n';
  pause();
}

/**
@brief Tests whether or not the test array is properly. If errors occur, be sure
that the test files are in the current directory.

@param none.
@return void.
*/
void test_arraySorting(void) {
  std::cout << "Unit Test Case 2: Function Name - sort()." << '\n';
  std::cout << "\tCase 2.1: Testing if array is properly sorted 1 " << '\n';
  ifstream teststream;
  int testArray[MAX_SIZE];
  int testArray_Size;
  teststream.open("unsorted1.txt");
  if (!teststream.is_open()) {
    std::cerr << "\nError: File not found - "
              << "unsorted1.txt" << endl;
    exit(EXIT_FAILURE);
  }
  testArray_Size = getArrayLength(testArray, teststream);
  sort(testArray, testArray + 5);
  assert(testArray[0] == 5);
  teststream.close();
  std::cout << "\tCase 2.1 passed." << '\n';

  std::cout << "\tCase 2.2: Testing if array is properly sorted 2 " << '\n';
  assert(testArray[2] == 7);
  std::cout << "\tCase 2.2 passed." << '\n';

  std::cout << "\tCase 2.3: Testing if array is properly sorted 3 " << '\n';
  assert(testArray[4] == 17);
  std::cout << "\tCase 2.3 passed." << '\n';
  std::cout << "\t..." << '\n';
  pause();
}

/**
@brief Performs several tests on the makeArrays() function.If errors occur, be
sure that the test files are in the current directory.

@param none.
@return void.
*/
void test_makeArrays1(void) {
  std::cout << "Unit Test Case 3: Function Name - makeArrays()." << '\n';
  std::cout << "\tCase 3.1: Testing if file stream is properly opened " << '\n';
  ifstream teststream;
  teststream.open("testfile1.txt");
  assert(teststream.is_open());
  std::cout << "\tCase 3.1 passed." << '\n';

  std::cout << "\tCase 3.2: Testing if file stream is properly closed " << '\n';
  teststream.close();
  assert(false == teststream.is_open());
  std::cout << "\tCase 3.2 passed." << '\n';
}

/**
@brief Performs several tests on the makeArrays() function.If errors occur, be
sure that the test files are in the current directory.

@param none.
@return void.
*/
void test_makeArrays2(void) {
  //----------------------- First File Operations-----------------------------

  ifstream teststream1;

  string file1;

  int testarray1[MAX_SIZE];
  int testarray1_size;

  teststream1.open("testfile1.txt");
  if (!teststream1.is_open()) {
    std::cerr << "\nError: File not found - "
              << "testfile1.txt" << endl;
    exit(EXIT_FAILURE);
  }
  testarray1_size = getArrayLength(testarray1, teststream1);
  teststream1.close();

  //----------------------- Second File Operations-----------------------------

  ifstream teststream2;

  int testarray2[MAX_SIZE];
  int testarray2_size;

  teststream2.open("testfile2.txt");
  if (!teststream2.is_open()) {
    std::cerr << "\nError: File not found - "
              << "testfile2.txt" << endl;
    exit(EXIT_FAILURE);
  }
  testarray2_size = getArrayLength(testarray2, teststream2);
  teststream2.close();

  //----------------------- Third File Operations -----------------------------
  string file3 = "finalfile.txt";
  int count = testarray1_size + testarray2_size;
  int testarray3[count];
  copy(testarray1, testarray1 + testarray1_size, testarray3);
  copy(testarray2, testarray2 + testarray2_size, testarray3 + testarray1_size);
  sort(testarray3, testarray3 + count);
  std::cout << "\tCase 3.3.1: Testing if final array is properly sorted 1 "
            << '\n';
  assert(testarray3[0] == 5);
  std::cout << "\tCase 3.3.1 passed." << '\n';
  std::cout << "\tCase 3.3.2: Testing if final array is properly sorted 2 "
            << '\n';
  assert(testarray3[12] == 32);
  std::cout << "\tCase 3.3.2 passed." << '\n';
  ofstream newfile;
  newfile.open(file3);
  for (int m = 0; m < count; m++) {
    newfile << testarray3[m] << endl;
  }

  ifstream finalteststream;
  finalteststream.open(file3);
  std::cout << "\tCase 3.4: Testing if final file is properly created" << '\n';
  assert(finalteststream.is_open());
  finalteststream.close();
  std::cout << "\tCase 3.4 passed." << '\n';
  std::cout << "\t..." << '\n';
  pause();
}

/**
@brief Program Ops.
@param none.
@return void.
*/
int main(void) {
  test_getArrayLength();
  test_arraySorting();
  test_makeArrays1();
  test_makeArrays2();
  std::cout << "\n*** Welcome to Danny's sorting program ***" << '\n';
  makeArrays();
  std::cout << "*** Goodbye. ***" << '\n';
  return 0;
}
