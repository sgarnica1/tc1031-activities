#ifndef ACTIVITY_H
#define ACTIVITY_H

// =========================================================
// File: actitivy.h
// Author: María del Pilar Dávila Verduzco - A01708943
// Author: Sergio Garnica González - A01704025
// Date: 12/11/2022
// =========================================================

#include "ugraph.h"

// =========================================================
// Function: dfs2
// Parameters: v - vertex to start traversal
//             graph - graph to traverse
//             reached - array of visited vertices
//             TS - temporal stack to store vertices
// Description: Depth-first search algorithm to traverse a graph
//              and store vertices in a stack
// COMPLEXITY: O(V+E)
// =========================================================
template <class Vertex>
void dfs2(Vertex v, const UnweightedGraph<Vertex> *graph, std::set<Vertex> &reached, std::stack<Vertex> &TS)
{
  // Add the vertex to the set of reached vertices
  reached.insert(v);
  // Get the neighbors of the vertex
  std::set<Vertex> connections = graph->getConnectionFrom(v);

  // Iterate over the neighbors
  typename std::set<Vertex>::iterator itr;
  for (itr = connections.begin(); itr != connections.end(); itr++)
    // If the neighbor is not in the set of reached vertices or is the last vertex, call dfs2
    if (reached.find(*itr) == reached.end())
      dfs2(*itr, graph, reached, TS);

  // Add the vertex to the stack
  TS.push(v);
}

// =========================================================
// Function: topologicalSort
// Parameters: UGraph<T> *graph
// Returns: string
// Description: This function returns a string with the
//              topological sort of the graph.
// COMPLEXITY: O(V+E)
// =========================================================
template <class Vertex>
std::string topologicalSort(const UnweightedGraph<Vertex> *graph)
{
  std::set<Vertex> visited;
  std::stack<Vertex> TS; // Temporal Stack

  // Iterate over the vertices
  typename std::vector<Vertex>::iterator itr;
  for (int i = 0; i < graph->getVertexes().size(); i++)
    // If the vertex is not in the set of reached vertices or if it is the last vertex on the set, call dfs2
    if (visited.find(graph->getVertexes()[i]) == visited.end())
      dfs2(graph->getVertexes()[i], graph, visited, TS);

  // Print temporal stack
  std::stringstream aux;
  aux << "[";
  while (!TS.empty())
  {
    if (TS.size() != 1)
      aux << TS.top() << " ";
    else
      aux << TS.top();
    TS.pop();
  }
  aux << "]";

  return aux.str();
}

// =========================================================
// Function: isBipartite
// Parameters: UGraph<T> *graph
// Returns: bool
// Description: This function returns true if the graph is
//              bipartite, false otherwise.
// COMPLEXITY: O(V+E)
template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex> *graph)
{
  // Create a map to store the colors of the vertices
  std::map<Vertex, int> colors;

  // Iterate over the vertices
  typename std::vector<Vertex>::iterator itr;
  for (itr = graph->getVertexes().begin(); itr != graph->getVertexes().end(); itr++)
    colors[*itr] = -1;

  colors[graph->getVertexes()[0]] = 1;

  std::queue<Vertex> q;
  q.push(graph->getVertexes()[0]);

  while (!q.empty())
  {
    int v = q.front();
    q.pop();

    // Get the neighbors of the vertex
    std::set<Vertex> connections = graph->getConnectionFrom(v);

    // Iterate over the neighbors
    typename std::set<Vertex>::iterator itr;
    for (itr = connections.begin(); itr != connections.end(); itr++)
    {
      // Return false if there is a self loop
      if (v == *itr)
        return false;

      // If the neighbor is not colored, color it with the opposite color
      if (colors[*itr] == -1)
      {
        colors[*itr] = 1 - colors[v];
        q.push(*itr);
      }
      else if (colors[*itr] == colors[v])
        return false;
    }
  }

  return true;
}

// =========================================================
// Function: isCyclic
// Parameters: v - vertex to start traversal
//             graph - graph to traverse
//             reached - array of visited vertices
//             parent - parent of the vertex
// Returns: bool
// Description: This function returns true if the graph is
//              cyclic, false otherwise.
// COMPLEXITY: O(V+E)
template <class Vertex>
bool isCyclic(Vertex v, const UnweightedGraph<Vertex> *graph,
              std::set<Vertex> &reached, Vertex parent)
{
  reached.insert(v);

  // Get the neighbors of the vertex
  std::set<Vertex> connections = graph->getConnectionFrom(v);

  // Iterate over the neighbors
  typename std::set<Vertex>::iterator itr;
  for (itr = connections.begin(); itr != connections.end(); itr++)
  {
    // Return true if there is a self loop
    if (v == *itr)
      return true;

    // If the neighbor is not in the set of reached vertices or is the last vertex, call isCyclic
    if (reached.find(*itr) == reached.end())
    {
      if (isCyclic(*itr, graph, reached, v))
        return true;
    }
    else if (*itr != parent)
      return true;
  }

  return false;
}

// =========================================================
// Function: isTree
// Parameters: UGraph<T> *graph
// Returns: bool
// Description: This function returns true if the graph is
//              a tree, false otherwise.
// COMPLEXITY: O(V+E)
template <class Vertex>
bool isTree(const UnweightedGraph<Vertex> *graph)
{
  typename std::vector<Vertex>::iterator itr;

  // Iterate over vertexes
  for (auto v : graph->getVertexes())
  {
    std::set<Vertex> reached;
    if (isCyclic(v, graph, reached, v))
      return false;
  }

  return true;
}

#endif /* ACTIVITY_H */
