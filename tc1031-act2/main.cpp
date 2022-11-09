// =================================================================
//
// File: main.cpp
// Author: Sergio Garnica González - A01704025
// Date: 30/08/2022
//
// =================================================================
#include <iostream>
#include <vector>
#include <fstream>
#include "header.h"
#include "search.h"
#include "bubble.h"
#include "selection.h"
#include "insertion.h"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream inputFile;
  ofstream outputFile;

  if (argc != 3)
  {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  outputFile.open(argv[2]);

  if (!inputFile.is_open())
  {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  // Cantidad de elementos del vector
  int n, q, num;
  inputFile >> n;
  vector<int> nums(n);

  // Inicializar vector
  for (int i = 0; i < n; i++)
  {
    inputFile >> num;
    nums[i] = num;
  }

  vector<int> disordered_nums = nums;
  int selection_c, insertion_c, bubble_c;

  selection_c = selectionSort(nums);
  nums = disordered_nums;
  insertion_c = insertionSort(nums);
  nums = disordered_nums;
  bubble_c = bubbleSort(nums);

  outputFile << bubble_c << " " << selection_c << " " << insertion_c << "\n\n";

  // Cantidad de números a buscar
  inputFile >> q;
  std::pair<int, int> result;

  for (int i = 0; i < q; i++)
  {
    inputFile >> num;
    result = sequentialSearch(nums, num);
    outputFile << result.first << " " << result.second << " ";
    result = binarySearch(nums, num);
    outputFile << result.second << "\n";
  }

  inputFile.close();
  outputFile.close();

  return 0;
}
