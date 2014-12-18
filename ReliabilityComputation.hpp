class ReliabilityGraph;

class ReliabilityComputation
{
  public:
  ReliabilityComputation(ReliabilityGraph *_rg) : rg(_rg) { }

  float compute();
  
  protected:

  enum operationality { EDGE_UP, EDGE_DOWN, EDGE_UNDETERMINED };

  void initStatus();
  float computeMoskovitz();

  private:
    ReliabilityGraph *rg;  
};
