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
	//默认构造函数
	tree_node() {};
	//赋值构造函数
	tree_node(const T& src);
	//获取结点的第一个孩子
	tree_node<T>* child();
	//获取结点的第一个兄弟
	tree_node<T>* sibling();
	//删除结点所有孩子
	void delete_children();
	//删除结点的一个兄弟
	void delete_sibling();
	//为结点增加孩子
	void add_child(const T& src);
	//为结点增加兄弟
	void add_sibling(const T* str);
	//获取结点对应数据
	const T get_data();
	//设置结点数据
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
		if (child->first_child_ != nullptr) //递归删除结点孩子的子结点
			child->first_child_->delete_children();
		delete child;
		child = tmp;
	}
	first_child_ = nullptr;
}

template <class T>
void tree_node<T>::add_child(const T& src)
{
	//在当前结点子结点的末尾添加一个子结点
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
	//在当前结点所在兄弟的末尾添加一个新兄弟结点
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
	//默认构造函数
	my_tree();
	//赋值构造函数
	explicit my_tree(tree_node<T>* src);
	//析构函数
	~my_tree();
	//获取指定结点的双亲节点
	tree_node<T>* get_parent(tree_node<T>* c, tree_node<T>* current_node);
	//寻找目标结点（使用布尔类型函数指针equal_sign判断是否是目标结点）
	tree_node<T>* find_node(const T dest, tree_node<T>* current_node, bool(*equal_sign)(T, T));
	//前序遍历
	void pre_traversal(tree_node<T>* root);
	//前序遍历封装
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

//判断字符串相等函数
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
	//函数指针，作为查找结点时比较依据，以函数参数形式传入
	bool(*equal_sign)(char*, char*);
public:
	Geneology();
	//完善家谱
	void improve_family();
	//添加家庭成员
	void add_member();
	//解散局部家庭
	void delete_family();
	//改变家庭成员名称
	void change_member_name();
};

Geneology::Geneology()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	tree_node<char*>* new_root = new tree_node<char*>(name);
	root = new_root;
	equal_sign = my_strcmp;

	cout << "此家谱的祖先是：" << root->get_data() << endl << endl;
	cout << "**" << setw(14) << ' ' << "家谱管理系统" << setw(16) << ' ' << "**" << endl;
	cout << "==============================================" << endl;
	cout << "**" << setw(13) << ' ' << "请选择要执行的操作" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "A --- 完善家谱" << setw(15) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "B --- 添加家庭成员" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "C --- 解散局部家庭" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "D --- 更改家庭成员姓名" << setw(7) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "E --- 退出程序" << setw(15) << ' ' << "**" << endl;
	cout << "==============================================" << endl;
}

inline void Geneology::improve_family()
{
	cout << "输入要建立家庭的人的姓名：";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	name[strlen(name)] = '\0';
	//查找对应的结点是否在已有的家庭树中
	tree_node<char*>* parent = find_node(name, root, equal_sign);
	if (parent == nullptr)
		cout << "查无此人" << endl;
	else
	{
		int num;
		cout << "请输入" << name << "的儿女人数：";
		cin >> num;
		cout << "请依次输入" << name << "的儿女姓名：";
		while (num--)
		{
			char* child = new char[MAX_NAME_LENGTH];
			cin >> child;
			parent->add_child(child);
		}
		cout << parent->get_data() << "的第一代子孙是：";
		tree_node<char*>* child = parent->child();
		while (child != nullptr)
		{
			cout << ' ' << child->get_data();
			child = child->sibling();
		}
		//清理可能留在缓冲区中的超限输入
		cin.clear();
		cin.ignore(1024, '\n');
		cout << endl;
	}
}

inline void Geneology::add_member()
{
	cout << "输入要添加儿子（或女儿）的人的姓名：";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	//清理可能留在缓冲区中的超限输入
	cin.clear();
	cin.ignore(1024, '\n');
	//查找对应的结点是否在已有的家庭树中
	tree_node<char*>* parent = find_node(name, root, equal_sign);
	if (parent == nullptr)
		cout << "查无此人" << endl;
	else
	{
		cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
		char* new_child = new char[MAX_NAME_LENGTH];
		cin >> new_child;
		//清理可能留在缓冲区中的超限输入
		cin.clear();
		cin.ignore(1024, '\n');
		//添加子结点
		parent->add_child(new_child);
		cout << parent->get_data() << "的第一代子孙是：";
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
	cout << "输入要解散家庭的人的目前姓名：";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	tree_node<char*>* current_node = find_node(name, root, equal_sign);
	if (current_node == nullptr)
		cout << "查无此人" << endl;
	else {
		cout << "要解散家庭的人的姓名是" << name << endl;
		if (current_node->child() == nullptr)
			cout << current_node->get_data() << "暂无家庭" << endl;
		else
		{
			cout << current_node->get_data() << "的第一代子孙是：";
			tree_node<char*>* child = current_node->child(), * tmp = new tree_node<char*>;
			while (child != nullptr)
			{
				cout << ' ' << child->get_data();
				child = child->sibling();
			}
			cout << endl;
			//调用删除所有子结点的函数
			current_node->delete_children();
		}
	}
}

inline void Geneology::change_member_name()
{
	cout << "输入要更改姓名的人的目前姓名：";
	char* name = new char[MAX_NAME_LENGTH];
	cin >> name;
	//清理可能留在缓冲区中的超限输入
	cin.clear();
	cin.ignore(1024, '\n');
	tree_node<char*>* current_node = find_node(name, root, equal_sign);
	if (current_node == nullptr)
		cout << "查无此人" << endl;
	else
	{
		cout << "请输入更改后的姓名：";
		char* new_name = new char[MAX_NAME_LENGTH];
		cin >> new_name;
		//清理可能留在缓冲区中的超限输入
		cin.clear();
		cin.ignore(1024, '\n');
		//更改名字
		current_node->set_data(new_name);
		cout << name << "已更名为" << new_name << endl;
	}
}


int main()
{
	//初始化家谱树对象
	Geneology gen;
	char option = '0';
	while (option != 'E') {
		cout << endl << endl << "请选择要执行的操作：";
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
			cout << "请输入正确的序号" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			break;
		}
	}
	return 0;
}