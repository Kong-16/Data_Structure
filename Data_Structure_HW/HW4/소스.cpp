#include <iostream>
#include <stack>

using namespace std;
const int MAXSIZE = 100; // up to 100 by 100 maze allowed
bool maze[MAXSIZE + 2][MAXSIZE + 2];
bool mark[MAXSIZE + 1][MAXSIZE + 1] = { 0 };

enum directions { N, NE, E, SE, S, SW, W, NW };
struct offsets
{   int a, b;
} mov[8] = { (-1,0),(-1,1),(0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1) };

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
ostream& operator<<(ostream& os, Items& item) {
    // 5개의 Items가 출력될 때마다 줄바꾸기위해
    static int count = 0;
    os << "(" << item.x << "," << item.y << ")";
    count++;
    if ((count % 5) == 0) cout << endl;
    return os;
}

void Path(const int m, const int p)
{

    // (1,1) start
    mark[1][1] = 1;

    stack<Items> hjstack;
    //m * p 개의 items를 입력받을 수 있는 stack생성

    Items tmp(1, 1, E);
    // (1,1) 에서 동쪽방향으로 가도록 하는 Item객체 tmp 생성

    hjstack.push(tmp);
    // tmp 아이템을 stack에 삽입

    int nodes_visited = 1;

    while (!hjstack.empty())
    {
        tmp = hjstack.top();
        hjstack.pop();

        int i = tmp.x; int j = tmp.y; int d = tmp.dir;
        // 동쪽부터 탐색

        while (d < 8)
            //모든방향 탐색
        {
            int g = i + mov[d].a;
            int h = j + mov[d].b;

            if ((g == m) && (h == p))
                //success
            {
                cout << hjstack;
                tmp.x = i; tmp.y = j; cout << "->" << tmp;
                tmp.x = m; tmp.y = p; cout << "->" << tmp << endl;
                cout << "#nodes visited = " << hjstack.size() << " out of " << nodes_visited << endl;
                return;
                //종료
            }

            if ((!maze[g][h]) && (!mark[g][h]))
                // 지나온 길이 아니라면 , 그리고 합당합 길이라면...? 
            {
                mark[g][h] = 1;
                // 지나온 위치는 '1' 로 mark

                tmp.x = i; tmp.y = j; tmp.dir = d + 1;
                hjstack.push(tmp);
                nodes_visited++;
                i = g; j = h; d = N;

            }
            else d++;
        }
        // while문 종료
    }
    cout << "No path in maze" << endl;
}

void getdata(istream& is, int& m, int& p) { // 자료화일을 읽어들여 maze에 저장한다.
    is >> m >> p;
    for (int i = 0; i < m + 2; i++) { maze[i][0] = 1; maze[i][p + 1] = 1; }
    for (int j = 1; j <= p; j++) { maze[0][j] = 1; maze[m + 1][j] = 1; }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= p; j++)
            is >> maze[i][j];
}
