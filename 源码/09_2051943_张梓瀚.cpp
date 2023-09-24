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
	//Ԫ����ӣ���������ĩβ��
	void enqueue(const T& data);
	//Ԫ�س��ӣ�ɾȥ�����һ����㣩
	const T& dequeue();
	//�ж϶����Ƿ�Ϊ��
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
//e������ʼ������ʱ��, l���ٿ�ʼ��ʱ��, ve[i]�¼����緢����ʱ��, vl[i]�¼���ٷ�����ʱ��, indegree[i]��ʾ��������
int e, l, ve[maxn], vl[maxn], indegree[maxn];
myStack<int> s, t; //s����������������� ��t�������Ϊ���ջ�����������Ϊ��ĵ� 

/*��������*/
int TopologicalSort()
{
	int cnt = 0;
	for (int i = 1; i <= n; i++) //���Ϊ��ĵ���ջ 
		if (!indegree[i])
			t.push(i), cnt++;
	while (!t.empty()) {
		auto tmp = t.top();
		s.push(tmp);
		t.pop();
		//ȥ�������Ϊ��ĵ�������ıߣ���Ӧ���յ����ȼ�һ 
		int k = head[tmp];
		while (k != -1) {
			if (!--indegree[edge[k].y]) //�յ�Ķȼ�һ�������Ϊ�㣬��ջ 
			{
				t.push(edge[k].y);
				cnt++;
			}
			if (ve[edge[k].y] < ve[tmp] + edge[k].w) //�������������¼�����������ʱ��ve[i]����edge[k].y���·�� 
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

	//�����ڽӱ� 
	for (int i = 1; i <= m; ++i) 
	{
		cin >> edge[i].x >> edge[i].y >> edge[i].w;
		indegree[edge[i].y]++;  //�յ����ȼ�һ 
		edge[i].next = head[edge[i].x];
		head[edge[i].x] = i;
	}

	if (TopologicalSort() == 0)
	{
		cout << 0 << endl << "�����ڹؼ�·��,���ڻ�" << endl;
		return 0;
	}

	memset(vl, inf, sizeof(vl));
	vl[n] = ve[n]; //���һ���¼�����ٷ����¼��������緢��ʱ��
	while (!s.empty()) //������������vl[i]  
	{
		//��������ջ����ջ˳��Ϊ��������
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
			e = ve[i]; //�����ߵ����������飬�����߱�ʾ�Ļ�����緢��ʱ��͵������������������緢��ʱ�� 
			l = vl[edge[k].y] - edge[k].w; //�����ٷ���ʱ��
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
