#include"subway.h"
#include<fstream>
int main()
{
	Graph g;
	int numLine;
	int line1, line2;
	string src, dst;
	
	fstream fin("stations.txt");
	fin >> numLine;
	//������ �޴� ����
	g.makeGraph(fin, numLine);
	fin.close();
	fstream fin2("input.txt");
	fin2 >> line1 >> src;
	fin2 >> line2 >> dst;
	fin2.close();
	g.searchPath(line1, src, line2, dst);

	return 0;
}