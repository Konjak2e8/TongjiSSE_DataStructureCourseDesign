#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
const int ExceptionNum = 5;

class String
{
	char* m_data;

public:
	String(const char* str = nullptr) //默认构造函数
	{
		if (str == nullptr)
		{
			m_data = new char[1];
			*m_data = '\0';
		}
		else
		{
			m_data = new char[strlen(str) + 1];
			strcpy(m_data, str);
		}
	}

	~String() //析构函数
	{
		delete[] m_data;
	}

	String(const String& src) //复制构造函数
	{
		int len = strlen(src.m_data);
		m_data = new char[len + 1];
		strcpy(m_data, src.m_data);
	}

	String(String&& src)
	{
		m_data = src.m_data;
		src.m_data = nullptr;
	}

	String& operator=(const char* src)
	{
		if (m_data)
			delete[] m_data;
		int len = strlen(src);
		m_data = new char[len + 1];
		strcpy(m_data, src);
		return *this;
	}

	String& operator=(const String& src) //拷贝赋值运算符
	{
		if (this != &src) //判断是否拷贝自身
		{
			if (m_data)
				delete[] m_data;
			int len = strlen(src.m_data);
			m_data = new char[len + 1];
			strcpy(m_data, src.m_data);
		}
		return *this;
	}

	String& operator=(String&& src) //移动赋值运算符
	{
		if (this != &src)
		{
			delete[] m_data;
			m_data = src.m_data;
			src.m_data = nullptr;
		}
		return *this;
	}

	friend istream& operator>>(istream& is, String& dest)
	{
		is >> dest.m_data;
		return is;
	}

	friend ostream& operator<<(ostream& os, const String& src)
	{
		os << src.m_data;
		return os;
	}
};

/*学生信息类*/
const String Sex[2] = { "男", "女" };
const String Type[3] = { "软件设计师", "软件开发师", "软件测试师" };

class Student
{
private:
	int id;
	String name;
	String sex;
	int age;
	String type;
public:
	//默认构造函数
	Student();
	//复制构造函数
	Student(const Student& tar);
	//获取学号（用于查找）
	int get_id();
	//修改学号
	void set_id(const int& new_id);
	//重载等于运算符
	bool operator ==(const Student& rhs) const;
	//重载流插入、流提取运算符
	friend istream& operator>>(istream& is, Student& s);
	friend ostream& operator<<(ostream& os, const Student& s);
};

Student::Student()
{
	id = -1;
	name = "(unnamed)";
	sex = "/";
	age = -1;
	type = "/";
}

Student::Student(const Student& tar)
{
	id = tar.id;
	name = tar.name;
	sex = tar.sex;
	age = tar.age;
	type = tar.type;
}

int Student::get_id()
{
	return id;
}

void Student::set_id(const int& new_id)
{
	id = new_id;
}

bool Student::operator ==(const Student& rhs) const
{
	return id == rhs.id;
}

istream& operator>>(istream& is, Student& s)
{
	is >> s.id >> s.name >> s.sex >> s.age >> s.type;
	return is;
}

ostream& operator<<(ostream& os, const Student& s)
{
	os << setiosflags(ios::left) << setw(8) << s.id << setw(16) << s.name << ' ' << s.sex << "      " << setw(6) << s.
		age << ' ' << s.type << endl;
	return os;
}

// const String exceptionMessages[5] = {"Invalid ID"};

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

const String Prompts[7] = {
	"首先请建立考生信息系统！\n",
	"请输入考生人数：",
	"请依次输入考生的考号、姓名、性别、年龄及报考类别！\n",
	"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）：",
	"请输入要插入考生的位置：",
	"请输入要操作的考生考号：",
	"考号\t姓名\t\t性别\t年龄\t报考类别\n"
};

class ExamRegisterSystem : public List<Student>
{
	Student s;
public:
	//初始化学生信息
	void Init();
	//处理请求
	void Query();
};

inline void ExamRegisterSystem::Init()
{
	int student_num;
	cout << Prompts[0] << Prompts[1];
	cin >> student_num;
	//错误处理，增强程序的健壮性
	while (cin.fail() || student_num <= 0)
	{
		cout << "考生人数应为正整数！" << endl;
		cout << "请重新输入考生人数：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> student_num;
	}
	cout << Prompts[2];
	for (int i = 0; i < student_num; i++)
	{
		cin >> s;
		insert(s);
	}
}

inline void ExamRegisterSystem::Query()
{
	int opt;
	cout << Prompts[6];
	printAll(cout);

	Student student_info, tmp;
	ListNode<Student>* removed_student = new ListNode<Student>, * changed_student = new ListNode<Student>, * exist_info = new ListNode<Student>;
	int pos, ID;
	while (1)
	{
		cout << Prompts[3];
		cin >> opt;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (opt)
		{
		case 0:
			exit(0);
			break;
		case 1:
			cout << Prompts[2];
			cin >> student_info;
			//输入学号，并判断输入的学号是否有重复
			while (findByData(student_info) != nullptr)
			{
				cout << "插入失败，该考号已被使用，请重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> student_info;
			}
			cout << Prompts[4];
			cin >> pos;
			//判断位置是否存在，增强程序的鲁棒性
			while (pos <= 0 || pos > get_list_size() + 1 || cin.fail())
			{
				cout << "输入非法（插入位置应为正整数，且不超过当前最大位置+1）" << endl;
				cout << "请重新输入插入位置：";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> pos;
			}
			insert(student_info, pos);
			break;
		case 2:
			cout << Prompts[5];
			cin >> ID;
			student_info.set_id(ID);
			//依据学号查找学生
			removed_student = findByData(student_info);
			//未查询到学生，重新输入
			while (removed_student == nullptr)
			{
				cout << "该考生号对应的考生不存在，请重新输入考生号 : ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> ID;
				student_info.set_id(ID);
				removed_student = findByData(student_info);
			}
			remove(student_info);
			cout << "删除成功！" << endl;
			break;
		case 3:
			cout << Prompts[5];
			cin >> ID;
			student_info.set_id(ID);
			//依据学号查找学生
			changed_student = findByData(student_info);
			//未查询到学生，重新输入
			while (changed_student == nullptr)
			{
				cout << "该考生号对应的考生不存在，请重新输入考生号" << endl;
				cin >> ID;
				student_info.set_id(ID);
				changed_student = findByData(student_info);
			}
			cout << "查询成功，您查询的考生信息为：" << endl;
			cout << findByData(student_info)->get_data();
			break;
		case 4:
			cout << Prompts[5];
			cin >> ID;
			student_info.set_id(ID);
			//依据学号查找学生
			changed_student = findByData(student_info);
			//未查询到学生，重新输入
			while (changed_student == nullptr)
			{
				cout << "该考生号对应的考生不存在，请重新输入考生号" << endl;
				cin >> ID;
				student_info.set_id(ID);
				changed_student = findByData(student_info);
			}
			cout << Prompts[2];
			//检查新考号是否存在
			cin >> tmp;
			exist_info = findByData(tmp);
			while (exist_info != nullptr)
			{
				cout << "修改失败，该考号已经存在，请重新输入信息" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> tmp;
				exist_info = findByData(tmp);
			}
			modify(student_info, tmp);
			cout << "修改成功！" << endl;
			break;
		case 5:
			cout << Prompts[6];
			printAll();
			break;
		}
		if (opt != 5 && opt != 3)
			printAll();
		cout << endl;
	}
}
int main() {
	ExamRegisterSystem sys;
	sys.Init();
	sys.Query();
	return 0;
}