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
    void setAllUnvisited();
    bool checkVisited();
    bool init(std::string path);
    bool print();

    //Implement this:
    bool depthSearchRek(int startKey);
    bool breadthSearchIter(int startKey);

    //This must be done by you
    double prim(int startKey);
    double kruskal();

    //They might be helpful
    int _anzKnoten;
    bool _ger, _gew;
    std::vector<GraphNode*> _nodes;
};

#endif // GRAPH_H
