/**
 * @author Sergio Garnica
 * @brief Graph Activity
 * @version 0.1
 * @date 2022-11-04
 *
 * */

#include <iostream>
#include "UMatrixGraph.h"
#include <vector>
#include <set>

// main function
int main()
{
  // Create a graph
  UMatrixGraph<int> graph(5);

  // Add vertexes
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addVertex(3);
  graph.addVertex(4);
  graph.addVertex(5);

  // Add edges
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(2, 4);
  graph.addEdge(3, 4);
  graph.addEdge(3, 5);
  graph.addEdge(4, 5);

  // Print graph
  std::cout << graph << std::endl;

  // DFS
  int start = 3;
  std::vector<int> dfs = graph.DFS(start, &graph);

  // Print DFS
  std::cout << "DFS from " << start << ": ";
  for (auto it = dfs.begin(); it != dfs.end(); ++it)
    std::cout << ' ' << *it;

  return 0;
}