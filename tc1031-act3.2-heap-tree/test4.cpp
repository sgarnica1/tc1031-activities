#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.h"
#include "priority_queue.h"

TEST_CASE("testing push", "[List]")
{
  PriorityQueue<int> pq;
  REQUIRE(pq.empty() == 1);
  pq.push(10);
  pq.push(50);
  pq.push(30);
  pq.push(20);
  pq.push(60);
  pq.push(70);
  pq.push(80);
  REQUIRE(pq.empty() == 0);
}