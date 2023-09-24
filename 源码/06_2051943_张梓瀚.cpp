#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_NAME_LENGTH = 100;

template<class T>
class my_tree;

template<class T>
class tree_node
{
	T* data = nullptr;
	tree_node<T>* first_child_ = nullptr;
	tree_node<T>* next_sibling_ = nullptr;
	tree_node<T>* prev = nullptr;
public:
	//Ĭ�Ϲ��캯��
	tree_node() {};
	//��ֵ���캯��
	tree_node(const T& src);
	//��ȡ���ĵ�һ������
	tree_node<T>* child();
	//��ȡ���ĵ�һ���ֵ�
	tree_node<T>* sibling();
	//ɾ��������к���
	void delete_children();
	//ɾ������һ���ֵ�
	void delete_sibling();
	//Ϊ������Ӻ���
	void add_child(const T& src);
	//Ϊ��������ֵ�
	void add_sibling(const T* str);
	//��ȡ����Ӧ����
	const T get_data();
	//���ý������
	void set_data(const T& new_data);
	friend class my_tree<T>;
};

template <class T>
tree_node<T>::tree_node(const T& src)
{
	data = new T(src);
}

template <class T>
tree_node<T>* tree_node<T>::child()
{
	return first_child_;
}

template <class T>
tree_node<T>* tree_node<T>::sibling()
{
	return next_sibling_;
}

template <class T>
void tree_node<T>::delete_sibling()
{
	tree_node<T>* sibling = next_sibling_;
	if (sibling->sibling() != nullptr)
		next_sibling_ = sibling->sibling();
	delete sibling;
	sibling = nullptr;
}

template <class T>
void tree_node<T>::delete_children()
{
	tree_node<T>* child = first_child_, * tmp;
	while (child != nullptr) {
		tmp = child->next_sibling_;
		if (child->first_child_ != nullptr) //�ݹ�ɾ����㺢�ӵ��ӽ��
			child->first_child_->delete_children();
		delete child;
		child = tmp;
	}
	first_child_ = nullptr;
}

template <class T>
void tree_node<T>::add_child(const T& src)
{
	//�ڵ�ǰ����ӽ���ĩβ���һ���ӽ��
	tree_node* child = new tree_node(src);
	if (first_child_ == nullptr)
		first_child_ = child, child->prev = this;
	else
	{
		tree_node* last_child = first_child_;
		while (last_child->next_sibling_ != nullptr)
			last_child = last_child->next_sibling_;
		last_child->next_sibling_ = child, child->prev = last_child;
	}
}

template <class T>
void tree_node<T>::add_sibling(const T* str)
{
	//�ڵ�ǰ��������ֵܵ�ĩβ���һ�����ֵܽ��
	tree_node* sibling = new tree_node(str);
	tree_node* last_sibling = this;
	while (last_sibling->next_sibling_ != nullptr)
		last_sibling = last_sibling->next_sibling_;
	last_sibling->next_sibling_ = sibling, sibling->prev = last_sibling;
}

template <class T>
const T tree_node<T>::get_data()
{
	return *data;
}

template <class T>
void tree_node<T>::set_data(const T& new_data)
{
	*data = new_data;
}

template<class T>
class my_tree
{

public:
	//Ĭ�Ϲ��캯��
	my_tree();
	//��ֵ���캯��
	explicit my_tree(tree_node<T>* src);
	//��������
	~my_tree();
	//��ȡָ������˫�׽ڵ�
	tree_node<T>* get_parent(tree_node<T>* c, tree_node<T>* current_node);
	//Ѱ��Ŀ���㣨ʹ�ò������ͺ���ָ��equal_sign�ж��Ƿ���Ŀ���㣩
	tree_node<T>* find_node(const T dest, tree_node<T>* current_node, bool(*equal_sign)(T, T));
	//ǰ�����
	void pre_traversal(tree_node<T>* root);
	//ǰ�������װ
	void pre_traversal();
	tree_node<T>* root, * current;
};

template <class T>
my_tree<T>::my_tree()
{
	root = new tree_node<T>;
	current = root;
}

template <class T>
my_tree<T>::my_tree(tree_node<T>* src)
{
	root = new tree_node<T>(src);
	current = root;
}

template <class T>
my_tree<T>::~my_tree()
{
	delete root;
	delete current;
}

template <class T>
tree_node<T>* my_tree<T>::get_parent(tree_node<T>* c, tree_node<T>* current_node)
{
	tree_node<T>* child = current_node->first_child_;
	while (child != nullptr && child != c)
	{
		if (get_parent(c, child))
			return true;
		child = child->next_sibling_;
	}
	if (child != nullptr && child == c)
		return current_node;
	else
		return nullptr;
}

template <class T>
tree_node<T>* my_tree<T>::find_node(const T dest, tree_node<T>* current_node, bool(*equal_sign)(T, T))
{
	if (equal_sign(*current_node->data, dest))
	{
		return current_node;
	}
	else
	{
		tree_node<T>* child = current_node->first_child_;
		tree_node<T>* result = new tree_node<T>;
		while (!(child == nullptr))
		{
			result = find_node(dest, child, equal_sign);
			if (result != nullptr)
				return result;
			else
				child = child->next_sibling_;
		}
	}
	return nullptr;
}

template <class T>
void my_tree<T>::pre_traversal(tree_node<T>* root)
{
	if (root != nullptr)
	{
		cout << root->get_data() << ' ';
		pre_traversal(root->first_child_);
		pre_traversal(root->next_sibling_);
	}
}

template <class T>
void my_tree<T>::pre_traversal()
{
	pre_traversal(root);
}

//�ж��ַ�����Ⱥ���
bool my_strcmp(char* str1, char* str2)
{
	if (!(str1 && str2))
		return false;
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
		{
			return true;
		}
		str1++;
		str2++;
	}
	return false;
}

class Geneology : public my_tree<char*>
{
private:
	//����ָ�룬��Ϊ���ҽ��ʱ�Ƚ����ݣ��Ժ���������ʽ����
	bool(*equal_sign)(char*, char*);
public:
	Geneology();
	//���Ƽ���
	void improve_family();
	//��Ӽ�ͥ��Ա
	void add_member();
	//��ɢ�ֲ���ͥ
	void delete_family();
	//�ı��ͥ��Ա����
	void change_member_name();
};

Geneology::Geneology()
{
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	tree_node<char*>* new_root = new tree_node<char*>(name);
	root = new_root;
	equal_sign = my_strcmp;

	cout << "�˼��׵������ǣ�" << root->get_data() << endl << endl;
	cout << "**" << setw(14) << ' ' << "���׹���ϵͳ" << setw(16) << ' ' << "**" << endl;
	cout << "==============================================" << endl;
	cout << "**" << setw(13) << ' ' << "��ѡ��Ҫִ�еĲ���" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "A --- ���Ƽ���" << setw(15) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "B --- ��Ӽ�ͥ��Ա" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "C --- ��ɢ�ֲ���ͥ" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "D --- ���ļ�ͥ��Ա����" << setw(7) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "E --- �˳�����" << setw(15) << ' ' << "**" << endl;
	cout << "==============================================" << endl;
}

inline void Geneology::improve_family()
{
	cout << "����Ҫ������ͥ���˵�������";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	name[strlen(name)] = '\0';
	//���Ҷ�Ӧ�Ľ���Ƿ������еļ�ͥ����
	tree_node<char*>* parent = find_node(name, root, equal_sign);
	if (parent == nullptr)
		cout << "���޴���" << endl;
	else
	{
		int num;
		cout << "������" << name << "�Ķ�Ů������";
		cin >> num;
		cout << "����������" << name << "�Ķ�Ů������";
		while (num--)
		{
			char* child = new char[MAX_NAME_LENGTH];
			cin >> child;
			parent->add_child(child);
		}
		cout << parent->get_data() << "�ĵ�һ�������ǣ�";
		tree_node<char*>* child = parent->child();
		while (child != nullptr)
		{
			cout << ' ' << child->get_data();
			child = child->sibling();
		}
		//����������ڻ������еĳ�������
		cin.clear();
		cin.ignore(1024, '\n');
		cout << endl;
	}
}

inline void Geneology::add_member()
{
	cout << "����Ҫ��Ӷ��ӣ���Ů�������˵�������";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	//����������ڻ������еĳ�������
	cin.clear();
	cin.ignore(1024, '\n');
	//���Ҷ�Ӧ�Ľ���Ƿ������еļ�ͥ����
	tree_node<char*>* parent = find_node(name, root, equal_sign);
	if (parent == nullptr)
		cout << "���޴���" << endl;
	else
	{
		cout << "������" << name << "����ӵĶ��ӣ���Ů������������";
		char* new_child = new char[MAX_NAME_LENGTH];
		cin >> new_child;
		//����������ڻ������еĳ�������
		cin.clear();
		cin.ignore(1024, '\n');
		//����ӽ��
		parent->add_child(new_child);
		cout << parent->get_data() << "�ĵ�һ�������ǣ�";
		tree_node<char*>* child = parent->child();
		while (child != nullptr)
		{
			cout << ' ' << child->get_data();
			child = child->sibling();
		}
		cout << endl;
	}
}

inline void Geneology::delete_family()
{
	cout << "����Ҫ��ɢ��ͥ���˵�Ŀǰ������";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	tree_node<char*>* current_node = find_node(name, root, equal_sign);
	if (current_node == nullptr)
		cout << "���޴���" << endl;
	else {
		cout << "Ҫ��ɢ��ͥ���˵�������" << name << endl;
		if (current_node->child() == nullptr)
			cout << current_node->get_data() << "���޼�ͥ" << endl;
		else
		{
			cout << current_node->get_data() << "�ĵ�һ�������ǣ�";
			tree_node<char*>* child = current_node->child(), * tmp = new tree_node<char*>;
			while (child != nullptr)
			{
				cout << ' ' << child->get_data();
				child = child->sibling();
			}
			cout << endl;
			//����ɾ�������ӽ��ĺ���
			current_node->delete_children();
		}
	}
}

inline void Geneology::change_member_name()
{
	cout << "����Ҫ�����������˵�Ŀǰ������";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	//����������ڻ������еĳ�������
	cin.clear();
	cin.ignore(1024, '\n');
	tree_node<char*>* current_node = find_node(name, root, equal_sign);
	if (current_node == nullptr)
		cout << "���޴���" << endl;
	else
	{
		cout << "��������ĺ��������";
		char* new_name = new char[MAX_NAME_LENGTH];
		cin >> new_name;
		//����������ڻ������еĳ�������
		cin.clear();
		cin.ignore(1024, '\n');
		//��������
		current_node->set_data(new_name);
		cout << name << "�Ѹ���Ϊ" << new_name << endl;
	}
}


int main()
{
	//��ʼ������������
	Geneology gen;
	char option = '0';
	while (option != 'E') {
		cout << endl << endl << "��ѡ��Ҫִ�еĲ�����";
		cin >> option;
		switch (option)
		{
		case 'A':
			gen.improve_family();
			break;
		case 'B':
			gen.add_member();
			break;
		case 'C':
			gen.delete_family();
			break;
		case 'D':
			gen.change_member_name();
			break;
		case 'E':
			break;
		default:
			cout << "��������ȷ�����" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			break;
		}
	}
	return 0;
}