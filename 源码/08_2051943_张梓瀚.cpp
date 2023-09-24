#pragma once
#include <iostream>
using namespace std;

constexpr int max_point_num = 1000, INF = 0x3f3f3f3f;

/*Prim*/
char node_name[100], st;
int g[max_point_num][max_point_num], dist[max_point_num], n, m, res;
bool in_stack[max_point_num];

int lowcost[max_point_num], closest[max_point_num];//lowcost[i]表示i到距离集合最近的距离，closest[i]表示i与之相连边的顶点序号。
int sum;//计算最小生成树的权值总和。
void Prim(int st) {
	//初始化操作，获取基本信息。
	for (int i = 1; i <= n; i++) {
		if (i == st)
			lowcost[i] = 0;
		else
			lowcost[i] = g[st][i];
		closest[i] = st;
	}
	int minn, pos;//记录距离集合最近的点，minn代表距离，pos代表该点的终边下标。
	sum = 0;
	for (int i = 1; i <= n; i++) {
		minn = INF;
		for (int j = 1; j <= n; j++) {
			//找出距离点集合最近的边。
			if (lowcost[j] != 0 && lowcost[j] < minn) {
				minn = lowcost[j];
				pos = j;
			}
		}
		if (minn == INF)
			break;
		sum += minn;//计算最小生成树的权值之和。
		lowcost[pos] = 0;//加入点集合。
		for (int j = 1; j <= n; j++) {
			//由于点集合中加入了新的点，我们要去更新。
			if (lowcost[j] != 0 && g[pos][j] < lowcost[j]) {
				lowcost[j] = g[pos][j];
				closest[j] = pos;//改变与顶点j相连的顶点序号。
			}
		}
	}
}
void printMST(int s) {
	for (int i = 1; i <= n; i++) {
		if (i != s) {
			cout << node_name[closest[i]] << "-(" << g[closest[i]][i] << ")->" << node_name[i] << "    ";
		}
	}
	cout << '\n';
}

//边结构体
struct edge {
	int x, y, len;
	edge() {
		x = 0, y = 0, len = 0;
	}
	bool operator <(const edge& rhs) const {
		return len < rhs.len;
	}
	bool operator >(const edge& rhs) const {
		return len > rhs.len;
	}
	bool operator ==(const edge& rhs) const {
		return x == rhs.x && y == rhs.y && len == rhs.len;
	}
	edge& operator =(const edge& rhs) {
		if (rhs == *this)
			return *this;
		x = rhs.x;
		y = rhs.y;
		len = rhs.len;
		return *this;
	}
	edge(const int& _x, const int& _y, const int& _v) {
		x = _x;
		y = _y;
		len = _v;
	}
}edges[max_point_num * max_point_num];

template<typename T>
void my_swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

constexpr char init_prompt[10][100] =
{
	"**          电网造价模拟系统          **",
	"========================================",
	"**         A -- 创建电网顶点          **",
	"**         B -- 添加电网的边          **",
	"**         C -- 构造最小生成树        **",
	"**         D -- 显示最小生成树        **",
	"**         E -- 退出程序              **",
	"========================================",
};

const char input_prompt[10][100] =
{
	"请选择操作 : ",
	"请输入顶点个数 : ",
	"请输入各顶点的名称 : \n",
	"请输入两个顶点及边 : ",
	"请输入起始顶点 : ",
};

constexpr char input_err[32] = "输入有误，请重新输入\n";

//输入错误处理，使用*isValid函数指针判断输入是否合法，如不合法则进行错误提示并继续输入
template<typename T>
void input(T& t, bool(*isValid)(const T&), const char* prompt1, const char* prompt2 = input_err) {
	while (true) {
		cout << prompt1;
		cin >> t;
		if (isValid(t))
			break;
		cout << prompt2;
		cin.clear();
		cin.ignore(1024, '\n');
	}
}

bool isOptValid(const char& opt) {
	return opt >= 'A' && opt <= 'E';
}

bool isNumPositive(const int& num) {
	return num > 0;
}

bool isNameValid(const char& name) {
	return (name >= 'a' && name <= 'z') || (name >= 'A' && name <= 'Z');
}

//由顶点名称获取顶点编号
int get_vertex(char name) {
	for (int i = 1; i <= n; i++)
		if (node_name[i] == name)
			return i;
	return -1;
}

void inputEdges() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			g[i][j] = INF;
		dist[i] = INF;
	}
	char name1, name2;
	int val;
	while (true) {
		cout << input_prompt[3];
		cin >> name1 >> name2 >> val;
		//错误处理
		while (val < 0)
		{
			cout << "输入边长度应为正整数，请重新输入两个顶点及边" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> name1 >> name2 >> val;
		}
		if (name1 == '?')
			break;
		int point1 = get_vertex(name1), point2 = get_vertex(name2);
		if (point1 == -1 || point2 == -1)
		{
			cout << "输入顶点不存在，请重新输入两个顶点及边" << endl;
			continue;
		}
		//邻接表存边
		if (point1 > point2)
			my_swap(point1, point2);
		edges[++m].x = point1;
		edges[m].y = point2;
		edges[m].len = val;
		g[point1][point2] = g[point2][point1] = val;
	}
}
int main() {
	//打印初始提示信息
	for (int i = 0; i < 8; i++) 
		cout << init_prompt[i] << endl;
	char opt = '0';
	int rt = 0;
	bool connected = true;
	while (opt != 'E') {
		//输入操作并做错误处理
		input<char>(opt, isOptValid, input_prompt[0]);
		switch (opt) {
		case 'A':
			//添加顶点
			input<int>(n, isNumPositive, input_prompt[1]);
			cout << input_prompt[2];
			for (int i = 1; i <= n; i++)
				cin >> node_name[i];
			break;
		case 'B':
			//添加边
			inputEdges();
			break;
		case 'C':
			//生成最小生成树（造价网络）
			input<char>(st, isNameValid, input_prompt[4]);
			for (int i = 1; i <= n; i++) {
				if (st == node_name[i]) {
					rt = i;
					break;
				}
			}
			Prim(rt);
			for (int i = 1; i <= n; i++)
			{
				if (lowcost[i] != 0)
				{
					cerr << "城市之间无法连通！" << endl;
					connected = false;
				}
			}
			if (connected)
				cout << "生成Prim最小生成树！\n";
			break;
		case 'D':
			//打印最小生成树
			printMST(rt);
			break;
		case 'E':
			//退出程序
			break;
		default:
			break;
		}
		if (!connected)
			break;
	}
	return 0;
}