#ifndef GRAPH_H
#define GRAPH_H

#include <deque>
#include <map>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "graphnode.h"

class Graph
{
public:
    Graph();
    ~Graph();

    GraphNode* GetNodeByKey(int key);
    void setAllUnvisited(bool edges = false);
    bool checkVisited();
    bool init(std::string path);
    bool print();

	void getAllEdges(std::priority_queue<GraphNode::edge, std::vector<GraphNode::edge>, GraphNode::edge> &q);

    //Implement this:
    bool depthSearchRek(int startKey);
    bool breadthSearchIter(int startKey);

    //This must be done by you
    double prim(int startKey);
    double kruskal();

	bool hasKreis(GraphNode* src, GraphNode* dst);

    //They might be helpful
    int _anzKnoten;
    bool _ger, _gew;
    std::vector<GraphNode*> _nodes;
};

#endif // GRAPH_H
