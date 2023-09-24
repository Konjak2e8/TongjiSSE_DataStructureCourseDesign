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
	String(const char* str = nullptr) //Ĭ�Ϲ��캯��
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

	~String() //��������
	{
		delete[] m_data;
	}

	String(const String& src) //���ƹ��캯��
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

	String& operator=(const String& src) //������ֵ�����
	{
		if (this != &src) //�ж��Ƿ񿽱�����
		{
			if (m_data)
				delete[] m_data;
			int len = strlen(src.m_data);
			m_data = new char[len + 1];
			strcpy(m_data, src.m_data);
		}
		return *this;
	}

	String& operator=(String&& src) //�ƶ���ֵ�����
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

/*ѧ����Ϣ��*/
const String Sex[2] = { "��", "Ů" };
const String Type[3] = { "������ʦ", "�������ʦ", "�������ʦ" };

class Student
{
private:
	int id;
	String name;
	String sex;
	int age;
	String type;
public:
	//Ĭ�Ϲ��캯��
	Student();
	//���ƹ��캯��
	Student(const Student& tar);
	//��ȡѧ�ţ����ڲ��ң�
	int get_id();
	//�޸�ѧ��
	void set_id(const int& new_id);
	//���ص��������
	bool operator ==(const Student& rhs) const;
	//���������롢����ȡ�����
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
	//Ĭ�Ϲ��캯��
	ListNode<T>();
	//��ֵ���캯��
	ListNode<T>(const T& src);
	//��ȡ����
	const T& get_data();
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
const T& ListNode<T>::get_data() //�������ݵĳ�����
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
	//Ĭ�Ϲ��캯��
	List();
	//��������
	~List();
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

const String Prompts[7] = {
	"�����뽨��������Ϣϵͳ��\n",
	"�����뿼��������",
	"���������뿼���Ŀ��š��������Ա����估�������\n",
	"��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ����������",
	"������Ҫ���뿼����λ�ã�",
	"������Ҫ�����Ŀ������ţ�",
	"����\t����\t\t�Ա�\t����\t�������\n"
};

class ExamRegisterSystem : public List<Student>
{
	Student s;
public:
	//��ʼ��ѧ����Ϣ
	void Init();
	//��������
	void Query();
};

inline void ExamRegisterSystem::Init()
{
	int student_num;
	cout << Prompts[0] << Prompts[1];
	cin >> student_num;
	//��������ǿ����Ľ�׳��
	while (cin.fail() || student_num <= 0)
	{
		cout << "��������ӦΪ��������" << endl;
		cout << "���������뿼��������";
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
			//����ѧ�ţ����ж������ѧ���Ƿ����ظ�
			while (findByData(student_info) != nullptr)
			{
				cout << "����ʧ�ܣ��ÿ����ѱ�ʹ�ã�����������" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> student_info;
			}
			cout << Prompts[4];
			cin >> pos;
			//�ж�λ���Ƿ���ڣ���ǿ�����³����
			while (pos <= 0 || pos > get_list_size() + 1 || cin.fail())
			{
				cout << "����Ƿ�������λ��ӦΪ���������Ҳ�������ǰ���λ��+1��" << endl;
				cout << "�������������λ�ã�";
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
			//����ѧ�Ų���ѧ��
			removed_student = findByData(student_info);
			//δ��ѯ��ѧ������������
			while (removed_student == nullptr)
			{
				cout << "�ÿ����Ŷ�Ӧ�Ŀ��������ڣ����������뿼���� : ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> ID;
				student_info.set_id(ID);
				removed_student = findByData(student_info);
			}
			remove(student_info);
			cout << "ɾ���ɹ���" << endl;
			break;
		case 3:
			cout << Prompts[5];
			cin >> ID;
			student_info.set_id(ID);
			//����ѧ�Ų���ѧ��
			changed_student = findByData(student_info);
			//δ��ѯ��ѧ������������
			while (changed_student == nullptr)
			{
				cout << "�ÿ����Ŷ�Ӧ�Ŀ��������ڣ����������뿼����" << endl;
				cin >> ID;
				student_info.set_id(ID);
				changed_student = findByData(student_info);
			}
			cout << "��ѯ�ɹ�������ѯ�Ŀ�����ϢΪ��" << endl;
			cout << findByData(student_info)->get_data();
			break;
		case 4:
			cout << Prompts[5];
			cin >> ID;
			student_info.set_id(ID);
			//����ѧ�Ų���ѧ��
			changed_student = findByData(student_info);
			//δ��ѯ��ѧ������������
			while (changed_student == nullptr)
			{
				cout << "�ÿ����Ŷ�Ӧ�Ŀ��������ڣ����������뿼����" << endl;
				cin >> ID;
				student_info.set_id(ID);
				changed_student = findByData(student_info);
			}
			cout << Prompts[2];
			//����¿����Ƿ����
			cin >> tmp;
			exist_info = findByData(tmp);
			while (exist_info != nullptr)
			{
				cout << "�޸�ʧ�ܣ��ÿ����Ѿ����ڣ�������������Ϣ" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> tmp;
				exist_info = findByData(tmp);
			}
			modify(student_info, tmp);
			cout << "�޸ĳɹ���" << endl;
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