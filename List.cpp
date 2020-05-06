#include "List.h"
using namespace std;

void list::generate(const bool loops) const
{
	if (this->density == 1)
	{
		int banner = 0;
		for (int ir_run_node = 0; ir_run_node < this->quantity_of_nodes; ir_run_node++)
		{
			for (int ir_end_node = 0; ir_end_node < this->quantity_of_nodes; ir_end_node++)
			{
				if (ir_run_node != ir_end_node)
				{
					int worth_connection = rand() % 50 - rv;
					while (worth_connection == 0) worth_connection = rand() % 50 - rv;
					add_edge(ir_run_node, ir_end_node, worth_connection, banner);
					banner++;
				}
			}
		}
	}
	
	else
	{
		for (int ir_edges = 0; ir_edges < this->quantity_of_edges; ir_edges++)
		{
			int rand_start = rand() % this->quantity_of_nodes;
			int rand_end = rand() % this->quantity_of_nodes;
			
			if (!this->check_existing(rand_start, rand_end))
			{
				int worth_connection = rand() % 50 - rv;
				while (worth_connection == 0) worth_connection = rand() % 50 - rv;
				if (rand_start != rand_end) add_edge(rand_start, rand_end, worth_connection, ir_edges);
				else if (loops) add_edge(rand_start, rand_end, worth_connection, ir_edges);
			}
		}
	}
}

void list::exhibit() const 
{
	cout << " \n \n Lista reprezentacji grafu \n \n ";
	
	for (int ir_start = 0; ir_start < this->quantity_of_nodes; ir_start++)
	{
		cout << ir_start;
		for (int ir_edge = 0; ir_edge < this->quantity_of_edges; ir_edge++)
		{
			if (this->in_edge[ir_edge].run_node == ir_start) cout << "->" << in_edge[ir_edge].end_node << "|" << in_edge[ir_edge].worth << "]";
		}
		cout << endl;
	}
	cout << endl;
}

const int list::read(const string file_title)
{
	ifstream in_file(file_title);
	if (!in_file.is_open())
	{
		cerr << "Plik nie zostal otwarty" << endl;
		return -1; 
	}
	int starting_node, begin, end_node, worth;
	in_file >> quantity_of_edges >> quantity_of_nodes >> starting_node;
	this->in_edge = new edge[quantity_of_edges];

	for (int ir_edge = 0; ir_edge < this->quantity_of_edges; ir_edge++)
	{
		in_file >> begin >> end_node >> worth;
		add_edge(begin, end_node, worth, ir_edge);
	}
	in_file.close();
	return starting_node;
}

void list::build(const int begin) const 
{
	ofstream out_file("out_input.txt");
	if (!out_file.is_open())
	{
		cerr << "Plik nie otwarty" << endl;
		return;
	}
	
	out_file << this->quantity_of_edges << this->quantity_of_nodes << begin << endl;
	for (int ir_edge = 0; ir_edge < quantity_of_edges; ir_edge++)
	{
		out_file << in_edge[ir_edge].run_node << " " << in_edge[ir_edge].end_node << " " << in_edge[ir_edge].worth << "\n";
	}
	out_file.close();
}

void list::add_edge(int run_node, int end_node, int worth, int banner) const
{
	this->in_edge[banner].run_node = run_node;
	this->in_edge[banner].end_node = end_node;
	this->in_edge[banner].worth = worth;
}

bool list::check_existing(int run_node, int end_node) const
{
	for (int ir_edges = 0; ir_edges < this->quantity_of_edges; ir_edges++)
	{
		if (this->in_edge[ir_edges].run_node == run_node && this->in_edge[ir_edges].end_node == end_node) return true;
	}
	return false;
}