/*#include <iostream>
#include <stack>

using namespace std;
const int MAXSIZE = 100; // up to 100 by 100 maze allowed
bool maze[MAXSIZE + 2][MAXSIZE + 2];
bool mark[MAXSIZE + 1][MAXSIZE + 1] = { 0 };

enum directions { N, NE, E, SE, S, SW, W, NW };
struct offsets
{
	int a, b;
} mov[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

struct Items {
Items(int xx = 0, int yy = 0, int dd = 0) : x(xx), y(yy), dir(dd) {}
int x, y, dir;
};

template <class T>
ostream& operator<< (ostream& os, stack<T>& s) {
	stack<T> s2;
	while (!s.empty()) { s2.push(s.top()); s.pop(); }
	while (!s2.empty()) { os << "->" << s2.top(); s.push(s2.top());  s2.pop(); }
	return os;
}
ostream& operator<<(ostream& os, Items& item){
	// 5���� Items�� ��µ� ������ �ٹٲٱ�����
	static int count = 0;
	os << "(" << item.x << "," << item.y << ")";
	count++;
	if ((count % 5) == 0) cout << endl;
	return os;
}

void Path(const int m, const int p){
	int count = 1; //node ���� �� count ����
	mark[1][1] = 1;
	stack<Items> stack;
	Items temp(1, 1, E); //����ġ, ���۹���
	stack.push(temp);
	while (!stack.empty()) {
		temp = stack.top(); stack.pop(); //������ ��� ������ ��� ���� ������ ���� item�� ������ �ٽ� �õ�.
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while (d < 8) { 
			int g = i + mov[d].a; int h = j + mov[d].b;// (i,j) ���� (g,h)�� �̵�
			if ((g == m) && (h == p)) {//�ⱸ�� �������� ��,
				cout << stack;
				temp.x = i; temp.y = j; cout << " -> " << temp;
				temp.x = m; temp.y = p; cout << " -> " << temp << endl; //������ �� ��ġ ����.
				cout << "#node visited = " << count << " out of " << m * p << endl; //�湮 ��� �� ���
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) { // �̵� ��
				mark[g][h] = 1; // �湮ǥ��
				count++; //�̵� �� �� ���� node�߰���. count +1����.
				temp.x = i; temp.y = j; temp.dir = d + 1; //����ġ , ���� ���� ���� �� ���ÿ� ����
				stack.push(temp);
				i = g; j = h; d = N;
			}
			else d++; //���� ����
		}
	}
	cout << "No path in maze." << endl; //Ż�� �Ұ��� �� ���
}
void getdata(istream& is, int& m, int& p){ // �ڷ�ȭ���� �о�鿩 maze�� �����Ѵ�.
		is >> m >> p;
		for (int i = 0; i < m + 2; i++) { maze[i][0] = 1; maze[i][p + 1] = 1; }
		for (int j = 1; j <= p; j++) { maze[0][j] = 1; maze[m + 1][j] = 1; }
		for (int i = 1; i <= m; i++) 
			for (int j = 1; j <= p; j++) 
				is >> maze[i][j];
}
*/