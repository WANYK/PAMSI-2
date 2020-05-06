#pragma once
#include <iostream>
#include "graph.h"
#include "BF_Algorithm.h"
using namespace std;

template<typename T>
string driver(int(&vs)[5], double(&dens)[4], int loops) 
{
	string result;
	for (auto density : dens) 
	{
		for (auto verticles : vs) 
		{
			double time = 0;
			for (int iter_loops = 0; iter_loops < loops; iter_loops++) 
			{
				shared_ptr<T> graph_ = make_shared<T>(verticles, density);
				int run_nodes = rand() % verticles;
				graph_->generate(false);
				time += algorythm(move(graph_), run_nodes);
			}
			result += to_string((time * 100 / loops) + 1);
			result += ",";
			cout << verticles << " wierzcholki wykonane " << endl;
		}
		cout << density << " gestosc wykonana " << endl;
	}
	return result;
}