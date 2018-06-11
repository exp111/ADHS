#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>
#include <list>

class GraphNode
{
public:

    struct edge {
        GraphNode *dstNode; //Destination node
		GraphNode *srcNode;
        double value; //Edge Weight
		bool visited;

        edge(){
            dstNode = nullptr;
			srcNode = nullptr;
            value = 0;
			visited = false;
        }
        edge(GraphNode * dst, GraphNode *src, double val)
        {
            dstNode = dst;
			srcNode = src;
            value = val;
			visited = false;
        }

        bool operator()(const edge& comp, const edge& toComp) const
           {
               return comp.value > toComp.value;
           }
    };

    //Maybe helpful for your Work
    GraphNode(int key);
    bool hasNeighbor(int neighborKey);
    edge getEdgeByNeigborkey(int key);

    int _key;
    std::vector<edge> _edges;
    bool _visited;
    double _distance;
    GraphNode *_prev;
    int _component;

};

#endif // GRAPHNODE_H
