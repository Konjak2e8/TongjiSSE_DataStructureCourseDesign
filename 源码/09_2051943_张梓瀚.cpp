#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

template <typename T>
class List;

template <typename T>
class ListNode
{
	T* data;
	ListNode<T>* next;
public:
	//默认构造函数
	ListNode<T>();
	//赋值构造函数
	ListNode<T>(const T& src);
	//获取数据
	const T& get_data() const;
	//获取后继结点
	const ListNode<T>* get_next() const;
	//修改数据
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
const T& ListNode<T>::get_data() const //返回数据的常引用
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
	//默认构造函数
	List();
	//析构函数
	~List();
	//获取头结点
	const ListNode<T>* get_head();
	//查找指定位置的结点
	ListNode<T>* Locate(int pos);
	//向链表尾部插入结点
	inline void insert(const T& s);
	//向特定位置插入结点
	inline bool insert(const T& s, int pos);
	//根据数据内容查找结点
	inline ListNode<T>* findByData(const T& s);
	//根据在链表中的位置查找结点
	inline ListNode<T>* findByPos(int tarID);
	//修改结点数据
	inline void modify(T tar, const T& new_s);
	//删除指定位置的结点
	inline void remove(int tarID);
	//按序打印链表所有结点
	inline void printAll(ostream& os = cout);
	//获取链表长度
	int get_list_size();
	//判断链表是否为空
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

//返回头结点的常引用
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
			throw("Requested position does not exist");
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

//基于List类实现的链式栈
template<typename T>
class myStack : private List<T> {
public:
	myStack();
	//向链表头部（栈顶）插入结点
	void push(const T& data);
	//返回第一个结点的数据
	const T top();
	//删除第一个结点
	void pop();
	//判断栈是否为空
	bool empty();
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

template<typename T>
class Queue : List<T>
{
	T head;
public:
	//元素入队（插入链表末尾）
	void enqueue(const T& data);
	//元素出队（删去链表第一个结点）
	const T& dequeue();
	//判断队列是否为空
	bool isEmpty();
};

template <typename T>
void Queue<T>::enqueue(const T& data)
{
	this->insert(data);
}

template <typename T>
const T& Queue<T>::dequeue()
{
	head = this->get_head()->get_next()->get_data();
	this->remove(1);
	return head;
}

template <typename T>
bool Queue<T>::isEmpty()
{
	return this->is_empty();
}

const int maxm = 20;
const int maxn = 100;
const int inf = 0x3f3f3f3f;
struct Edge {
	int x, y, w;
	int next;
	Edge()
	{
		x = 0, y = 0, w = 0, next = -1;
	}
	Edge(int _x, int _y, int _w, int _next) :x(_x), y(_y), w(_w), next(_next) {}
	Edge(const Edge&rhs)
	{
		x = rhs.x, y = rhs.y, w = rhs.w, next = rhs.next;
	}
}edge[maxm];
int n, m;
int head[maxn];
//e代表活动开始的最早时间, l活动最迟开始的时间, ve[i]事件最早发生的时间, vl[i]事件最迟发生的时间, indegree[i]表示顶点的入度
int e, l, ve[maxn], vl[maxn], indegree[maxn];
myStack<int> s, t; //s代表逆序的拓扑排序 ，t代表入度为零的栈，里面存放入度为零的点 

/*拓扑排序*/
int TopologicalSort()
{
	int cnt = 0;
	for (int i = 1; i <= n; i++) //入度为零的点入栈 
		if (!indegree[i])
			t.push(i), cnt++;
	while (!t.empty()) {
		auto tmp = t.top();
		s.push(tmp);
		t.pop();
		//去掉与入度为零的点的相连的边，对应的终点的入度减一 
		int k = head[tmp];
		while (k != -1) {
			if (!--indegree[edge[k].y]) //终点的度减一后，如果度为零，入栈 
			{
				t.push(edge[k].y);
				cnt++;
			}
			if (ve[edge[k].y] < ve[tmp] + edge[k].w) //正拓扑排序求事件发生的最早时间ve[i]，到edge[k].y的最长路径 
				ve[edge[k].y] = ve[tmp] + edge[k].w;
			k = edge[k].next;
		}
	}
	if (cnt < n)
		return 0;
	return 1;
}


int main()
{
	memset(head, -1, sizeof(head));
	cin >> n >> m;

	//建立邻接表 
	for (int i = 1; i <= m; ++i) 
	{
		cin >> edge[i].x >> edge[i].y >> edge[i].w;
		indegree[edge[i].y]++;  //终点的入度加一 
		edge[i].next = head[edge[i].x];
		head[edge[i].x] = i;
	}

	if (TopologicalSort() == 0)
	{
		cout << 0 << endl << "不存在关键路径,存在环" << endl;
		return 0;
	}

	memset(vl, inf, sizeof(vl));
	vl[n] = ve[n]; //最后一个事件的最迟发生事件等于最早发生时间
	while (!s.empty()) //逆拓扑排序求vl[i]  
	{
		//拓扑序入栈，出栈顺序即为逆拓扑序
		auto tmp = s.top();
		s.pop();
		int k = head[tmp];
		while (k != -1) 
		{
			if (vl[tmp] > vl[edge[k].y] - edge[k].w) 
				vl[tmp] = vl[edge[k].y] - edge[k].w;
			k = edge[k].next;
		}
	}
	Queue<Edge>critical_activities;
	for (int i = 1; i <= n; i++) 
	{
		int k = head[i];
		while (k != -1) 
		{
			e = ve[i]; //该条边的起点代表事情，该条边表示的活动的最早发生时间就等于起点代表的事情的最早发生时间 
			l = vl[edge[k].y] - edge[k].w; //活动的最迟发生时间
			if (l == e)
				critical_activities.enqueue({ i,edge[k].y,edge[k].w,-1 });/*, total_time += edge[k].w;*/
			k = edge[k].next;
		}
	}
	cout << ve[n] << endl;
	Edge* edge1;
	while (!critical_activities.isEmpty())
	{
		edge1 = new Edge(critical_activities.dequeue());
		cout << edge1->x << "->" << edge1->y << endl;
	}
	return 0;
}
