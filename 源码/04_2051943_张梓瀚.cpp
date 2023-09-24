#define _CRT_SECURE_NO_WARNINGS
#include "MyStack.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const int MAX_LEN = 2 * 100;

/*计算运算符优先级*/
int priority(char c) {
	if (c == '(')
		return 0;
	else if (c == '+' || c == '-')
		return 1;
	else
		return 2;
}

/*比较运算符优先级*/
bool cmp(char a, char b) {
	return priority(a) > priority(b);
}

const char* infix_to_suffix(const char* infix)
{
	char* suffix = new char[MAX_LEN + 1];
	char last = '1'; //last记录上个符号，简化判断
	bool fir = false, is_opt = false; // 判断首个符号和负号是否为运算符的标志
	int cnt = 0; //记录在后缀表达式中的位置
	myStack<char>stk;
	for (int i = 0; infix[i] != '\0'; i++) {
		char c = infix[i];
		//扫描到句子末尾，结束循环
		if (c == '\0') {
			break;
		}
		else if (c == ' ') {
			last = c;
			continue;
		}
		//对于小数点和数字，直接输出
		else if (isdigit(c) || c == '.') {
			if (isdigit(c))
				is_opt = true;
			//判断当前的数字是否和前几个符号同属一个运算数
			if (!(!fir || last == '-' || isdigit(last) || last == '.'))
				suffix[cnt++] = ' ';
			suffix[cnt++] = c;
			fir = true;
			last = c;
			continue;
		}
		//右括号，将栈顶符号出栈直到对应的左括号出栈
		else if (c == ')') {
			while (!stk.empty() && stk.top() != '(') {
				suffix[cnt++] = ' ';
				suffix[cnt++] = stk.top();
				last = stk.top();
				stk.pop();
			}
			stk.pop();
		}
		//左括号直接压栈
		else if (c == '(') {
			stk.push(c);
		}
		else {
			if ((c == '+' || c == '-') && isdigit(infix[i + 1])) {
				//对负数的特殊处理
				if (c == '-') {
					//若负号为运算符，输出空格
					if (is_opt)
						suffix[cnt++] = ' ';
					suffix[cnt++] = c;
					last = c;
				}
				continue;
			}
			while (!stk.empty() && !cmp(c, stk.top())) {
				suffix[cnt++] = ' ';
				suffix[cnt++] = stk.top();
				last = stk.top();
				stk.pop();
			}
			stk.push(c);
		}
	}
	//若栈内还有剩余运算符或数字则全部输出
	while (!stk.empty()) {
		suffix[cnt++] = ' ';
		suffix[cnt++] = stk.top();
		stk.pop();
	}
	suffix[cnt] = '\0';
	return suffix;
}

int main() {
	char str[MAX_LEN + 1];
	bool is_valid = 1;
	while (1)
	{
		cout << "请输入待转换的中缀表达式（长度不超过100个字符）：" << endl;
		cin.get(str, MAX_LEN);
		is_valid = 1;
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (str[i] <= -1 || str[i] >= 255)
			{
				is_valid = 0;
				break;
			}
		}
		if (is_valid)
			break;
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "输入表达式含有非法字符，请重新输入" << endl;
	}
	cout << "转换后的后缀表达式为：" << endl << infix_to_suffix(str);
	return 0;
}