/* 设计一个算法，给一个起点给一个终点，设计一条路走出来迷宫
   0表示通道，1表示围墙 构建矩阵。*/

#include<iostream>
#include<stack>
#include<queue>
#include<Eigen/Dense>
using namespace std;

class Coord
{
public:
	Coord(int dx, int dy)
	{
		this->x = dx;
		this->y = dy;
	}
	int x, y;
};

void Path_Depth(Coord c1, Coord c2, Eigen::Matrix<int, 10, 10>& m)  // c1（x1,y1)表示起点，c2(x2,y2)表示终点
{
	// 把起点入栈
	stack<Coord> st;
	st.push(c1);
	Coord CurNode = st.top(); //当前节点位置
	// 栈空表示没有路径，如果栈不空则循环
	while (!st.empty())
	{
		CurNode = st.top();
		// 判断当前是不是终点，是的话打印栈内所有节点
		if ((CurNode.x == c2.x) && (CurNode.y == c2.y))
		{
			cout << endl << "************" << endl;
			while (!st.empty())
			{
				printf("(%d,%d)\n", st.top().x, st.top().y);
				st.pop();
			}
		}
		else 
		{
			// 向上
			if (m(st.top().x - 1, st.top().y) == 0)
			{
				CurNode.x = st.top().x - 1;
				st.push(CurNode);
				continue;
			}
			// 向右
			else if (m(st.top().x, st.top().y + 1) == 0)
			{
				CurNode.y = st.top().y + 1;
				st.push(CurNode);
				continue;
			}
			// 向下
			else if (m(st.top().x + 1, st.top().y) == 0)
			{
				CurNode.x = st.top().x + 1;
				st.push(CurNode);
				continue;
			}
			// 向左
			else if (m(st.top().x, st.top().y - 1) == 0)
			{
				CurNode.y = st.top().y - 1;
				st.push(CurNode);
				continue;
			}
			else
			{
				// 如果当前节点上下左右全部撞墙，则把这个节点释放掉,并把这个节点的值改为8
				m(st.top().x, st.top().y) = (8, 8);
				st.pop();
				continue;
			}
		}
	};
	std::cout << endl << "迷宫现在为： " << endl << m << endl;
};

int main()
{
	Eigen::Matrix<int,10,10> maze;
	maze << 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1;

	cout << "迷宫(0:通路，1：墙)是：" << endl << maze << endl;

	Coord begin(1, 1);
	Coord final(8, 8);
	//stack<Coord> s;
	//s.push(begin);
	//s.push(final);
	Path_Depth(begin, final, maze);

	system("pause");
	return 0;	 
}