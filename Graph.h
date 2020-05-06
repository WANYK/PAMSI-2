#pragma once
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include "edge.h"
using namespace std;

class graph
{
protected:
	int quantity_of_nodes;
	int quantity_of_edges;
	double density;

public:
	const int return_node()
	{
		return this->quantity_of_nodes;
	}
	
	const int return_edge()
	{
		return this->quantity_of_edges;
	}

	virtual void generate(const bool loops) const = 0;
	virtual void exhibit() const = 0;
	virtual const int read(const string file_title) = 0;
	virtual void build(const int begin) const = 0;
	graph(int in_nodes, int in_edges, double in_density) : quantity_of_nodes(in_nodes), quantity_of_edges(in_edges), density(in_density) {};
	graph() {};
	virtual ~graph() {};
};