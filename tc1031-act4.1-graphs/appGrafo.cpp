/**
 * @author Sergio Garnica
 * @brief Graph Activity
 * @version 0.1
 * @date 2022-11-04
 *
 * */

#include <iostream>
#include "UMatrixGraph.h"
#include "UListGraph.h"
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
  std::cout << "DFS desde  " << start << ": ";
  for (auto it = dfs.begin(); it != dfs.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << "\n\n------------------------\n";

  // Graph Adjacent List
  UListGraph<int> graphList(5);

  // Add vertexes
  graphList.addVertex(1);
  graphList.addVertex(2);
  graphList.addVertex(3);
  graphList.addVertex(4);
  graphList.addVertex(5);

  // Add edges
  graphList.addEdge(1, 2);
  graphList.addEdge(1, 3);
  graphList.addEdge(2, 3);
  graphList.addEdge(2, 4);
  graphList.addEdge(3, 4);
  graphList.addEdge(3, 5);
  graphList.addEdge(4, 5);

  // Print graph
  std::cout << graphList << std::endl;

  // BFS
  std::vector<int> bfs = graphList.BFS(start, &graphList);

  // Print BFS
  std::cout << "BFS desde  " << start << ": ";
  for (auto it = bfs.begin(); it != dfs.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << std::endl;

  return 0;
}