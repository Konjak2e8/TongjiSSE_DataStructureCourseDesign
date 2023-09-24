#include <iostream>
#include <iomanip>
using namespace std;
#pragma once

#include<iostream>
using std::ostream;

template <typename T>
class List;

template <typename T>
class ListNode
{
	T* data;
	ListNode<T>* next;
public:
	//Ĭ�Ϲ��캯��
	ListNode<T>();
	//��ֵ���캯��
	ListNode<T>(const T& src);
	//��ȡ����
	const T& get_data() const;
	//��ȡ��̽��
	const ListNode<T>* get_next() const;
	//�޸�����
	void set_data(const T& src);
	friend class List<T>;
};

template <typename T>
ListNode<T>::ListNode()
{
	data = new T;
	next = nullptr;
}

template <typename T>
ListNode<T>::ListNode(const T& src)
{
	data = new T(src);
	next = nullptr;
}

template <typename T>
const T& ListNode<T>::get_data() const //�������ݵĳ�����
{
	return *data;
}

template <typename T>
const ListNode<T>* ListNode<T>::get_next() const
{
	return next;
}

template <typename T>
void ListNode<T>::set_data(const T& src)
{
	*data = src;
}

template <typename T>
class List
{
private:
	ListNode<T>* start;
	int size = 0;
	inline ListNode<T>* findLastByData(const T& tar);
	inline ListNode<T>* findLastByPos(int pos);
public:
	//Ĭ�Ϲ��캯��
	List();
	//��������
	~List();
	//��ȡͷ���
	const ListNode<T>* get_head();
	//����ָ��λ�õĽ��
	ListNode<T>* Locate(int pos);
	//������β��������
	inline void insert(const T& s);
	//���ض�λ�ò�����
	inline bool insert(const T& s, int pos);
	//�����������ݲ��ҽ��
	inline ListNode<T>* findByData(const T& s);
	//�����������е�λ�ò��ҽ��
	inline ListNode<T>* findByPos(int tarID);
	//�޸Ľ������
	inline void modify(T tar, const T& new_s);
	//ɾ��ָ��λ�õĽ��
	inline void remove(int tarID);
	//ɾ��ָ�����ݵĽ��
	inline void remove(const T& tar);
	//�����ӡ�������н��
	inline void printAll(ostream& os = cout);
	//��ȡ������
	int get_list_size();
	//�ж������Ƿ�Ϊ��
	bool is_empty();
};

template<typename T>
inline ListNode<T>* List<T>::findLastByData(const T& tar)
{
	ListNode<T>* s1 = start;
	while (s1->next != nullptr)
	{
		if (*s1->next->data == tar)
		{
			return s1;
		}
		s1 = s1->next;
	}
	return nullptr;
}

template <typename T>
List<T>::~List()
{
	ListNode<T>* node = start;
	while (node != nullptr)
	{
		auto tmp = node->next;
		delete node;
		node = tmp;
	}
	node = 0;
}

//����ͷ���ĳ�����
template <typename T>
const ListNode<T>* List<T>::get_head()
{
	return start;
}

template<typename T>
inline ListNode<T>* List<T>::findLastByPos(int pos)
{
	ListNode<T>* s1 = start;
	while (--pos)
	{
		if (s1 == nullptr)
		{
			throw("Requested position does not exist");
			break;
		}
		s1 = s1->next;
	}
	return s1;
}

template<typename T>
List<T>::List()
{
	start = new ListNode<T>;
}

template <typename T>
ListNode<T>* List<T>::Locate(int pos)
{
	if (pos < 0)
		return nullptr;
	ListNode<T>* s1 = start;
	int k = 0;
	while (s1 != nullptr && k < pos)
	{
		s1 = s1->next;
		k++;
	}
	return s1;
}

template<typename T>
inline void List<T>::insert(const T& s)
{
	ListNode<T>* s1 = start;
	while (s1->next != nullptr)
	{
		s1 = s1->next;
	}
	ListNode<T>* s2 = new ListNode<T>(s);
	s2->next = nullptr;
	s1->next = s2;
	size++;
}

template <typename T>
bool List<T>::insert(const T& s, int pos)
{
	if (pos <= 0)
	{
		return false;
	}
	ListNode<T>* s1 = findLastByPos(pos);
	ListNode<T>* s2 = new ListNode<T>(s);
	if (s2 == nullptr)
	{
		return false;
	}
	s2->next = s1->next;
	s1->next = s2;
	size++;
	return true;
}

template <typename T>
ListNode<T>* List<T>::findByData(const T& tar)
{
	ListNode<T>* last_node = findLastByData(tar);
	if (last_node != nullptr)
		return findLastByData(tar)->next;
	return nullptr;
}

template <typename T>
ListNode<T>* List<T>::findByPos(int tarID)
{
	return findLastByPos(tarID)->next;
}

template <typename T>
void List<T>::modify(T tar, const T& new_s)
{
	ListNode<T>* s1 = findByData(tar);
	if (s1 != nullptr)
	{
		*s1->data = new_s;
	}
}

template <typename T>
void List<T>::remove(int tarID)
{
	if (tarID <= 0)
	{
		throw("Invalid ID");
	}
	ListNode<T>* s1 = findLastByPos(tarID);
	ListNode<T>* tmp = s1->next;
	s1->next = tmp->next;
	delete tmp;
	size--;
}

template <typename T>
void List<T>::remove(const T& tar)
{
	//�ҵ���ɾ������ǰ�����
	ListNode<T>* s1 = findLastByData(tar);
	ListNode<T>* tmp = s1->next;
	//ɾ���ý��
	s1->next = tmp->next;
	delete tmp;
	size--; //�����ȼ�һ
}

template <typename T>
void List<T>::printAll(ostream& os)
{
	ListNode<T>* s = start->next;
	while (s != nullptr)
	{
		os << *s->data;
		s = s->next;
	}
}

template <typename T>
int List<T>::get_list_size()
{
	return size;
}

template <typename T>
bool List<T>::is_empty()
{
	return size == 0;
}

//����List��ʵ�ֵ���ʽջ
template<typename T>
class myStack : private List<T> {
public:
	myStack();
	//������ͷ����ջ����������
	void push(const T& data);
	//���ص�һ����������
	const T top();
	//ɾ����һ�����
	void pop();
	//�ж�ջ�Ƿ�Ϊ��
	bool empty();
	//��ȡջ�Ĵ�С
	int size();
};

template <typename T>
myStack<T>::myStack()
{

}


template <typename T>
void myStack<T>::push(const T& data)
{
	this->insert(data, 1);
}

template <typename T>
const T myStack<T>::top()
{
	return this->get_head()->get_next()->get_data();
}

template <typename T>
void myStack<T>::pop()
{
	this->remove(1);
}

template <typename T>
bool myStack<T>::empty()
{
	return this->is_empty();
}

template <typename T>
int myStack<T>::size()
{
	return this->get_list_size();
}

const int MAP_SIZE = 6;
const char Map[MAP_SIZE + 2][MAP_SIZE + 2] = 
{
	{'#','#','#','#','#','#','#','#'},
	{'#','x','0','x','0','0','x','#'},
	{'#','x','0','x','x','0','x','#'},
	{'#','x','0','x','x','x','x','#'},
	{'#','x','0','x','0','x','0','#'},
	{'#','x','x','x','0','x','x','#'},
	{'#','0','0','0','0','0','x','#'},
	{'#','#','#','#','#','#','#','#'}
};
void PrintMap()
{
	cout << "�Թ���ͼ��\n\n     ";
	for (int i = 0; i < MAP_SIZE + 2; i++) cout << i << "�� ";
	cout << endl << endl;
	for (int i = 0; i < MAP_SIZE + 2; i++) 
	{
		cout << i << "�� ";
		for (int j = 0; j < MAP_SIZE + 2; j++) 
			cout << setw(4) << Map[i][j];
		cout << endl << endl;
	}
}
bool vis[MAP_SIZE][MAP_SIZE];

//�������
struct Point
{
	int x, y;
	bool operator == (const Point& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	Point operator + (Point& rhs)
	{
		Point pt = { x + rhs.x,y + rhs.y };
		return pt;
	}
};

Point operator + (const Point& p1, const Point& p2)
{
	Point pt = { p1.x + p2.x,p1.y + p2.y };
	return pt;
}

bool isReachable(Point pnt)
{
	return Map[pnt.x][pnt.y] == 'x';
}

const Point step[4] = { {1,0},{0,1},{-1,0},{0,-1} };

myStack<Point>stk;

//�����������
bool search(Point start, Point end)
{
	bool** visited = new bool* [MAP_SIZE + 1];
	for (int i = 0; i <= MAP_SIZE; i++)
	{
		visited[i] = new bool[MAP_SIZE + 1];
		memset(visited[i], 0, (MAP_SIZE + 1) * sizeof(bool));
	}

	//�����ջ
	stk.push(start);
	Point current;
	while (!stk.empty())
	{
		current = stk.top();
		if (current == end)
			break;
		bool no_way = true;
		//�ж��ĸ������Ƿ��ܵ�����ܵ����򽫸÷����ϵĵ���ջ
		for (int i = 0; i < 4; i++)
		{
			Point next = current + step[i];
			if (isReachable(next) && !visited[next.x][next.y])
			{
				stk.push(next);
				visited[next.x][next.y] = true;
				no_way = false;
				break;
			}
		}
		//��û�пɴ�ķ���˵����ǰ��û��ǰ�����ܣ����䵯ջ
		if (no_way)
			stk.pop();
	}

	for (int i = 0; i <= MAP_SIZE; i++)
		delete[] visited[i];
	delete[] visited;

	if (stk.empty())
		return false;
	return true;
}

void print_path()
{
	Point tmp = stk.top();
	stk.pop();
	if (!stk.empty())
	{
		//�ݹ����·��
		print_path();
		cout << " ---> ";
	}
	cout << '<' << tmp.x << ',' << tmp.y << '>';
}
int main()
{
	PrintMap();
	Point st = { 1,1 };
	Point ed = { MAP_SIZE,MAP_SIZE };
	search(st, ed);
	cout << endl;
	if (stk.size())
	{
		cout << "·����";
		cout << endl << endl;
		print_path();
	}
	else
		cout << "û�пɴ�·��" << endl;
	return 0;
}