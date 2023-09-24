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
	inline void print_all(ostream& os = cout);
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
		//�Ƚ��˿ͷֱ����
		if (id & 1)
			q1.enqueue(id);
		else
			q2.enqueue(id);
	}
	while (!(q1.isEmpty() && q2.isEmpty()))
	{
		//�����ڶ��в�Ϊ�գ�����Ŀ�������������ҵ��Ĺ˿ͳ��Ӳ����
		if (!q1.isEmpty())
			cout << q1.dequeue() << ' ';
		if (!q1.isEmpty())
			cout << q1.dequeue() << ' ';
		if (!q2.isEmpty())
			cout << q2.dequeue() << ' ';
	}
	return 0;
}