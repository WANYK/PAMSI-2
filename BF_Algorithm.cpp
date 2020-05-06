#include "BF_Algorithm.h"
using namespace std;

double algorythm(shared_ptr<list> graph, int run_nodes)
{
	string* path_stoarge = new string[graph->return_node()];
	auto start_time = chrono::high_resolution_clock::now();
	int* length_stoarge = new int[graph->return_node()];
	for (int ir_nodes = 0; ir_nodes < graph->return_node(); ir_nodes++) length_stoarge[ir_nodes] = inf;
	length_stoarge[run_nodes] = 0;
	for (int ir_nodes = 1; ir_nodes < graph->return_node(); ir_nodes++)
	{
		for (int ir_edges = 0; ir_edges < graph->return_edge(); ir_edges++)
		{
			int tem_run_node = graph->get_edge()[ir_edges].run_node;
			int temend_node = graph->get_edge()[ir_edges].end_node;
			int tem_worth = graph->get_edge()[ir_edges].worth;
			if (length_stoarge[tem_run_node] + tem_worth < length_stoarge[temend_node]) length_stoarge[temend_node] = length_stoarge[tem_run_node] + tem_worth;
			path_stoarge[temend_node].clear();
			path_stoarge[temend_node].append(path_stoarge[tem_run_node] + to_string(tem_run_node) + "->");
		}
	}
	
	for (int ir_nodes = 1; ir_nodes < graph->return_node(); ir_nodes++)
	{
		for (int ir_edges = 0; ir_edges < graph->return_edge(); ir_edges++)
		{
			int tem_run_node = graph->get_edge()[ir_edges].run_node;
			int temend_node = graph->get_edge()[ir_edges].end_node;
			int tem_worth = graph->get_edge()[ir_edges].worth;
			if (length_stoarge[tem_run_node] + tem_worth < length_stoarge[temend_node])
			{
				if (length_stoarge[tem_run_node] > inf / 2) length_stoarge[tem_run_node] = inf;
				else length_stoarge[temend_node] = ninf;
			}
			else if (length_stoarge[tem_run_node] > inf / 2) length_stoarge[tem_run_node] = inf;
		}
	}

	auto end_time = chrono::high_resolution_clock::now();
	results(move(path_stoarge), move(length_stoarge), graph->return_node(), run_nodes);
	delete[] path_stoarge;
	delete[] length_stoarge;
	return chrono::duration<double, milli>(end_time - start_time).count();
}

double algorythm(shared_ptr<g_matrix> graph, int run_nodes)
{
	string* path_stoarge = new string[graph->return_node()];
	auto start_time = chrono::high_resolution_clock::now();
	int* length_stoarge = new int[graph->return_node()];

	for (int ir_nodes = 0; ir_nodes < graph->return_node(); ir_nodes++) length_stoarge[ir_nodes] = inf;
	length_stoarge[run_nodes] = 0;
	for (int ir_nodes = 1; ir_nodes < graph->return_node(); ir_nodes++)
	{
		for (int int_cell_node = 0; int_cell_node < graph->return_node(); int_cell_node++)
		{
			for (int int_column_node = 0; int_column_node < graph->return_node(); int_column_node++)
			{
				int tem_run_node = int_cell_node;
				int temend_node = int_column_node;
				int tem_worth = graph->getworth(int_cell_node, int_column_node);
				
				if (length_stoarge[tem_run_node] + tem_worth < length_stoarge[temend_node])
				{
					length_stoarge[temend_node] = length_stoarge[run_nodes] + tem_worth;
					path_stoarge[temend_node].clear();
					path_stoarge[temend_node].append(path_stoarge[tem_run_node] + to_string(tem_run_node) + "->");
				}
			}
		}
	}
	
	for (int ir_nodes = 1; ir_nodes < graph->return_node(); ir_nodes++)
	{
		for (int int_cell_node = 0; int_cell_node < graph->return_node(); int_cell_node++)
		{
			for (int int_column_node = 0; int_column_node < graph->return_node(); int_column_node++)
			{
				int tem_run_node = int_cell_node;
				int temend_node = int_column_node;
				int tem_worth = graph->getworth(int_cell_node, int_column_node);
				
				if (length_stoarge[tem_run_node] + tem_worth < length_stoarge[temend_node])
				{
					if (length_stoarge[tem_run_node] > inf / 2) length_stoarge[tem_run_node] = inf;
					else if (tem_worth == inf) continue;
					else length_stoarge[temend_node] = ninf;		
				}
				else if (length_stoarge[tem_run_node] > inf / 2) length_stoarge[tem_run_node] = inf;	
			}
		}
	}
	
	auto end_time = chrono::high_resolution_clock::now();
	results(move(path_stoarge), move(length_stoarge), graph->return_node(), run_nodes);
	delete[] path_stoarge;
	delete[] length_stoarge;
	return chrono::duration<double, milli>(end_time - start_time).count();
}

void results(string path_string[], int length_stoarge[], int quantity_nodes, int run_nodes)
{
	ofstream results("Results.txt");
	results << "\n           Wyniki          \n\n";
	results << "Poczatkowy wezel to:  " << run_nodes << endl;
	
	for (int ir_nodes = 0; ir_nodes < quantity_nodes; ir_nodes++)
	{
		if (length_stoarge[ir_nodes] == inf)
		{
			results << ir_nodes << "-> inf" << endl;
			continue;
		}
		
		else if (length_stoarge[ir_nodes] == ninf)
		{
			results << ir_nodes << "-> -inf" << endl;
			continue;
		}
		
		else
		{
			results << ir_nodes << "->" << length_stoarge[ir_nodes] << endl;
		}

		results << "  ";

		if ((length_stoarge[ir_nodes] >= 100 && length_stoarge[ir_nodes] < 1000) || (-100 > length_stoarge[ir_nodes] && length_stoarge[ir_nodes] <= -10)) 
		{
			results << " Najkrotsza sciezka: " << path_string[ir_nodes] << ir_nodes;
		}
		
		else if (0 <= length_stoarge[ir_nodes] && length_stoarge[ir_nodes] < 10) 
		{
			results << " Najkrotsza sciezka: " << path_string[ir_nodes] << ir_nodes;
		}
		
		else if ((length_stoarge[ir_nodes] >= 10 && length_stoarge[ir_nodes] < 100) || (-10 < length_stoarge[ir_nodes] && length_stoarge[ir_nodes] < 0)) 
		{
			results << " Najkrotsza sciezka: " << path_string[ir_nodes] << ir_nodes;
		}
		
		else 
		{
			results << " Najkrotsza sciezka: " << path_string[ir_nodes] << ir_nodes;
		}
		
	}
	results << endl;
}