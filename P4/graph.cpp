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
void Graph::setAllUnvisited(bool edges)
{
    for(int i = 0; i < _nodes.size(); i++)
    {
        GraphNode* currentNode = _nodes[i];
        currentNode->_visited = false;
		if (edges)
		{
			for (int i = 0; i < currentNode->_edges.size(); i++)
			{
				currentNode->_edges[i].visited = false;
			}
		}
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
            GraphNode::edge edge(currentNeighbour, currentNode, value);
            currentNode->_edges.push_back(edge);
            //Rückrichtung:
            GraphNode::edge backEdge(currentNode, currentNeighbour, value);
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
                std::cout << " -> " << currentEdge.dstNode->_key << " [" << currentEdge.value << "] ";
            }
        }
        std::cout << std::endl;

    }

    return true;
}

void Graph::getAllEdges(std::priority_queue<GraphNode::edge, std::vector<GraphNode::edge>, GraphNode::edge>& q)
{
	for each (GraphNode* nodey in _nodes)
	{
		for each(GraphNode::edge edgy in nodey->_edges)
		{
			q.push(edgy);
		}
	}
}

//Implement the depth-/breadfirstthsearch and Prim & Kruskal here

//Implement this:
bool Graph::depthSearchRek(int startKey)
{
	GraphNode* start = GetNodeByKey(startKey);
	if (start == nullptr)
		return false;

	start->_visited = true;
	for (GraphNode::edge edgy : start->_edges)
		if (!edgy.dstNode->_visited)
			depthSearchRek(edgy.dstNode->_key);

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
			if (!edge.dstNode->_visited)
			{
				edge.dstNode->_visited = true;
				q.push(edge.dstNode);
			}
		}
		q.pop();
	}

    return true;
}

//This must be done by you
double Graph::prim(int startKey)
{
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
		} while (topEdgy.dstNode->_visited); //do it till we find a not visited node

		mst += topEdgy.value;
		topEdgy.dstNode->_visited = true; //Set to visited to we don't double add a edge
		
		//New possible routes -> add them if they're not visited already
		for (GraphNode::edge newEdgy : topEdgy.dstNode->_edges)
		{
			if (!newEdgy.dstNode->_visited)
			{
				q.push(newEdgy);
			}
		}
	}

    return mst;
}

bool contains(std::vector<GraphNode::edge> visited, GraphNode::edge edgy)
{
	for each(GraphNode::edge vEdgy in visited)
	{
		if (vEdgy.dstNode == edgy.dstNode && vEdgy.srcNode == edgy.srcNode && vEdgy.value == edgy.value)
			return true;
	}
	return false;
}

double Graph::kruskal()
{
	//kruskal
	std::priority_queue<GraphNode::edge, std::vector<GraphNode::edge>, GraphNode::edge> q;
	double mst = 0;

	//Add all edges to the priority queue
	getAllEdges(q);
	setAllUnvisited();

	while (!q.empty())
	{
		GraphNode::edge topEdgy;
		bool isDuplicate = false;
		do
		{
			if (q.empty())
				return mst;
			isDuplicate = false;
			topEdgy = q.top();
			q.pop();
		} while (topEdgy.visited || isDuplicate);

		std::cout << "From " << topEdgy.srcNode->_key << " to " << topEdgy.dstNode->_key << ". Distance: " << topEdgy.value;
		//wenn kein Kreis -> füge zu mst hinzu
		if (!hasKreis(topEdgy.srcNode, topEdgy.dstNode))
		{
			mst += topEdgy.value;
			for (int i = 0; i < topEdgy.srcNode->_edges.size(); i++)
			{
				if (topEdgy.srcNode->_edges[i].dstNode == topEdgy.dstNode)
				{
					topEdgy.srcNode->_edges[i].visited = true;
					break;
				}
			}

			for (int i = 0; i < topEdgy.dstNode->_edges.size(); i++)
			{
				if (topEdgy.dstNode->_edges[i].dstNode == topEdgy.srcNode)
				{
					topEdgy.dstNode->_edges[i].visited = true;
					break;
				}
			}
			std::cout << ". Added." << std::endl;
		}
		else
		{
			std::cout << ". Not added." << std::endl;
		}
		setAllUnvisited();
	}

    return mst;
}

bool Graph::hasKreis(GraphNode* src, GraphNode* dst)
{
	//gucke ob zwischen src und dst eine verbindung besteht
	//dazu gucken ob edges visited
	src->_visited = true;
	for each(GraphNode::edge edgy in src->_edges)
	{
		if (edgy.visited && !edgy.dstNode->_visited)
		{
			if (edgy.dstNode == dst)
				return true;
			else
				if (hasKreis(edgy.dstNode, dst))
					return true;
		}
	}

	return false;
}