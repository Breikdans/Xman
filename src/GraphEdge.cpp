#include <GraphEdge.h>

GraphEdge::GraphEdge(GraphVertex* origin, GraphVertex* dest) : _pOrigin(origin), _pDestination(dest) {_weight = 0.0f;}

GraphEdge::~GraphEdge () {}
