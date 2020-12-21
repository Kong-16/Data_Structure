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
	// 5개의 Items가 출력될 때마다 줄바꾸기위해
	static int count = 0;
	os << "(" << item.x << "," << item.y << ")";
	count++;
	if ((count % 5) == 0) cout << endl;
	return os;
}

void Path(const int m, const int p){
	int count = 1; //node 갯수 셀 count 선언
	mark[1][1] = 1;
	stack<Items> stack;
	Items temp(1, 1, E); //현위치, 시작방향
	stack.push(temp);
	while (!stack.empty()) {
		temp = stack.top(); stack.pop(); //막혔을 경우 직전의 길과 다음 방향을 가진 item을 빼내고 다시 시도.
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while (d < 8) { 
			int g = i + mov[d].a; int h = j + mov[d].b;// (i,j) 에서 (g,h)로 이동
			if ((g == m) && (h == p)) {//출구에 도착했을 때,
				cout << stack;
				temp.x = i; temp.y = j; cout << " -> " << temp;
				temp.x = m; temp.y = p; cout << " -> " << temp << endl; //마지막 두 위치 삽입.
				cout << "#node visited = " << count << " out of " << m * p << endl; //방문 노드 수 출력
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) { // 이동 시
				mark[g][h] = 1; // 방문표시
				count++; //이동 할 때 마다 node추가됨. count +1해줌.
				temp.x = i; temp.y = j; temp.dir = d + 1; //현위치 , 다음 방향 저장 후 스택에 삽입
				stack.push(temp);
				i = g; j = h; d = N;
			}
			else d++; //다음 방향
		}
	}
	cout << "No path in maze." << endl; //탈출 불가능 할 경우
}
void getdata(istream& is, int& m, int& p){ // 자료화일을 읽어들여 maze에 저장한다.
		is >> m >> p;
		for (int i = 0; i < m + 2; i++) { maze[i][0] = 1; maze[i][p + 1] = 1; }
		for (int j = 1; j <= p; j++) { maze[0][j] = 1; maze[m + 1][j] = 1; }
		for (int i = 1; i <= m; i++) 
			for (int j = 1; j <= p; j++) 
				is >> maze[i][j];
}
*/