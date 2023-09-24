#include <iostream>
using std::ostream;
using std::cin;
using std::cout;

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
	inline void print_all(ostream& os = cout);
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
	return start->get_next();
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
void List<T>::print_all(ostream& os)
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

template<typename T>
class Queue : List<T>
{
	T head = 0;
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
	head = this->get_head()->get_data();
	this->remove(1);
	return head;
}

template <typename T>
bool Queue<T>::isEmpty()
{
	return this->is_empty();
}


int main()
{
	Queue<int> q1, q2;
	int num, id;
	std::cin >> num;
	for (int i = 1; i <= num; i++)
	{
		cin >> id;
		//先将顾客分别入队
		if (id & 1)
			q1.enqueue(id);
		else
			q2.enqueue(id);
	}
	while (!(q1.isEmpty() && q2.isEmpty()))
	{
		//若所在队列不为空，按题目描述依次让完成业务的顾客出队并输出
		if (!q1.isEmpty())
			cout << q1.dequeue() << ' ';
		if (!q1.isEmpty())
			cout << q1.dequeue() << ' ';
		if (!q2.isEmpty())
			cout << q2.dequeue() << ' ';
	}
	return 0;
}