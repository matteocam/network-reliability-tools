#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cassert>

#include <lemon/list_graph.h>

using std::vector;
using std::min;
using std::max;
//using std::assert;

// typedefs
typedef lemon::ListGraph graph_t;
typedef graph_t::EdgeIt EdgeIt;
typedef graph_t::Edge Edge;
typedef graph_t::NodeIt NodeIt;
typedef graph_t::Node Node;
typedef graph_t::EdgeMap<float> DistanceMap;
typedef graph_t::EdgeMap<float> FailureProbMap;
typedef graph_t::EdgeMap<bool> FilterMap;
enum operationality {EDGE_UP, EDGE_DOWN, EDGE_UNDETERMINED};
typedef graph_t::EdgeMap<operationality> StatusMap;
typedef std::vector<Node> NodeTable;
typedef std::pair<int, int> EdgeP;
using lemon::INVALID;

class ReliabilityGraph
{
  public:

  ReliabilityGraph(int _n, int num_arcs, EdgeP edge_array[], float distances[], float failure_probs[], int D = 2);
  ~ReliabilityGraph();

  // getters
  // NOTE: assumption on vertex labelling: 0..n-1
  int numVertices();
  Node s() { return nodes[0]; } // source node
  Node t() { return nodes[n-1]; } // sink node

  vector<Edge> getEdges();

  void computeMinDistances();

  void forceEdgeUp(Edge e) { status[e] = EDGE_UP; }
  void forceEdgeDown(Edge e) { status[e] = EDGE_DOWN; }

  bool hasDstPath();
  bool hasOperationalDstPath();

  Edge getEdgeWithUndeterminedState();
  float getEdgeReliability(Edge);
  
  void setRealEdgeStatus(const Edge &e);

  protected:
  void addEdgeById(int a, int b, float dist, float fp);
  // return the distance between s and it or -1 if they are not reachable
  int filteredBFS(const FilterMap &test);
  

  
  private:
    graph_t g;
    NodeTable nodes;
    int n;
    int D;
    
    // edge properties
    DistanceMap distance;
    FailureProbMap failureProb;
    StatusMap status;

};

