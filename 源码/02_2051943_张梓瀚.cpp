#include<string>
#include<iostream>
#include<iomanip>
using namespace std;

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
	const T& get_data();
	//修改数据
	void set_data(const T& src);
	//获取后继结点
	ListNode<T>* get_next();
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
const T& ListNode<T>::get_data() //返回数据的常引用
{
	return *data;
}


template <typename T>
void ListNode<T>::set_data(const T& src)
{
	*data = src;
}

template <typename T>
ListNode<T>* ListNode<T>::get_next()
{
	return next;
}


template <typename T>
class List
{
private:
	ListNode<T>* start;
	ListNode<T>* end;
	int size = 0;
	inline ListNode<T>* findLastByData(const T& tar);
	inline ListNode<T>* findLastByPos(int pos);
public:
	//默认构造函数
	List();
	//析构函数
	~List();
	//获取头结点
	ListNode<T>* get_head() const;
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
	//删除指定内容的结点
	inline void remove(const T& tar);
	//按序打印链表所有结点
	inline void printAll(ostream& os = cout);
	//获取链表长度
	int get_list_size();
};

template <typename T>
ListNode<T>* List<T>::get_head() const
{
	return start->get_next();
}


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
	//找到待删除结点的前驱结点
	ListNode<T>* s1 = findLastByData(tar);
	ListNode<T>* tmp = s1->next;
	//删除该结点
	s1->next = tmp->next;
	delete tmp;
	size--; //链表长度减一
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

template<class T>
void get_intersection(const List<T>& l1, const List<T>& l2, List<T>& result)
{
	auto it1 = l1.get_head();
	auto it2 = l2.get_head();

	while (it1 != nullptr && it2 != nullptr)
	{
		int num1 = it1->get_data(), num2 = it2->get_data();
		if (num1 < num2)
			it1 = it1->get_next();
		else if (num1 > num2)
			it2 = it2->get_next();
		else
		{
			result.insert(num1);
			it1 = it1->get_next();
			it2 = it2->get_next();
		}
	}
}

int main() {
	int n;
	List<int> l1, l2;
	while (cin >> n) {
		if (n == -1)
			break;
		l1.insert(n);
	}
	while (cin >> n) {
		if (n == -1)
			break;
		l2.insert(n);
	}
	List<int>intersection;
	get_intersection<int>(l1, l2, intersection);
	if (intersection.get_list_size() == 0)
		cout << "NULL" << endl;
	else
	{
		ListNode<int>* head_node = intersection.get_head();
		while (head_node != nullptr)
		{
			cout << head_node->get_data() << ' ';
			head_node = head_node->get_next();
		}
	}
	return 0;
}