#include "matrix.h"
#include "List.h"
using namespace std;

g_matrix::g_matrix(int quantity_nodes, double density) :graph(quantity_nodes, static_cast<int>(density* quantity_nodes* (quantity_nodes - 1)), density), matrix(make_unique<unique_ptr<int[]>[]>(quantity_nodes))
{
	for (int ir_cell_nodes = 0; ir_cell_nodes < this->quantity_of_nodes; ir_cell_nodes++)
	{
		matrix[ir_cell_nodes] = make_unique<int[]>(quantity_nodes);
		for (int ir_column_nodes = 0; ir_column_nodes < this->quantity_of_nodes; ir_column_nodes++)
		{
			if (ir_cell_nodes == ir_column_nodes) matrix[ir_cell_nodes][ir_column_nodes] = 0;
			else matrix[ir_cell_nodes][ir_column_nodes] = inf;
		}
	}
}


void g_matrix::generate(const bool loops) const
{
	if (this->density == 1)
	{
		for (int ir_cell_nodes = 0; ir_cell_nodes < this->quantity_of_nodes; ir_cell_nodes++)
		{
			for (int ir_column_nodes = 0; ir_column_nodes < this->quantity_of_nodes; ir_column_nodes++)
			{
				if (ir_cell_nodes != ir_column_nodes)
				{
					int rand_worth = rand() % 50 - rv;
					while (rand_worth == 0) rand_worth = rand() % 50 - rv;
					matrix[ir_cell_nodes][ir_column_nodes] = rand_worth;
				}
			}
		}
	}
	
	else
	{
		int ir_edges = this->quantity_of_edges;
		while (ir_edges != 0)
		{
			int node_cell = rand() % this->quantity_of_nodes;
			int node_column = rand() % this->quantity_of_nodes;
			if (matrix[node_cell][node_column] == 0 || matrix[node_cell][node_column] == inf)
			{
				int rand_worth = rand() % 50 - rv;
				while (rand_worth == 0) rand_worth = rand() % 50 - rv;
				if (node_cell != node_column)
				{
					matrix[node_cell][node_column] = rand_worth;
					--ir_edges;
				}
				else if (loops)
				{
					matrix[node_cell][node_column] = rand_worth;
					--ir_edges;
				}
			}
		}
	}
}

void g_matrix::exhibit() const
{
	cout << "\n macierzowa reprezentacja grafu \n\n";
	for (int ir_node = 0; ir_node < this->quantity_of_nodes; ir_node++)	cout << "  " << ir_node;
	cout << endl << endl;
	for (int cell_node = 0; cell_node < this->quantity_of_nodes; cell_node++)
	{
		cout << cell_node << " *";
		for (int column_node = 0; column_node < this->quantity_of_nodes; column_node++)
		{
			int tmp_matrix_worth = matrix[cell_node][column_node];
			if (tmp_matrix_worth == inf) cout << "#";
			else cout << tmp_matrix_worth;
			cout << "  ";
		}
		cout << "*" << endl;
	}
	cout << endl;
}

const int g_matrix::read(const string file_title)
{
	ifstream in_file(file_title);
	if (!in_file.is_open())
	{
		cerr << " Input file is not open" << endl;
		return -1;
	}
	
	int run_nodes, run_node, end_node, worth;
	in_file >> this->quantity_of_edges >> this->quantity_of_nodes >> run_nodes;
	matrix = make_unique<unique_ptr<int[]>[]>(this->quantity_of_nodes);
	
	for (int ir_cell_nodes = 0; ir_cell_nodes < this->quantity_of_nodes; ir_cell_nodes++)
	{
		matrix[ir_cell_nodes] = make_unique<int[]>(this->quantity_of_nodes);
		for (int ir_column_nodes = 0; ir_column_nodes < this->quantity_of_nodes; ir_column_nodes++)
		{
			if (ir_cell_nodes == ir_column_nodes) matrix[ir_cell_nodes][ir_column_nodes] = 0;
			else matrix[ir_cell_nodes][ir_column_nodes] = inf;
		}
	}
	
	for (int ir_edge = 0; ir_edge < this->quantity_of_edges; ir_edge++)
	{
		in_file >> run_node >> end_node >> worth;
		matrix[run_node][end_node] = worth;
	}
	in_file.close();
	return run_nodes;
}

void g_matrix::build(const int begin) const
{
	ofstream outFile("OutInput.txt");
	if (!outFile.is_open())
	{
		cerr << " Output File not Created";
		return;
	}

	outFile << this->quantity_of_edges << " " << this->quantity_of_nodes << " " << begin << endl;
	for (int ir_cell_nodes = 0; ir_cell_nodes < this->quantity_of_nodes; ir_cell_nodes++)
	{
		for (int ir_column_nodes = 0; ir_column_nodes < this->quantity_of_nodes; ir_column_nodes++)
		{
			if (matrix[ir_cell_nodes][ir_column_nodes] != inf && matrix[ir_cell_nodes][ir_column_nodes] != 0) outFile << ir_cell_nodes << " " << ir_column_nodes << " " << matrix[ir_cell_nodes][ir_column_nodes] << endl;
		}
	}
	outFile.close();
}