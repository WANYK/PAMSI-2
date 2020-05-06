#pragma once
#include "graph.h"
using namespace std;

static int rv = -1;
class list : public graph
{
private:
	edge* in_edge;
public:
	void generate(const bool loops) const override;
	void exhibit() const override;
	const int read(const string file_title)  override;
	void build(const int begin) const override;
	const edge* get_edge() { return this->in_edge; }
	void add_edge(int run_node, int end_node, int worth, int banner) const;
	bool check_existing(int run_node, int end_node) const;
	~list() { delete[] in_edge; }
	list() :graph() {};
	list(int in_quantity_of_nodes, int in_density) 
		:graph(in_quantity_of_nodes, in_density* in_quantity_of_nodes* (in_quantity_of_nodes - 1), in_density), in_edge(new edge[in_density * in_quantity_of_nodes * (in_quantity_of_nodes - 1)]) {}
};