#include "ReliabilityGraph.hpp"

#include <iostream>
#include <queue>
using std::queue;

ReliabilityGraph::ReliabilityGraph(int _n, int num_arcs, EdgeP edge_array[], float distances[], float failure_probs[], int _D) :
  distance(g), failureProb(g), status(g), D(_D)
{
  n = _n;
  // initialize graph
  for (auto i(0); i < n; i++)
    nodes.push_back(g.addNode());
    
//    int num_arcs = sizeof(edge_array) / sizeof(EdgeP);
  std::cout << "NUM_ARCS = " << num_arcs << std::endl;
  for (auto i(0); i < num_arcs; i++)
    addEdgeById(edge_array[i].first,
                edge_array[i].second,
                distances[i],
                failure_probs[i] );

    // TEST


  char name[] = "012345";
  
  std::cout << "Nodes:";
  for (NodeIt i(g); i!=INVALID; ++i)
    std::cout << " " << g.id(i);
  std::cout << std::endl;

  std::cout << "Edges:";
  for (EdgeIt i(g); i!=INVALID; ++i)
    std::cout << " (" << g.id(g.u(i)) << "," << g.id(g.v(i)) << ")";
  std::cout << std::endl;
  std::cout << std::endl;

  for (EdgeIt i(g); i!=INVALID; ++i) {
    int u, v;
    u = g.id(g.u(i));
    v = g.id(g.v(i));
    std::cout << "dist(" << g.id(g.u(i)) << ","
              << g.id(g.v(i)) << ")="<<distance[i] << " fp=" << failureProb[i] << " ";
      
    switch(status[i]) {
      case EDGE_DOWN:
        std::cout << "EDGE_DOWN\n";
        break;
      case EDGE_UNDETERMINED:
        std::cout << "EDGE_UNDETERMINED\n";
        break;
      case EDGE_UP:
        std::cout << "EDGE_UP\n";
        break;
    };
    
  }

  std::cout << std::endl;
  
}

ReliabilityGraph::~ReliabilityGraph()
{

}

int ReliabilityGraph::numVertices()
{
  assert(0); // should be implemented IF called
}

vector<Edge> ReliabilityGraph::getEdges()
{
  assert(0); // should probably not be called
}

void ReliabilityGraph::setRealEdgeStatus(const Edge &e)
{
  float fp = failureProb[e];
  if ( fp == 0.0 )  // the edge cannot fail
    status[e] = EDGE_UP;
  else if ( fp == 1.0 )  // the edge will certainly fail
    status[e] = EDGE_DOWN;
  else
    status[e] = EDGE_UNDETERMINED;
}


void ReliabilityGraph::addEdgeById(int a, int b, float dist, float fp)
{
  Node u, v;
  u = nodes[a];
  v = nodes[b];
  Edge e = g.addEdge(u,v);
  distance[e] = dist;
  failureProb[e] = fp;
  setRealEdgeStatus(e);
}


void ReliabilityGraph::computeMinDistances()
{
  // predecessor map
  std::vector<Node> p(numVertices());
  // distance map
  std::vector<int> d(n);
  // starting vertex
  Node start = s();

  // do Dijkstra here
  // TODO
  // ...

}

bool ReliabilityGraph::hasDstPath()
{
  // returns if there a (s,t)-path of nodes that are either up or undetermined
  // of length <= D
  FilterMap excludeDownEdges(g);
  for (EdgeIt e(g); e!=INVALID; ++e)
  {
    excludeDownEdges[e] = status[e] != EDGE_DOWN;
  }

  int d = filteredBFS(excludeDownEdges);
  return (d != -1 && d <= D);
}

bool ReliabilityGraph::hasOperationalDstPath()
{
  FilterMap onlyUpEdges(g);
  for (EdgeIt e(g); e!=INVALID; ++e)
  {
    onlyUpEdges[e] = (status[e] == EDGE_UP);
    //std::cout << onlyUpEdges[e] << std::endl;
  }

  int d = filteredBFS(onlyUpEdges);
  return (d != -1 && d <= D);
}

Edge ReliabilityGraph::getEdgeWithUndeterminedState()
{
  // returns an edge (the first found) with status between 0 and 1
  for (EdgeIt e(g); e != INVALID; ++e)
    if (status[e] == EDGE_UNDETERMINED)
      return e;

  std::cerr << "No edge with undetermined status" << std::endl;
  
}

float ReliabilityGraph::getEdgeReliability(Edge e)
{
  return 1.0 - failureProb[e];
}

int ReliabilityGraph::filteredBFS(const FilterMap &test)
{
  queue<Node> q;
  graph_t::NodeMap<bool> discovered(g);
  graph_t::NodeMap<int> bfs_distance(g);

  // TODO: initialize maps
  for (NodeIt u(g); u!=INVALID; ++u)
  {
    discovered[u] = false;
    bfs_distance[u] = -1;
  }
  
  
  // starting point: s()
  q.push(s());
  discovered[s()] = true;
  bfs_distance[s()] = 0;
  
  while(!q.empty()) {
    // remove node from queue and explore it
    Node u = q.front();
    q.pop();

    // explore each of the neighbors
    for (graph_t::OutArcIt a(g, u); a != INVALID; ++a)
    {
      if (!test[a]) // skip edge if we cannot go through it
        continue;
      Node v = g.target(a);
      if (discovered[v]) // skip node if already visited
        continue; 
      q.push(v);
      discovered[v] = true;
      bfs_distance[v] = bfs_distance[u]+1;
    }
  }

    return bfs_distance[t()]; // it's -1 if unreached

}
