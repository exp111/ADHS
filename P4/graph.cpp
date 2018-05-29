#include "graph.h"

Graph::Graph()
{
    _anzKnoten = 0;
    _nodes.clear();
}

Graph::~Graph()
{
    for (int i = 0; i < _nodes.size(); i++) {
        delete _nodes[i];
    }
    _nodes.clear();
}

//Get the node pointer by given key
GraphNode* Graph::GetNodeByKey(int key)
{
    for(int i = 0; i < _anzKnoten; i++)
    {
        GraphNode* currentNode = _nodes[i];
        if(currentNode->_key == key)
        {
            return currentNode;
        }
    }
    return nullptr;
}

//iterate all nodes and set _visited to false
void Graph::setAllUnvisited()
{
    for(int i = 0; i < _nodes.size(); i++)
    {
        GraphNode* currentNode = _nodes[i];
        currentNode->_visited = false;
    }
}

//Check if all nodes are set to visited
bool Graph::checkVisited()
{
    for(int i = 0; i < _nodes.size(); i++)
    {
        GraphNode* currentNode = _nodes[i];
        if(currentNode->_visited == false)
            return false;
    }
    return true;
}

bool Graph::init(std::string path)
{
    {
    std::ifstream file;
    file.open(path, std::ios_base::in);

    if (!file)
    {
        std::cout << "Cannot open file." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Start reading" << std::endl;

        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);

        std::cout << "Insert _anzKnoten" << std::endl;
        iss >> _anzKnoten;

        std::cout << "Create all Nodes" << std::endl;
        //Alle Knoten anlegen
        for(int i = 0; i < _anzKnoten; i++)
        {
            GraphNode* currentNode = new GraphNode(i);
            _nodes.push_back(currentNode);
        }

        std::cout << "Start creating edges" << std::endl;
        while (std::getline(file, line))
        {
            std::istringstream edges(line);
            int from, value, to;
            if (!(edges >> from >> to >> value)) { break; } // error

            std::cout << "From: " << from << " To: " << to << " Value: " << value << std::endl;
            GraphNode* currentNode = GetNodeByKey(from);
            GraphNode* currentNeighbour = GetNodeByKey(to);
            //Hinrichrung:
            GraphNode::edge edge(currentNeighbour, value);
            currentNode->_edges.push_back(edge);
            //Rückrichtung:
            GraphNode::edge backEdge(currentNode, value);
            currentNeighbour->_edges.push_back(backEdge);
        }
       return true;
    }

    return false;
}

}

bool Graph::print()
{
    if(_nodes.empty()) return false;
    //Print with Node ID: 1st neighbour, 2nd neighbour ...
    for(int i = 0; i < _anzKnoten; i++)
    {
        GraphNode* currentNode = _nodes[i];
        std::cout << currentNode->_key << " ";
        for(int k = 0; k < currentNode->_edges.size(); k++)
        {
            if(!currentNode->_edges.empty()){
                GraphNode::edge currentEdge = currentNode->_edges[k];
                std::cout << " -> " << currentEdge.node->_key << " [" << currentEdge.value << "] ";
            }
        }
        std::cout << std::endl;

    }

    return true;
}

//Implement the depth-/breadfirstthsearch and Prim & Kruskal here

//Implement this:
bool Graph::depthSearchRek(int startKey)
{
	GraphNode* start = GetNodeByKey(startKey);
	if (start == nullptr)
		return false;

	start->_visited = true;
	for (int i = 0; i < start->_edges.size(); i++)
		if (!start->_edges[i].node->_visited)
			depthSearchRek(start->_edges[i].node->_key);

	return true;
}


bool Graph::breadthSearchIter(int startKey)
{
	GraphNode* start = GetNodeByKey(startKey);
	if (start == nullptr)
		return false;

	std::queue<GraphNode*> q;
	q.push(start);

	start->_visited = true;
	while (!q.empty())
	{
		for (GraphNode::edge edge : q.front()->_edges)
		{
			if (!edge.node->_visited)
			{
				edge.node->_visited = true;
				q.push(edge.node);
			}
		}
		q.pop();
	}

    return true;
}

//This must be done by you
double Graph::prim(int startKey)
{
	//TODO: prim
	GraphNode* start = GetNodeByKey(startKey);
	if (start == nullptr)
		return -1;

	//priority queues so we just can get the top edge in the queue (the one with the lowest value)
	std::priority_queue<GraphNode::edge, std::vector<GraphNode::edge>, GraphNode::edge> q;
	double mst = 0;
	
	for (GraphNode::edge edgy : start->_edges)
	{
		q.push(edgy);
	}
	start->_visited = true;

	while (!q.empty())
	{
		GraphNode::edge topEdgy;
		do
		{
			if (q.empty()) //no nodes? then frick off
				return mst;
			topEdgy = q.top();
			q.pop();
		} while (topEdgy.node->_visited); //do it till we find a not visited node

		mst += topEdgy.value;
		topEdgy.node->_visited = true; //Set to visited to we don't double add a edge
		
		//New possible routes -> add them if they're not visited already
		for (GraphNode::edge newEdgy : topEdgy.node->_edges)
		{
			if (!newEdgy.node->_visited)
			{
				q.push(newEdgy);
			}
		}
	}

    return mst;
}

double Graph::kruskal()
{
	//TODO: kruskal
    return 5.;
}
