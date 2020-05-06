#include <iostream>
#include "driver.h"
using namespace std;

int main(){
	int vs[5] = { 5,25,50,75,100 };
	double dens[4] = { 0.25,0.5,0.75,1.00 };
	const int loop = 100;
	ofstream file("times.txt");
	
	if (!file.is_open()) 
	{
		cerr << "wyjœcie nie otwarte" << endl;
		return 1;
	}

	file << driver<list>(vs, dens, loop); 
	cout << "lista zrobiona\n" << endl;
	cout << " ";
	file << driver<g_matrix>(vs, dens, loop);
	cout << "macierz wykonana" << endl;
	file.close();
	return 0;
}