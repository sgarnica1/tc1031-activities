// =================================================================
//
// File: heap.h
// Author: Sergio Garnica González - A01704025
// Date: 19/11/2022
//
// =================================================================

#include <iostream>
#include <fstream>

#include "heap.h"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " <size> <file>" << std::endl;
    return 1;
  }

  std::fstream file(argv[1], std::ios::in);
  if (!file.is_open())
  {
    std::cout << "Error: Could not open file " << argv[1] << std::endl;
    return 1;
  }

  std::fstream output_file(argv[2], std::ios::out);
  if (!output_file.is_open())
  {
    std::cout << "Error: Could not open file " << argv[2] << std::endl;
    return 1;
  }

  int size;
  file >> size;

  Heap<int> heap;

  int value;
  // ADD NODES TO HEAP
  for (int i = 0; i < size; i++)
  {
    file >> value;
    heap.push(value);
  }

  int comparisons = 0, sum = 0;

  // MAKE COMPARISONS
  while (heap.get_size() > 1)
  {
    sum = heap.pop_front() + heap.pop_front();
    heap.push(sum);
    comparisons += sum - 1;
  }

  output_file << comparisons << std::endl;
}