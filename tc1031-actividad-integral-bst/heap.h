// =================================================================
//
// File: heap.h
// Author: Sergio Garnica González - A01704025
// Date: 19/11/2022
//
// =================================================================

#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <sstream>
#include <vector>

template <class T>
class Heap
{
public:
  // Constructor
  Heap() = default;

  // Destructor
  ~Heap() = default;

  // Access Methods
  int get_size() const;
  std::vector<T> get_nodes() const;

  // Operator Overload
  template <class ostream_t>
  friend std::ostream &operator<<(std::ostream &, const Heap<ostream_t> &);

  // Functions
  void push(T);
  void clear();

  T pop_front();

  bool is_empty() const;
  bool is_full() const;

private:
  std::vector<T> nodes;

  unsigned int get_parent(unsigned int) const;
  unsigned int get_left_child(unsigned int) const;
  unsigned int get_right_child(unsigned int) const;

  void createHeap(unsigned int);
  void swap(T, T);
  void insert(T);

  T remove();
};

template <class T>
unsigned int Heap<T>::get_parent(unsigned int index) const
{
  return (index - 1) / 2;
}

/**
 * Desc: Get the left child of a node
 * Params: index of the node
 * Return: unsigned int Index of the left child
 * Complexity O(1)
 */
template <class T>
unsigned int Heap<T>::get_left_child(unsigned int index) const
{
  return (2 * index) + 1;
}

/**
 * Desc: Get the right child of a node
 * Params: index of the node
 * Return: unsigned int Index of the right child
 * Complexity O(1)
 */
template <class T>
unsigned int Heap<T>::get_right_child(unsigned int index) const
{
  return (2 * index) + 2;
}

/**
 * Desc: Get the size of the heap
 * Return: int Size of the heap
 * Complexity O(1)
 */
template <class T>
int Heap<T>::get_size() const
{
  return nodes.size();
}

/**
 * Desc: Get the nodes of the heap
 * Return: std::vector<T> nodes of the heap
 * Complexity O(1)
 */
template <class T>
std::vector<T> Heap<T>::get_nodes() const
{
  return nodes;
}

// Operator Overload
/**
 * Desc: Overload the << operator to print the heap
 * Params: os Output stream, _heap Heap to be printed
 * Return: std::ostream& Output stream
 * Complexity O(n)
 */
template <class ostream_t>
std::ostream &operator<<(std::ostream &os, const Heap<ostream_t> &_heap)
{
  for (auto &elem : _heap.nodes)
    os << elem << " ";

  return os;
}

/**
 * Desc: createHeap the heap (min heap)
 * Parms: index Index of the node
 * Complexity O(log n)
 */
template <class T>
void Heap<T>::createHeap(unsigned int index)
{
  unsigned int left_child = get_left_child(index);
  unsigned int right_child = get_right_child(index);
  unsigned int smallest = index;

  if (left_child < nodes.size() && nodes[left_child] < nodes[smallest])
    smallest = left_child;

  if (right_child < nodes.size() && nodes[right_child] < nodes[smallest])
    smallest = right_child;

  if (index != smallest)
  {
    swap(index, smallest);
    createHeap(smallest);
  }
}

/**
 * Desc: Swap two elements in the heap
 * Params: value_1 First element, value_2 Second element
 */
template <class T>
void Heap<T>::swap(T value_1, T value_2)
{
  T temp = nodes[value_1];
  nodes[value_1] = nodes[value_2];
  nodes[value_2] = temp;
}

/**
 * Desc: Insert an element into the heap
 * Param: element to be inserted
 */
template <class T>
void Heap<T>::insert(T element)
{
  nodes.push_back(element);
  unsigned int position = nodes.size() - 1;

  while (position > 0 && element < nodes[get_parent(position)])
  {
    swap(position, get_parent(position));
    position = get_parent(position);
  }
}

/**
 * Desc: Remove the minimum element from the heap
 * Return: T Minimum element
 * Complexity O(log n)
 */
template <class T>
T Heap<T>::remove()
{
  T min = nodes[0];
  nodes[0] = nodes[nodes.size() - 1];
  nodes.pop_back();
  createHeap(0);

  return min;
}

/**
 * Insert an element into the heap
 * Params: element Element to be inserted
 */
template <class T>
void Heap<T>::push(T element)
{
  insert(element);
}

/**
 * Desc: Remove from heap the minimum element
 * Return T Minimum element
 */
template <class T>
T Heap<T>::pop_front()
{
  return remove();
}

/**
 * Desc: Check if the heap is empty
 * Return: true Heap is empty / false Heap is not empty
 * Complexity O(1)
 */
template <class T>
bool Heap<T>::is_empty() const
{
  return nodes.empty();
}

/**
 * Desc: Check if the heap is full
 * Return: true Heap is full / false Heap is not full
 * Complexity O(1)
 */
template <class T>
bool Heap<T>::is_full() const
{
  return nodes.size() == nodes.max_size();
}

#endif