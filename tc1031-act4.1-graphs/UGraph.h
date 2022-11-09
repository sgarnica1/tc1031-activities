/**
 * @file UGraph.h
 * @author Sergio Garnica
 * @brief Declaration of Unweighted Graph Class
 * @version 0.1
 * @date 2022-11-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef U_GRAPH_H
#define U_GRAPH_H
#include <vector>
#include <set>

template <class Vertex>
class UGraph
{
public:
  virtual std::vector<Vertex> getVertexes() const = 0;
  virtual std::set<Vertex> getNeighbours(Vertex) const = 0;
  virtual void addVertex(Vertex) = 0;
  virtual void addEdge(Vertex, Vertex) = 0;
};

#endif