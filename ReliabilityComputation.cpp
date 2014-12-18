#include "ReliabilityGraph.hpp"
#include "ReliabilityComputation.hpp"

float ReliabilityComputation::computeMoskovitz()
{
  if ( !rg->hasDstPath() )
    return 0;
  
  if ( rg->hasOperationalDstPath() )
    return 1.0;

  Edge e = rg->getEdgeWithUndeterminedState(); // filter among relevant edges
  float r_e = rg->getEdgeReliability(e);

  float rel_with_e_up, rel_with_e_down;

  // compute reliability when edge is up
  rg->forceEdgeUp(e);
  rel_with_e_up = computeMoskovitz();
  rg->setRealEdgeStatus(e); // put it back

  // compute reliability when edge is down
  rg->forceEdgeDown(e);
  rel_with_e_down = computeMoskovitz();
  rg->setRealEdgeStatus(e); // put it back

  return r_e*rel_with_e_up + (1-r_e)*rel_with_e_down;
}

float ReliabilityComputation::compute()
{
  initStatus();
  return computeMoskovitz();
}

void ReliabilityComputation::initStatus()
{
  // Unnecessary probably.
  
  // set all edges relevant
  // TODO
  
  // set all edges to their real state
  //vector <Edge> edges = rg->getEdges();
  //std::for_each(edges.begin(), edges.end(), [this](Edge e){ rg->setEdgeRealStatus(e); });
}
