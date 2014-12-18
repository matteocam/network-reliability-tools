#include "ReliabilityGraph.hpp"
#include "ReliabilityComputation.hpp"

#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::exit;
using std::cerr;

const int MAX_EDGES = 10000;



int N, E;
float distances[MAX_EDGES];
float failureProbs[MAX_EDGES];
EdgeP edges[MAX_EDGES];


// reads graph from standard input
void readGraph()
{
  /*
   * Format: N E
   * Then E lines with: U V Distance ProbOfFailure
  */

  std::fstream cin("graph.in");
  cin >> N >> E;
  if (E > MAX_EDGES) {
    cerr << "Graph is too big (max = " << MAX_EDGES
         << " edges) . Exiting...";
    exit(1);
  }

  // XXX: No check on proper indices of nodess

  cout << N << " " << E << endl;

  for (int i(0); i < E; i++) {
    cin >> edges[i].first >> edges[i].second;
    cin >> distances[i] >> failureProbs[i];
    cout << edges[i].first << " " << edges[i].second << "\t";
    cout << distances[i] << "\t" << failureProbs[i] << endl;
    
    
  }
  
}

int main(int argc, char *argv[])
{
  readGraph();
  ReliabilityGraph rg(N, E, edges, distances, failureProbs);
  ReliabilityComputation rc(&rg);
  cout << "Reliability of the graph: " << rc.compute() << endl;
  
  return 0;
}
