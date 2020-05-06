#pragma once
#include<memory>
#include "graph.h"
using namespace std;

static int inf = 10000000;
static int ninf = -10000000;
class g_matrix : public graph 
{
	unique_ptr<unique_ptr<int[]>[]> matrix;
public:
	void generate(const bool loops) const override;
	void exhibit() const override;
	const int read(const string file_title) override;
	void build(const int begin) const override;
	const int getworth(int arg_one, int arg_two) const { return this->matrix[arg_one][arg_two]; }
	g_matrix(int quantity_nodes, double density);
	g_matrix() :graph() {};
};