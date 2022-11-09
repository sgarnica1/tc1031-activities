/**
 * @file UMatrixGraph.h
 * @author Sergio Garnica
 * @brief Declaration of Unweighted Matrix Graph Class
 * @version 0.1
 * @date 2022-11-04
 *
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef U_MATRIX_GRAPH_H
#define U_MATRIX_GRAPH_H

#include <iostream>
#include "UGraph.h"
#include <vector>
#include <set>
#include <stack>

template <class Vertex>
class UMatrixGraph : public UGraph<Vertex>
{
private:
  int size, next;
  std::vector<std::vector<bool>> matrix;
  std::vector<Vertex> vertexes;

  // Private functions
  int indexOf(Vertex) const;

public:
  UMatrixGraph();
  UMatrixGraph(int);

  // Getters
  std::vector<Vertex> getVertexes() const;
  std::set<Vertex> getNeighbours(Vertex) const;

  // Public functions
  void addVertex(Vertex);
  void addEdge(Vertex, Vertex);

  // Métodos de recorrido
  std::vector<Vertex> DFS(Vertex, const UGraph<Vertex> *);

  // Operator overload
  template <class T>
  friend std::ostream &operator<<(std::ostream &, const UMatrixGraph<T> &);
};

// Constructor por default
template <class Vertex>
UMatrixGraph<Vertex>::UMatrixGraph()
{
  next = 0;
  size = 0;
}

// Constructor
template <class Vertex>
UMatrixGraph<Vertex>::UMatrixGraph(int size)
{
  matrix = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
  vertexes = std::vector<Vertex>(size);
  next = 0;
}

// Método para obtener los vértices
template <class Vertex>
std::vector<Vertex> UMatrixGraph<Vertex>::getVertexes() const
{
  return vertexes;
}

// Método para obtener el índice de un vértice
template <class Vertex>
int UMatrixGraph<Vertex>::indexOf(Vertex vertex) const
{
  for (int i = 0; i < vertexes.size(); i++)
    if (vertexes[i] == vertex)
      return i;

  return -1;
}

// Método para regresar los vecinos de un vértice
template <class Vertex>
std::set<Vertex> UMatrixGraph<Vertex>::getNeighbours(Vertex vertex) const
{
  std::set<Vertex> neighbours;
  int index = indexOf(vertex);
  for (int i = 0; i < next; i++)
    if (index != i && matrix[index][i])
      neighbours.insert(vertexes[i]);

  return neighbours;
}

// Método para agregar un vértice
template <class Vertex>
void UMatrixGraph<Vertex>::addVertex(Vertex vertex)
{
  if (indexOf(vertex) == -1 && next != size)
  {
    vertexes[next] = vertex;
    next++;
  }
}

// Método para agregar un edge
template <class Vertex>
void UMatrixGraph<Vertex>::addEdge(Vertex fromVertex, Vertex toVertex)
{
  // Revisar el ínidice de los vértices y si hay espacio disponible para agregarlos en caso de nos estar
  int fromIndex = indexOf(fromVertex);
  if (fromIndex == -1)
  {
    if (this->next == this->size)
      throw std::out_of_range("No hay espacio para agregar el vértice");
    vertexes.push_back(fromVertex);
    next++;
  }

  int toIndex = indexOf(toVertex);
  if (toIndex == -1)
  {
    if (this->next == this->size)
      throw std::out_of_range("No hay espacio para agregar el vértice");
    vertexes.push_back(toVertex);
    next++;
  }

  matrix[fromIndex][toIndex] = true;
  matrix[toIndex][fromIndex] = true;
}

// Sobrecarga del operador <<
template <class T>
std::ostream &operator<<(std::ostream &os, const UMatrixGraph<T> &graph)
{
  os << "Vértices: ";
  for (int i = 0; i < graph.vertexes.size(); i++)
    os << graph.vertexes[i] << " ";
  os << std::endl;

  os << "\nMatriz de adyacencia: " << std::endl;
  for (int i = 0; i < graph.vertexes.size(); i++)
  {
    for (int j = 0; j < graph.vertexes.size(); j++)
      os << graph.matrix[i][j] << " ";
    os << std::endl;
  }

  return os;
}

// Método para recorrer el grafo en profundidad
template <class Vertex>
std::vector<Vertex> UMatrixGraph<Vertex>::DFS(Vertex start, const UGraph<Vertex> *graph)
{
  std::set<Vertex> visited;
  std::vector<Vertex> vertexes;
  std::stack<Vertex> pending;
  pending.push(start);

  while (!pending.empty())
  {
    Vertex current = pending.top();
    pending.pop();

    if (visited.find(current) == visited.end())
    {
      visited.insert(current);
      vertexes.push_back(current);
      std::set<Vertex> neighbours = graph->getNeighbours(current);

      for (auto neighbour : neighbours)
        pending.push(neighbour);
    }
  }

  return vertexes;
}

#endif