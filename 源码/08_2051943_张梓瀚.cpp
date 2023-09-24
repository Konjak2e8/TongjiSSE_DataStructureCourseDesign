#pragma once
#include <iostream>
using namespace std;

constexpr int max_point_num = 1000, INF = 0x3f3f3f3f;

/*Prim*/
char node_name[100], st;
int g[max_point_num][max_point_num], dist[max_point_num], n, m, res;
bool in_stack[max_point_num];

int lowcost[max_point_num], closest[max_point_num];//lowcost[i]��ʾi�����뼯������ľ��룬closest[i]��ʾi��֮�����ߵĶ�����š�
int sum;//������С��������Ȩֵ�ܺ͡�
void Prim(int st) {
	//��ʼ����������ȡ������Ϣ��
	for (int i = 1; i <= n; i++) {
		if (i == st)
			lowcost[i] = 0;
		else
			lowcost[i] = g[st][i];
		closest[i] = st;
	}
	int minn, pos;//��¼���뼯������ĵ㣬minn������룬pos����õ���ձ��±ꡣ
	sum = 0;
	for (int i = 1; i <= n; i++) {
		minn = INF;
		for (int j = 1; j <= n; j++) {
			//�ҳ�����㼯������ıߡ�
			if (lowcost[j] != 0 && lowcost[j] < minn) {
				minn = lowcost[j];
				pos = j;
			}
		}
		if (minn == INF)
			break;
		sum += minn;//������С��������Ȩֵ֮�͡�
		lowcost[pos] = 0;//����㼯�ϡ�
		for (int j = 1; j <= n; j++) {
			//���ڵ㼯���м������µĵ㣬����Ҫȥ���¡�
			if (lowcost[j] != 0 && g[pos][j] < lowcost[j]) {
				lowcost[j] = g[pos][j];
				closest[j] = pos;//�ı��붥��j�����Ķ�����š�
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

//�߽ṹ��
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
	"**          �������ģ��ϵͳ          **",
	"========================================",
	"**         A -- ������������          **",
	"**         B -- ��ӵ����ı�          **",
	"**         C -- ������С������        **",
	"**         D -- ��ʾ��С������        **",
	"**         E -- �˳�����              **",
	"========================================",
};

const char input_prompt[10][100] =
{
	"��ѡ����� : ",
	"�����붥����� : ",
	"���������������� : \n",
	"�������������㼰�� : ",
	"��������ʼ���� : ",
};

constexpr char input_err[32] = "������������������\n";

//���������ʹ��*isValid����ָ���ж������Ƿ�Ϸ����粻�Ϸ�����д�����ʾ����������
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

//�ɶ������ƻ�ȡ������
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
		//������
		while (val < 0)
		{
			cout << "����߳���ӦΪ�������������������������㼰��" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> name1 >> name2 >> val;
		}
		if (name1 == '?')
			break;
		int point1 = get_vertex(name1), point2 = get_vertex(name2);
		if (point1 == -1 || point2 == -1)
		{
			cout << "���붥�㲻���ڣ������������������㼰��" << endl;
			continue;
		}
		//�ڽӱ���
		if (point1 > point2)
			my_swap(point1, point2);
		edges[++m].x = point1;
		edges[m].y = point2;
		edges[m].len = val;
		g[point1][point2] = g[point2][point1] = val;
	}
}
int main() {
	//��ӡ��ʼ��ʾ��Ϣ
	for (int i = 0; i < 8; i++) 
		cout << init_prompt[i] << endl;
	char opt = '0';
	int rt = 0;
	bool connected = true;
	while (opt != 'E') {
		//�����������������
		input<char>(opt, isOptValid, input_prompt[0]);
		switch (opt) {
		case 'A':
			//��Ӷ���
			input<int>(n, isNumPositive, input_prompt[1]);
			cout << input_prompt[2];
			for (int i = 1; i <= n; i++)
				cin >> node_name[i];
			break;
		case 'B':
			//��ӱ�
			inputEdges();
			break;
		case 'C':
			//������С��������������磩
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
					cerr << "����֮���޷���ͨ��" << endl;
					connected = false;
				}
			}
			if (connected)
				cout << "����Prim��С��������\n";
			break;
		case 'D':
			//��ӡ��С������
			printMST(rt);
			break;
		case 'E':
			//�˳�����
			break;
		default:
			break;
		}
		if (!connected)
			break;
	}
	return 0;
}