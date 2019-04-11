#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <stack>

#define MAX_SIZE 25
//#define DEBUG

class Graph
{
public:
	Graph();

	bool nodeFound(char c);   // found node in graph by name
	int getIndex(char symbol);  // get matrix index by name
	void showMatrix();         // output matrix
	void addEdge(char from, char to, double weight); // add new edge
	void deleteEdge(char from, char to); // add new edge
	double weight(char from, char to); // get weight of from-to edge
	std::list<std::pair<char, double>> neighbours(char c); // returns list of probable ways from "c" node

	~Graph();

private:
	double** mMatrix;
	std::vector<char> mNodes; // vector of names of nodes
};

double heuristic(char from, char to) { return std::abs(static_cast<int>(from) - static_cast<int>(to)); }

int main()
{
	Graph graph;

	char start;
	char goal;
	std::cin >> start >> goal;

	char from, to;
	double weight;

	// Input from cin
	while (std::cin >> from)
	{
		std::cin >> to >> weight;
		graph.addEdge(from, to, weight);
	}
	//graph.showMatrix();

	/*graph.addEdge('a', 'b', 3.0);
	graph.addEdge('b', 'c', 1.0);
	graph.addEdge('c', 'd', 1.0);
	graph.addEdge('a', 'd', 5.0);
	graph.addEdge('d', 'e', 1.0);*/

	// main queue, that will be empty in
	// the end of algorithm
	/*std::priority_queue < std::pair<double, char>,
		std::vector < std::pair<double, char > >,
		std::greater< std::pair<double, char> >
	> frontier;*/

	std::stack<char> frontier;

	// start of algorithm
	frontier.push(start);

	while (!frontier.empty())
	{
		auto current = frontier.top();

		if (current == goal)
			break;

		// go neighbours of current node one by one
		char bestNode;
		double bestCost = std::numeric_limits<double>::max();
		for (auto next : graph.neighbours(current))
		{
			// cout cost of all way from start point to current vertex
			double cost =  graph.weight(current, next.first);
			if (bestCost > cost)
			{
				bestCost = cost;
				bestNode = next.first;
			}
		}
		//std::cout << "#iter# next: " << bestNode << "\n";

		if (!graph.neighbours(current).size())
		{
			frontier.pop();
		}
		else
		{
			frontier.push(bestNode);
			graph.deleteEdge(current, bestNode);
		}
	}
	//graph.show();
	std::string answer;
	while( !frontier.empty() )
	{
		answer.push_back(frontier.top());
		frontier.pop();
	}
	std::reverse(answer.begin(), answer.end());

	std::cout << answer;
}

Graph::Graph()
{
	mMatrix = new double*[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) {
		mMatrix[i] = new double[MAX_SIZE]();
	}
}

Graph::~Graph()
{
	for (int i = 0; i < MAX_SIZE; i++)
		delete[] mMatrix[i];
	delete[] mMatrix;
}

bool Graph::nodeFound(char c)
{
	return std::find(mNodes.begin(), mNodes.end(), c) != mNodes.end();
}

int Graph::getIndex(char symbol)
{
	int idx = -1;
	auto it = std::find(mNodes.begin(), mNodes.end(), symbol);
	if (it != mNodes.end()) {
		idx = static_cast<int>(it - mNodes.begin());
	}
	return idx;
}

void Graph::showMatrix()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
			std::cout << mMatrix[i][j] << " ";
		std::cout << "\n";
	}
}

void Graph::addEdge(char from, char to, double weight)
{
	if (!nodeFound(from))
		mNodes.push_back(from);
	if (!nodeFound(to))
		mNodes.push_back(to);
	int y = getIndex(to);
	int x = getIndex(from);
	mMatrix[x][y] = weight;
}

void Graph::deleteEdge(char from, char to)
{
	int y = getIndex(to);
	int x = getIndex(from);
	mMatrix[x][y] = 0;
}

double Graph::weight(char from, char to)
{
	int x = getIndex(from);
	int y = getIndex(to);
	return mMatrix[x][y];
}
std::list<std::pair<char, double>> Graph::neighbours(char c)
{
	int pos = getIndex(c);
	std::list<std::pair<char, double>> mlist;
	for (int i = 0; i < MAX_SIZE; i++)
		if (mMatrix[pos][i] != 0)
			mlist.push_back({ mNodes[i], mMatrix[pos][i] });
	return mlist;
}
