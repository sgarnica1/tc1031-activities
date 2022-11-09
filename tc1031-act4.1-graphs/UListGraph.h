/**
 * @file UListGraph.h
 * @author Sergio Garnica
 * @brief Declaration of Unweighted List Graph Class
 * @version 0.1
 * @date 2022-11-04
 *
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef U_LIST_GRAPH_H
#define U_LIST_GRAPH_H

#include <iostream>
#include "UGraph.h"
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

template <class Vertex>
class UListGraph : public UGraph<Vertex>
{
private:
  int size, next;
  std::map<Vertex, std::set<Vertex>> edges;
  std::vector<Vertex> vertexes;

public:
  UListGraph();
  UListGraph(int);

  // Getters
  std::vector<Vertex> getVertexes() const;
  std::set<Vertex> getNeighbours(Vertex) const;

  // Public functions
  void addVertex(Vertex);
  void addEdge(Vertex, Vertex);
  bool containsEdge(Vertex) const;

  // Métodos de recorrido
  std::vector<Vertex> BFS(Vertex, const UGraph<Vertex> *);

  // Operator overload
  template <class T>
  friend std::ostream &operator<<(std::ostream &, const UListGraph<T> &);
};

// Constructor por default
template <class Vertex>
UListGraph<Vertex>::UListGraph()
{
  next = 0;
  size = 0;
}

// Constructor con tamaño
template <class Vertex>
UListGraph<Vertex>::UListGraph(int size)
{
  vertexes = std::vector<Vertex>(size);
  this->size = size;
  this->next = 0;
}

// Función que regresa los vértices del grafo
template <class Vertex>
std::vector<Vertex> UListGraph<Vertex>::getVertexes() const
{
  return vertexes;
}

// Función que regresa los vecinos de un vértice
template <class Vertex>
std::set<Vertex> UListGraph<Vertex>::getNeighbours(Vertex vertex) const
{
  return edges.at(vertex);
}

// Función que agrega un vértice al grafo
template <class Vertex>
void UListGraph<Vertex>::addVertex(Vertex vertex)
{
  if (next < size)
  {
    vertexes[next] = vertex;
    next++;
  }
}

// Función que agrega una arista al grafo
template <class Vertex>
void UListGraph<Vertex>::addEdge(Vertex fromVertex, Vertex toVertex)
{
  addVertex(fromVertex);
  addVertex(toVertex);

  edges[fromVertex].insert(toVertex);
  edges[toVertex].insert(fromVertex);
}

// Función que regresa si existe una arista entre dos vértices
template <class Vertex>
bool UListGraph<Vertex>::containsEdge(Vertex vertex) const
{
  return edges.find(vertex) != edges.end();
}

// Función que regresa un vector con el recorrido BFS
template <class Vertex>
std::vector<Vertex> UListGraph<Vertex>::BFS(Vertex vertex, const UGraph<Vertex> *graph)
{
  std::set<Vertex> visited;
  std::vector<Vertex> vertexes;
  std::queue<Vertex> queue;
  queue.push(vertex);

  while (!queue.empty())
  {
    Vertex current = queue.front();
    queue.pop();

    if (visited.find(vertex) == visited.end())
    {
      visited.insert(current);
      vertexes.push_back(current);

      std::set<Vertex> neighbours = graph->getNeighbours(current);
      for (auto neighbour : neighbours)
      {
        queue.push(neighbour);
      }
    }
  }

  return vertexes;
}

// Sobrecarga del operador <<
template <class T>
std::ostream &operator<<(std::ostream &os, const UListGraph<T> &graph)
{
  os << "Lista de adjacencia: " << std::endl;
  for (auto vertex : graph.vertexes)
  {
    os << vertex << " -> ";
    for (auto neighbour : graph.edges.at(vertex))
    {
      os << neighbour << " ";
    }
    os << std::endl;
  }
  os << "\nVértices: ";
  for (int i = 0; i < graph.vertexes.size(); i++)
    os << graph.vertexes[i] << " ";
  os << std::endl;
  return os;
}

#endif
