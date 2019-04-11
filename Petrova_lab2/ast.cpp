#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>

#define MAX_SIZE 25
#define DEBUG

class Graph
{
public:
	Graph();

	bool nodeFound(char c);   // found node in graph by name
	int getIndex(char symbol);  // get matrix index by name
	void showMatrix();         // output matrix
	void addEdge(char from, char to, double weight); // add new edge
	double weight(char from, char to); // get weight of from-to edge
	std::list<std::pair<char, double>> neighbours(char c); // returns list of probable ways from "c" node

	~Graph();

private:
	double** mMatrix; 
	std::vector<char> mNodes; // vector of names of nodes
};

int main()
{
	size_t heuristic;
	Graph graph;

	char start;
	char goal;
	std::cout << "Enter from-to points: \n";
	std::cin >> start >> goal;

	char from, to;
	double weight;

	std::cout << "Enter grom-to-weight-heuristic  \n";
	// Input from cin
	while (std::cin >> from)
	{
		std::cin >> to >> weight >> heuristic;
		graph.addEdge(from, to, weight + heuristic);
	}
	//graph.showMatrix();

	/*graph.addEdge('a', 'b', 0.4);
	graph.addEdge('b', 'e', 0.9);
	graph.addEdge('a', 'c', 2.4);
	graph.addEdge('a', 'd', 1.5);
	graph.addEdge('d', 'e', 3.2);
	graph.addEdge('c', 'e', 1.7);*/

	// main queue, that will be empty in
	// the end of algorithm
	std::priority_queue < std::pair<double, char>,
		std::vector < std::pair<double, char > > ,
		std::greater< std::pair<double, char> >
	> frontier;

	// start of algorithm
	frontier.push({ 0, start });

	// dictionary of passed paths
	// first - "to" node, second - "from" node 
	std::unordered_map<char, char> came_from;

	// dictionary of nodes with matched costs
	// cost means summary of all previous nodes
	// beginning from start node
	std::map<char, double> current_cost;

	while (!frontier.empty())
	{
#ifdef DEBUG
		auto queue = frontier;
		int size = queue.size();
		std::cout << "#ITER#\nqueue: ";
		for (int i = 0; i < size; i++)
		{
			std::cout << queue.top().second;
			queue.pop();
		}
		std::cout << "\ncost map:\n";
		for (auto i : current_cost)
		{
			std::cout << "\t" << i.first << " " << i.second << "\n";
		}
		std::cout << "passed paths map:\n";
		for (auto i : came_from)
		{
			std::cout << "\t" << i.second << " -> " << i.first << "\n";
		}
		std::cout << "_________________________\n";
#endif
		auto current = frontier.top();
		frontier.pop();

		if (current.second == goal) 
			break;

		// go neighbours of current node one by one 
		for (auto next : graph.neighbours(current.second))
		{
			// cout cost of all way from start point to current vertex
			double new_cost = current_cost[current.second] + graph.weight(current.second, next.first);
			if (!current_cost.count(next.first) || new_cost < current_cost[next.first])
			{
				current_cost[next.first] = new_cost;
				frontier.push({ new_cost + heuristic , next.first });
				came_from[next.first] = current.second;
			}
		}
	}

	//graph.show();

	std::string answer;
	answer.push_back(goal);

	while (answer.back() != start)
		answer.push_back(came_from[answer.back()]);


	std::reverse(answer.begin(), answer.end());

	for (auto e : answer)
		std::cout << e;

	//system("pause");
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
