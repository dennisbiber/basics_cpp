#include <iostream>
using namespace std;

typedef pair<int, int> tuple;

struct Graph
{
	vecctor<pair<int, tuple> > edges;
	Graph(int i, int j)
	{
		this -> i = i;
		this -> j = j;
	}

	void addEdge(int a, int b, int c)
	{
		edges.push_back((c, (a, b)));
	}
}