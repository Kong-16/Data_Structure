#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
void getdata(istream&, int&, int&);
void Path(int, int);
int main()
{
	int m, p; // m by p maze

		ifstream is;
		is.open("maze.txt");
		if (!is) { cerr << " does not exist\n"; exit(1); }
		cout << "For maze datafile (" << ")\n";
		getdata(is, m, p); is.close();
		Path(m, p);
}